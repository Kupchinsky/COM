#ifndef COMPONENTIMPL_H
#define COMPONENTIMPL_H

#include "component.h"

class CProcessMonitorImpl: public IProcessMonitor {
    long lRefCount = 0;
    unsigned int iLastError = 0;
public:
    HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void **ppObj);
    ULONG STDMETHODCALLTYPE AddRef();
    ULONG STDMETHODCALLTYPE Release();

    HRESULT STDMETHODCALLTYPE registerProcessByName(wchar_t *name);
    HRESULT STDMETHODCALLTYPE registerProcessByPid(unsigned int pid);

    HRESULT STDMETHODCALLTYPE unregisterProcessByName(wchar_t *name);
    HRESULT STDMETHODCALLTYPE unregisterProcessByPid(unsigned int pid);

    HRESULT STDMETHODCALLTYPE unregisterAllProcesses(void);
    HRESULT STDMETHODCALLTYPE updateStatuses(void);

    HRESULT STDMETHODCALLTYPE getChangedStatusFirst(unsigned int *pid, wchar_t **pname,
                                                    unsigned int *pnamelen, unsigned int *status);
    HRESULT STDMETHODCALLTYPE getChangedStatusNext(unsigned int *pid, wchar_t **pname,
                                                   unsigned int *pnamelen, unsigned int *status);

    HRESULT STDMETHODCALLTYPE getLastError(unsigned int *code, wchar_t **msg, unsigned int *msglen);

    virtual ~CProcessMonitorImpl() {
    }
};
#endif // COMPONENTIMPL_H
