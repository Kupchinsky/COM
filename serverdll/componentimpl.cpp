#include "componentimpl.h"
#include <QDebug>

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
    return S_OK;
}

ULONG STDMETHODCALLTYPE CProcessMonitorImpl::Release() {
    long nRefCount = InterlockedDecrement(&this->lRefCount);

    if (nRefCount == 0) {
        delete this;
    }

    return nRefCount;
}

HRESULT STDMETHODCALLTYPE CProcessMonitorImpl::registerProcessByName(BSTR name) {
    return S_OK;
}

HRESULT STDMETHODCALLTYPE CProcessMonitorImpl::registerProcessByPid(unsigned int pid) {
    return S_OK;
}

HRESULT STDMETHODCALLTYPE CProcessMonitorImpl::unregisterProcessByName(BSTR name) {
    return S_OK;
}

HRESULT STDMETHODCALLTYPE CProcessMonitorImpl::unregisterProcessByPid(unsigned int pid) {
    return S_OK;
}

HRESULT STDMETHODCALLTYPE CProcessMonitorImpl::unregisterAllProcesses(void) {
    return S_OK;
}

HRESULT STDMETHODCALLTYPE CProcessMonitorImpl::updateStatuses(void) {
    return S_OK;
}

HRESULT STDMETHODCALLTYPE CProcessMonitorImpl::getChangedStatusFirst(unsigned int *pid, unsigned int *status) {
    return S_OK;
}

HRESULT STDMETHODCALLTYPE CProcessMonitorImpl::getChangedStatusNext(unsigned int *pid, unsigned int *status) {
    return S_OK;
}
