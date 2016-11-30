#ifndef COMPONENTIMPL_H
#define COMPONENTIMPL_H

#include "component.h"

class CProcessMonitorImpl: public IProcessMonitor {
    long lRefCount = 0;
public:
    HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void **ppObj);
    ULONG STDMETHODCALLTYPE AddRef();
    ULONG STDMETHODCALLTYPE Release();

    HRESULT STDMETHODCALLTYPE registerProcessByName(BSTR name);
    HRESULT STDMETHODCALLTYPE registerProcessByPid(unsigned int pid);

    HRESULT STDMETHODCALLTYPE unregisterProcessByName(BSTR name);
    HRESULT STDMETHODCALLTYPE unregisterProcessByPid(unsigned int pid);

    HRESULT STDMETHODCALLTYPE unregisterAllProcesses(void);
    HRESULT STDMETHODCALLTYPE updateStatuses(void);

    HRESULT STDMETHODCALLTYPE getChangedStatusFirst(unsigned int *pid, unsigned int *status);
    HRESULT STDMETHODCALLTYPE getChangedStatusNext(unsigned int *pid, unsigned int *status);

    virtual ~CProcessMonitorImpl() {
    }
};
#endif // COMPONENTIMPL_H
