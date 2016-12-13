#include "componenteximpl.h"
#include "serverdllextend.h"
#include <tlhelp32.h>
#include <psapi.h>
#include <QDebug>

HRESULT STDMETHODCALLTYPE CProcessMonitorExImpl::QueryInterface(REFIID riid, void **ppvObject) {
    if (riid == IID_IUnknown) {
        *ppvObject = static_cast<IUnknown*>(static_cast<IProcessMonitor*>(this));
        this->AddRef();
        return S_OK;
    } else if (riid == IID_IDispatch) {
        *ppvObject = static_cast<IDispatch*>(static_cast<IProcessMonitorExDispatch*>(this));
        this->AddRef();
        return S_OK;
    } else if (riid == IID_IProcessMonitor) {
        *ppvObject = static_cast<IProcessMonitor*>(this);
        this->AddRef();
        return S_OK;
    } else if (riid == IID_IProcessMonitorRegistrar) {
        *ppvObject = static_cast<IProcessMonitorRegistrar*>(this);
        this->AddRef();
        return S_OK;
    } else if (riid == IID_IProcessMonitorRegistrarEx) {
        *ppvObject = static_cast<IProcessMonitorRegistrarEx*>(this);
        this->AddRef();
        return S_OK;
    }

    *ppvObject = NULL;
    return E_NOINTERFACE;
}

ULONG STDMETHODCALLTYPE CProcessMonitorExImpl::AddRef() {
    InterlockedIncrement(&this->lRefCount);
    InterlockedIncrement(&g_ObjectsInUse);
    return S_OK;
}

ULONG STDMETHODCALLTYPE CProcessMonitorExImpl::Release() {
    long nRefCount = InterlockedDecrement(&this->lRefCount);
    InterlockedDecrement(&g_ObjectsInUse);

    if (nRefCount == 0) {
        delete this;
    }

    return nRefCount;
}

HRESULT STDMETHODCALLTYPE CProcessMonitorExImpl::pushPid(unsigned int pid) {
    setError(0);
    return this->delegatePMR->pushPid(pid);
}

HRESULT STDMETHODCALLTYPE CProcessMonitorExImpl::removePid(unsigned int pid) {
    setError(0);
    return this->delegatePMR->removePid(pid);
}

HRESULT STDMETHODCALLTYPE CProcessMonitorExImpl::clearPids() {
    setError(0);
    return this->delegatePMR->clearPids();
}

HRESULT STDMETHODCALLTYPE CProcessMonitorExImpl::updateStatuses(void) {
    setError(0);

    // TODO: update names
    // Check newly created processes
    if (pnames.size() != 0) {
        PROCESSENTRY32 entry;
        entry.dwSize = sizeof(PROCESSENTRY32);

        HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

        if (Process32First(snapshot, &entry) == TRUE) {
            while (Process32Next(snapshot, &entry) == TRUE) {
                if (phandles.contains(entry.th32ProcessID)) {
                    continue;
                }

                bool openHandle = false;
                QString pname = QString::fromWCharArray(entry.szExeFile);

                foreach (QString name, pnames) {
                    if (name.compare(pname, Qt::CaseInsensitive) == 0) {
                        qDebug() << LOGTAG << pname << "good";

                        openHandle = true;
                        break;
                    }
                }

                if (openHandle) {
                    HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION, FALSE, entry.th32ProcessID);

                    if (hProcess == NULL) {
                        errMsg += "\r\n" + pname + " (" + QString::number(entry.th32ProcessID) +
                                "): OpenProcess fails with " + getLastErrorMsg();
                    } else {
                        qDebug() << LOGTAG << "handle opened";
                        phandles.insert(entry.th32ProcessID, hProcess);
                        ppidnames.insert(entry.th32ProcessID, pname);
                    }
                }
            }
        }

        CloseHandle(snapshot);
    }


    return this->delegatePM->updateStatuses();
}

HRESULT STDMETHODCALLTYPE CProcessMonitorExImpl::getChangedStatusFirst(unsigned int *pid,
                                                                     LPBSTR pname,
                                                                     unsigned int *pnamelen,
                                                                     unsigned int *status) {
    setError(0);
    return this->delegatePM->getChangedStatusFirst(pid, pname, pnamelen, status);
}

