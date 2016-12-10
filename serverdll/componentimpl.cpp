#include "componentimpl.h"
#include "serverdll.h"
#include <tlhelp32.h>
#include <psapi.h>
#include <QDebug>
#include <QFileInfo>

HRESULT STDMETHODCALLTYPE CProcessMonitorImpl::QueryInterface(REFIID riid, void **ppvObject) {    
    if (riid == IID_IUnknown) {
        *ppvObject = static_cast<IUnknown*>(static_cast<IProcessMonitor*>(this));
        this->AddRef();
        return S_OK;
    } else if (riid == IID_IDispatch) {
        *ppvObject = static_cast<IDispatch*>(static_cast<IProcessMonitor*>(this));
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
    }

    *ppvObject = NULL;
    return E_NOINTERFACE;
}

ULONG STDMETHODCALLTYPE CProcessMonitorImpl::AddRef() {
    InterlockedIncrement(&this->lRefCount);
    InterlockedIncrement(&g_ObjectsInUse);
    return S_OK;
}

ULONG STDMETHODCALLTYPE CProcessMonitorImpl::Release() {
    long nRefCount = InterlockedDecrement(&this->lRefCount);
    InterlockedDecrement(&g_ObjectsInUse);

    if (nRefCount == 0) {
        delete this;
    }

    return nRefCount;
}

HRESULT STDMETHODCALLTYPE CProcessMonitorImpl::pushPid(unsigned int pid) {
    setError(0);

    if (pid == 0) {
        setError(104);
        return S_FALSE;
    }

    pidsLock.lock();

    HRESULT result = S_OK;

    if (pids.contains(pid)) {
        setError(103);
        result = S_FALSE;
    } else {
        HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION, FALSE, pid);

        if (hProcess == NULL) {
            setError(101, getLastErrorMsg());
            result = S_FALSE;
        } else {
            ppidnamesLock.lock();
            wchar_t *pname = new wchar_t[MAX_PATH];
            long pnameLen;
            pnameLen = GetProcessImageFileNameW(hProcess, pname, MAX_PATH);
            if (pnameLen != 0) {
                QString ppathStr = QString::fromWCharArray(pname, pnameLen);
                QFileInfo fileInfo(ppathStr);
                ppidnames.insert(pid, fileInfo.fileName());

                pids.push_back(pid);

                phandlesLock.lock();
                phandles.insert(pid, hProcess);
                phandlesLock.unlock();
            } else {
                setError(105, "GetProcessImageFileNameW fails with " + getLastErrorMsg());
                result = S_FALSE;

                CloseHandle(hProcess);
            }

            delete[] pname;
            ppidnamesLock.unlock();
        }
    }

    pidsLock.unlock();
    return result;
}

HRESULT STDMETHODCALLTYPE CProcessMonitorImpl::removePid(unsigned int pid) {
    setError(0);

    if (pid == 0) {
        setError(104);
        return S_FALSE;
    }

    pidsLock.lock();

    HRESULT result = S_OK;

    if (pids.contains(pid)) {
        pids.removeOne(pid);

        oldStatusesLock.lock();
        oldStatuses.remove(pid);
        oldStatusesLock.unlock();

        phandlesLock.lock();

        if (phandles.contains(pid)) {
            CloseHandle(phandles[pid]);
            phandles.remove(pid);
        }

        phandlesLock.unlock();

        ppidnamesLock.lock();
        ppidnames.remove(pid);
        ppidnamesLock.unlock();
    } else {
        setError(102);
        result = S_FALSE;
    }

    pidsLock.unlock();
    return result;
}

HRESULT STDMETHODCALLTYPE CProcessMonitorImpl::clearPids() {
    setError(0);

    pidsLock.lock();
    pids.clear();
    pidsLock.unlock();

    oldStatusesLock.lock();
    oldStatuses.clear();
    oldStatusesLock.unlock();

    phandlesLock.lock();
    foreach (HANDLE hProcess, phandles) {
        CloseHandle(hProcess);
    }
    phandles.clear();
    phandlesLock.unlock();

    statusesLock.lock();
    if (statusesIterator != NULL) {
        delete statusesIterator;
        statusesIterator = NULL;
    }
    statuses.clear();
    statusesLock.unlock();

    ppidnamesLock.lock();
    ppidnames.clear();
    ppidnamesLock.unlock();

    return S_OK;
}

