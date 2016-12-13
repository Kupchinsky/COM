#include "componentfactory.h"
#include "serverdllextend.h"

HRESULT STDMETHODCALLTYPE CProcessMonitorExImplFactory::QueryInterface(REFIID riid, void **ppvObject) {
    if (riid == IID_IUnknown) {
        *ppvObject = static_cast<IUnknown*>(this);
        this->AddRef();
        return S_OK;
    } else if (riid == IID_IClassFactory) {
        *ppvObject = static_cast<IClassFactory*>(this);
        this->AddRef();
        return S_OK;
    }

    *ppvObject = NULL;
    return E_NOINTERFACE;
}

ULONG STDMETHODCALLTYPE CProcessMonitorExImplFactory::AddRef() {
    InterlockedIncrement(&this->lRefCount);
    InterlockedIncrement(&g_ObjectsInUse);
    return S_OK;
}

ULONG STDMETHODCALLTYPE CProcessMonitorExImplFactory::Release() {
    long nRefCount = InterlockedDecrement(&this->lRefCount);
    InterlockedDecrement(&g_ObjectsInUse);

    if (nRefCount == 0) {
        delete this;
    }

    return nRefCount;
}

HRESULT STDMETHODCALLTYPE CProcessMonitorExImplFactory::CreateInstance(IUnknown* pUnknownOuter, const IID& iid, void** ppv) {
    if (pUnknownOuter != NULL) {
        return CLASS_E_NOAGGREGATION;
    }

    CProcessMonitorExImpl *impl = new CProcessMonitorExImpl();
    return impl->QueryInterface(iid, ppv);
}

HRESULT STDMETHODCALLTYPE CProcessMonitorExImplFactory::LockServer(BOOL bLock) {
    return E_NOTIMPL;
}
