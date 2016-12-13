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

    pnamesLock.lock();

    // Check newly created processes
    if (pnames.size() != 0) {
        PROCESSENTRY32 entry;
        entry.dwSize = sizeof(PROCESSENTRY32);

        HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

        if (Process32First(snapshot, &entry) == TRUE) {
            while (Process32Next(snapshot, &entry) == TRUE) {
                QString pname = QString::fromWCharArray(entry.szExeFile);

                foreach (QString name, pnames) {
                    if (name.compare(pname, Qt::CaseInsensitive) == 0) {
                        qDebug() << LOGTAG << pname << "matches";

                        ppidnames.insert(entry.th32ProcessID, pname);
                        this->pushPid(entry.th32ProcessID);
                        break;
                    }
                }
            }
        }

        CloseHandle(snapshot);
    }

    pnamesLock.unlock();
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

    qDebug() << LOGTAG << "Registering" << nameStr;

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

    qDebug() << LOGTAG << "Unregistering" << nameStr;

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
                this->removePid(iterator.key());
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

    QMapIterator<unsigned int, QString> iterator(ppidnames);
    while (iterator.hasNext()) {
        iterator.next();
        this->removePid(iterator.key());
    }

    ppidnames.clear();
    ppidnamesLock.unlock();
    return S_OK;
}

HRESULT STDMETHODCALLTYPE CProcessMonitorExImpl::getLastError(unsigned int *code,
                                                            LPBSTR msg,
                                                            unsigned int *msglen) {
    unsigned int lastError;
    QString lastErrorMsg;

    lastErrorLock.lock();

    if (this->iLastError == 0) { // No error in extended component, use error data from parent
        wchar_t *errorMsg;
        unsigned int errorMsgLen;

        this->delegatePM->getLastError(&lastError, &errorMsg, &errorMsgLen);
        lastErrorMsg = QString::fromWCharArray(errorMsg, errorMsgLen);
    } else {
        lastError = this->iLastError;

        errorsLock.lock();
        lastErrorMsg = this->errors.value(this->iLastError, "Unknown error");

        if (this->lastErrorMsg.length() != 0) {
            lastErrorMsg += " [" + this->lastErrorMsg + "]";
        }
        errorsLock.unlock();
    }

    lastErrorLock.unlock();

    if (code != NULL) {
        *code = lastError;
    }

    if (msg != NULL && msglen != NULL) {
        *msg = new wchar_t[lastErrorMsg.size()];
        *msglen = lastErrorMsg.toWCharArray(*msg);
    }

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
