#ifndef COMPONENTIMPL_H
#define COMPONENTIMPL_H

#include "componentex.h"
#include "../serverdll/component.h"
#include <QMap>
#include <QList>
#include <QPair>
#include <QMutex>
#include <QMapIterator>
#include <QString>

class CProcessMonitorExImpl:
        public IProcessMonitorExDispatch,
        public IProcessMonitorDisp,
        public IProcessMonitorRegistrarEx,
        public IProcessMonitor,
        public IProcessMonitorRegistrar {
    // Delegates
    IDispatch *delegateDisp;
    IProcessMonitor *delegatePM;
    IProcessMonitorRegistrar *delegatePMR;
    //

    // IUnknown related
    long lRefCount = 0;

    // IDispatch related
    QMap<QString, DISPID> dispIdNames;
    QMutex dispIdNamesLock;

    //
    unsigned int iLastError = 0;
    QString lastErrorMsg;
    QMutex lastErrorLock;

    QMap<unsigned int, QString> errors;
    QMutex errorsLock;

    void setError(unsigned int code, QString msg = "");
    QString getLastErrorMsg();
public:
    // IUnknown related
    HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void **ppObj);
    ULONG STDMETHODCALLTYPE AddRef();
    ULONG STDMETHODCALLTYPE Release();

    // IDispatch related
    HRESULT STDMETHODCALLTYPE GetTypeInfoCount(UINT *pctinfo);
    HRESULT STDMETHODCALLTYPE GetTypeInfo(UINT iTInfo, LCID lcid, ITypeInfo **ppTInfo);
    HRESULT STDMETHODCALLTYPE GetIDsOfNames(REFIID riid, LPOLESTR *rgszNames, UINT cNames, LCID lcid,
                                            DISPID *rgDispId);
    HRESULT STDMETHODCALLTYPE Invoke(DISPID dispIdMember, REFIID riid, LCID lcid, WORD wFlags,
                                     DISPPARAMS *pDispParams, VARIANT *pVarResult, EXCEPINFO *pExcepInfo,
                                     UINT *puArgErr);

    // IProcessMonitorRegistrar
    HRESULT STDMETHODCALLTYPE pushPid(unsigned int pid);
    HRESULT STDMETHODCALLTYPE removePid(unsigned int pid);
    HRESULT STDMETHODCALLTYPE clearPids();

    // IProcessMonitor
    HRESULT STDMETHODCALLTYPE updateStatuses(void);

    HRESULT STDMETHODCALLTYPE getChangedStatusFirst(unsigned int *pid,
                                                    LPBSTR pname,
                                                    unsigned int *pnamelen,
                                                    unsigned int *status);

    HRESULT STDMETHODCALLTYPE getChangedStatusNext(unsigned int *pid,
                                                   LPBSTR pname,
                                                   unsigned int *pnamelen,
                                                   unsigned int *status);

    // IProcessMonitorRegistrarEx new part
    HRESULT STDMETHODCALLTYPE registerProcessByName(BSTR name);
    HRESULT STDMETHODCALLTYPE registerProcessByPid(unsigned int pid);
    HRESULT STDMETHODCALLTYPE unregisterProcessByName(BSTR name);
    HRESULT STDMETHODCALLTYPE unregisterProcessByPid(unsigned int pid);
    HRESULT STDMETHODCALLTYPE unregisterAllProcesses();

    // Shared in IProcessMonitor/IProcessMonitorRegistrar/IProcessMonitorRegistrarEx
    HRESULT STDMETHODCALLTYPE getLastError(unsigned int *code,
                                           LPBSTR msg,
                                           unsigned int *msglen);

    CProcessMonitorExImpl() {
        errorsLock.lock();
        errors[0] = "No error";
        // TODO
        errorsLock.unlock();

        dispIdNamesLock.lock();
        dispIdNames.insert("RegisterProcessByName", 12);
        dispIdNames.insert("RegisterProcessByPid", 13);
        dispIdNames.insert("UnregisterProcessByName", 14);
        dispIdNames.insert("UnregisterProcessByPid", 15);
        dispIdNames.insert("UnregisterAllProcesses", 16);
        dispIdNamesLock.unlock();
    }

    virtual ~CProcessMonitorExImpl() {
        this->delegateDisp->Release();
        this->delegatePM->Release();
        this->delegatePMR->Release();
    }
};
#endif // COMPONENTIMPL_H