HRESULT STDMETHODCALLTYPE CProcessMonitorExImpl::getChangedStatusNext(unsigned int *pid,
                                                                    LPBSTR pname,
                                                                    unsigned int *pnamelen,
                                                                    unsigned int *status) {
    setError(0);
    return this->delegatePM->getChangedStatusFirst(pid, pname, pnamelen, status);
}

HRESULT STDMETHODCALLTYPE CProcessMonitorExImpl::registerProcessByName(BSTR name) {
    setError(0);
    QString nameStr = QString::fromWCharArray(name);

    if (nameStr.length() == 0) {
        setError(206, "1");
        return S_FALSE;
    }

    pnamesLock.lock();

    HRESULT result = S_OK;

    if (pnames.contains(nameStr)) {
        setError(204);
        result = S_FALSE;
    } else {
        pnames.push_back(nameStr);
    }

    pnamesLock.unlock();
    return result;
}

HRESULT STDMETHODCALLTYPE CProcessMonitorExImpl::unregisterProcessByName(BSTR name) {
    setError(0);
    QString nameStr = QString::fromWCharArray(name);

    if (nameStr.length() == 0) {
        setError(206, "1");
        return S_FALSE;
    }

    pnamesLock.lock();

    HRESULT result = S_OK;

    if (pnames.contains(nameStr)) {
        pnames.removeOne(nameStr);

        ppidnamesLock.lock();
        QMutableMapIterator<unsigned int, QString> iterator(ppidnames);
        while (iterator.hasNext()) {
            iterator.next();

            if (iterator.value().compare(nameStr, Qt::CaseInsensitive) == 0) {
                iterator.remove();
            }
        }
        ppidnamesLock.unlock();
    } else {
        setError(203);
        result = S_FALSE;
    }

    pnamesLock.unlock();
    return result;
}

HRESULT STDMETHODCALLTYPE CProcessMonitorExImpl::unregisterAllNames() {
    pnamesLock.lock();
    pnames.clear();
    pnamesLock.unlock();

    ppidnamesLock.lock();
    ppidnames.clear();
    ppidnamesLock.unlock();
    return S_OK;
}

HRESULT STDMETHODCALLTYPE CProcessMonitorExImpl::getLastError(unsigned int *code,
                                                            LPBSTR msg,
                                                            unsigned int *msglen) {
    // TODO
    lastErrorLock.lock();

    if (code != NULL) {
        *code = this->iLastError;
    }

    if (msg != NULL && msglen != NULL) {
        errorsLock.lock();
        QString qmsg = this->errors.value(this->iLastError, "Unknown error");

        if (lastErrorMsg.length() != 0) {
            qmsg += " [" + lastErrorMsg + "]";
        }

        *msg = new wchar_t[qmsg.size()];
        *msglen = qmsg.toWCharArray(*msg);
        errorsLock.unlock();
    }

    lastErrorLock.unlock();
    return S_OK;
}

void CProcessMonitorExImpl::setError(unsigned int code, QString msg) {
    lastErrorLock.lock();
    errorsLock.lock();
    iLastError = code;
    lastErrorMsg = errors[code] + (msg.length() != 0 ? " [" + msg + "]" : "");
    lastErrorLock.unlock();
    errorsLock.unlock();
}

QString CProcessMonitorExImpl::getLastErrorMsg() {
    LPWSTR bufPtr = NULL;
    DWORD err = GetLastError();
    FormatMessageW(FORMAT_MESSAGE_ALLOCATE_BUFFER |
                   FORMAT_MESSAGE_FROM_SYSTEM |
                   FORMAT_MESSAGE_IGNORE_INSERTS,
                   NULL, err, 0, (LPWSTR)&bufPtr, 0, NULL);
    const QString result =
        (bufPtr) ? QString::fromUtf16((const ushort*)bufPtr).trimmed() :
                   QString("Unknown Error %1").arg(err);
    LocalFree(bufPtr);
    return result;
}
