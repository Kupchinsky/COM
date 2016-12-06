#include "componentimpl.h"
#include "serverdll.h"

HRESULT STDMETHODCALLTYPE CProcessMonitorImpl::QueryInterface(REFIID riid, void **ppvObject) {    
    if (riid == IID_IUnknown) {
        *ppvObject = static_cast<IUnknown*>(this);
        this->AddRef();
        return S_OK;
    } else if (riid == IID_IProcessMonitor) {
        *ppvObject = static_cast<IProcessMonitor*>(this);
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

HRESULT STDMETHODCALLTYPE CProcessMonitorImpl::registerProcessByName(wchar_t *name) {
    setError(0);

    QString nameStr = QString::fromWCharArray(name);

    if (nameStr.length() == 0) {
        setError(106);
        return S_FALSE;
    }

    pnamesLock.lock();

    HRESULT result = S_OK;

    if (pnames.contains(nameStr)) {
        setError(104);
        result = S_FALSE;
    } else {
        pnames.push_back(nameStr);
    }

    pnamesLock.unlock();

    return result;
}

HRESULT STDMETHODCALLTYPE CProcessMonitorImpl::registerProcessByPid(unsigned int pid) {
    setError(101);
    return S_FALSE;
}

HRESULT STDMETHODCALLTYPE CProcessMonitorImpl::unregisterProcessByName(wchar_t *name) {
    return S_OK;
}

HRESULT STDMETHODCALLTYPE CProcessMonitorImpl::unregisterProcessByPid(unsigned int pid) {
    return S_OK;
}

HRESULT STDMETHODCALLTYPE CProcessMonitorImpl::unregisterAllProcesses(void) {
    setError(0);

    pidsLock.lock();
    pids.clear();
    pidsLock.unlock();

    pnamesLock.lock();
    pnames.clear();
    pnamesLock.unlock();
    return S_OK;
}

HRESULT STDMETHODCALLTYPE CProcessMonitorImpl::updateStatuses(void) {
    setError(0);

    statusesLock.lock();
    statuses.clear();

    // TODO: fetch statuses

    statusesLock.unlock();
    return S_OK;
}

HRESULT STDMETHODCALLTYPE CProcessMonitorImpl::getChangedStatusFirst(unsigned int *pid,
                                                                     wchar_t **pname,
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
                                                                    wchar_t **pname,
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

HRESULT STDMETHODCALLTYPE CProcessMonitorImpl::getLastError(unsigned int *code, wchar_t **msg,
                                                            unsigned int *msglen) {
    if (code != NULL) {
        lastErrorLock.lock();
        *code = this->iLastError;
        lastErrorLock.unlock();
    }

    if (msg != NULL) {
        errorsLock.lock();
        QString qmsg = this->errors.value(this->iLastError, "Unknown error");

        *msg = new wchar_t[qmsg.size()];
        *msglen = qmsg.toWCharArray(*msg);
        errorsLock.unlock();
    }

    return S_OK;
}
