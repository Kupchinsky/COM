#ifndef CPROCESSMONITORIMPLFACTORY_H
#define CPROCESSMONITORIMPLFACTORY_H

#include "componentex.h"
#include "componenteximpl.h"

class CProcessMonitorExImplFactory: public IClassFactory
{
    long lRefCount = 0;
public:
    HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void **ppObj);
    ULONG STDMETHODCALLTYPE AddRef();
    ULONG STDMETHODCALLTYPE Release();

    HRESULT STDMETHODCALLTYPE CreateInstance(IUnknown* pUnknownOuter, const IID& iid, void** ppv);
    HRESULT STDMETHODCALLTYPE LockServer(BOOL bLock);

    virtual ~CProcessMonitorExImplFactory() {
    }
};

#endif // CPROCESSMONITORIMPLFACTORY_H
