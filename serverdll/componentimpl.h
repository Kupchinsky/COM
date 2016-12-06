#ifndef COMPONENTIMPL_H
#define COMPONENTIMPL_H

#include "component.h"
#include <QMap>
#include <QList>
#include <QPair>

class CProcessMonitorImpl: public IProcessMonitor {
    long lRefCount = 0;
    unsigned int iLastError = 0;
    QMap<unsigned int, QString> errors;
    QList<unsigned int> pids;
    QList<QString> pnames;
    QMap<unsigned int, QPair<unsigned int, QString>> statuses;
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

    CProcessMonitorImpl() {
        errors[0] = "No error";
        errors[101] = "Process with this pid not found";
        errors[102] = "Process with this pid not registered";
        errors[103] = "This process name pattern isn't registered";
        errors[104] = "Process with same pid already registered";
        errors[105] = "This process name pattern is already registered";
    }

    virtual ~CProcessMonitorImpl() {
    }
};
#endif // COMPONENTIMPL_H
