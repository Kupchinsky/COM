#include "componenteximpl.h"
#include "serverdllextend.h"

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
    } else if (riid == IProcessMonitorRegistrarEx) {
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

}

HRESULT STDMETHODCALLTYPE CProcessMonitorExImpl::registerProcessByPid(unsigned int pid) {

}

HRESULT STDMETHODCALLTYPE CProcessMonitorExImpl::unregisterProcessByName(BSTR name) {

}

HRESULT STDMETHODCALLTYPE CProcessMonitorExImpl::unregisterProcessByPid(unsigned int pid) {

}

HRESULT STDMETHODCALLTYPE CProcessMonitorExImpl::unregisterAllProcesses() {

}

HRESULT STDMETHODCALLTYPE CProcessMonitorExImpl::getLastError(unsigned int *code,
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