HRESULT STDMETHODCALLTYPE CProcessMonitorImpl::updateStatuses(void) {
    setError(0);

    statusesLock.lock();
    pidsLock.lock();
    oldStatusesLock.lock();
    phandlesLock.lock();
    ppidnamesLock.lock();

    statuses.clear();

    if (statusesIterator != NULL) {
        delete statusesIterator;
        statusesIterator = NULL;
    }

    QString errMsg;

    // Check all opened handles
    QMutableMapIterator<unsigned int, HANDLE> iterator(phandles);
    while (iterator.hasNext()) {
        iterator.next();

        unsigned int pid = iterator.key();
        HANDLE hProcess = iterator.value();
        DWORD status;

        qDebug() << "Process" << pid;

        if (GetExitCodeProcess(hProcess, &status) == TRUE) {
            bool isChanged = false;

            if (oldStatuses.contains(pid)) {
                qDebug() << "Old status" << oldStatuses[pid];

                if (oldStatuses[pid] != status) {
                    qDebug() << "Changed" << status;
                    isChanged = true;
                    oldStatuses[pid] = status;
                }
            } else {
                qDebug() << "No old status -> changed" << status;
                isChanged = true;
                oldStatuses.insert(pid, status);
            }

            if (isChanged) {
                statuses.insert(pid, QPair<unsigned int, QString>(status, ppidnames[pid]));

                if (status != STILL_ACTIVE) {
                    CloseHandle(hProcess);

                    qDebug() << "Removed" << ppidnames[pid] << pid;

                    oldStatuses.remove(pid);
                    ppidnames.remove(pid);

                    iterator.remove();
                }
            }
        } else {
            errMsg += "\r\nProcessId " + QString::number(pid) +
                    ": GetExitCodeProcess fails with " + getLastErrorMsg();
        }
    }

    if (errMsg.length() != 0) {
        setError(105, errMsg);
    }

    statusesLock.unlock();
    pidsLock.unlock();
    oldStatusesLock.unlock();
    phandlesLock.unlock();
    ppidnamesLock.unlock();
    return S_OK;
}

HRESULT STDMETHODCALLTYPE CProcessMonitorImpl::getChangedStatusFirst(unsigned int *pid,
                                                                     LPBSTR pname,
                                                                     unsigned int *pnamelen,
                                                                     unsigned int *status) {
    setError(0);

    statusesLock.lock();

    if (statusesIterator != NULL) {
        delete statusesIterator;
    }

    statusesIterator = new QMapIterator<unsigned int, QPair<unsigned int, QString>>(this->statuses);

    HRESULT result = S_FALSE;

    if (statusesIterator->hasNext()) {
        statusesIterator->next();

        QString pnameStr = statusesIterator->value().second;

        *pid = statusesIterator->key();
        *pname = new wchar_t[pnameStr.size()];
        *pnamelen = pnameStr.toWCharArray(*pname);
        *status = statusesIterator->value().first;

        result = S_OK;
    }

    statusesLock.unlock();
    return result;
}

HRESULT STDMETHODCALLTYPE CProcessMonitorImpl::getChangedStatusNext(unsigned int *pid,
                                                                    LPBSTR pname,
                                                                    unsigned int *pnamelen,
                                                                    unsigned int *status) {
    setError(0);

    statusesLock.lock();

    HRESULT result = S_FALSE;

    if (statusesIterator != NULL && statusesIterator->hasNext()) {
        statusesIterator->next();

        QString pnameStr = statusesIterator->value().second;

        *pid = statusesIterator->key();
        *pname = new wchar_t[pnameStr.size()];
        *pnamelen = pnameStr.toWCharArray(*pname);
        *status = statusesIterator->value().first;

        result = S_OK;
    }

    statusesLock.unlock();
    return result;
}

HRESULT STDMETHODCALLTYPE CProcessMonitorImpl::getLastError(unsigned int *code,
                                                            LPBSTR msg,
                                                            unsigned int *msglen) {
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

void CProcessMonitorImpl::setError(unsigned int code, QString msg) {
    lastErrorLock.lock();
    iLastError = code;
    lastErrorMsg = msg;
    lastErrorLock.unlock();
}

QString CProcessMonitorImpl::getLastErrorMsg() {
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
