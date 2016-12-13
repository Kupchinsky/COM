#ifndef COMPONENTIMPL_H
#define COMPONENTIMPL_H

#include "componentex.h"
#include "../serverdll/component.h"
#include <QMap>
#include <QList>
#include <QMutex>
#include <QString>

#define LOGTAG "CProcessMonitorExImpl >>"

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

    QList<QString> pnames;
    QMutex pnamesLock;

    QMap<unsigned int, QString> ppidnames;
    QMutex ppidnamesLock;

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
    HRESULT STDMETHODCALLTYPE unregisterProcessByName(BSTR name);
    HRESULT STDMETHODCALLTYPE unregisterAllNames();

    // Shared in IProcessMonitor/IProcessMonitorRegistrar/IProcessMonitorRegistrarEx
    HRESULT STDMETHODCALLTYPE getLastError(unsigned int *code,
                                           LPBSTR msg,
                                           unsigned int *msglen);

    CProcessMonitorExImpl() {
        IUnknown *iUnk;

        if (CoCreateInstance(LIBID_ProcessManager, NULL, CLSCTX_INPROC_SERVER,
                         IID_IUnknown, (void**) &iUnk) != S_OK) {
            throw "CoCreateInstance failed";
        }

        if (iUnk->QueryInterface(IID_IDispatch, (void **) &this->delegateDisp) != S_OK) {
            throw "QueryInterface failed for IID_IDispatch";
        }

        if (iUnk->QueryInterface(IID_IProcessMonitor, (void **) &this->delegatePM) != S_OK) {
            throw "QueryInterface failed for IID_IProcessMonitor";
        }

        if (iUnk->QueryInterface(IID_IProcessMonitorRegistrar, (void **) &this->delegatePMR) != S_OK) {
            throw "QueryInterface failed for IID_IProcessMonitorRegistrar";
        }

        iUnk->Release();

        errorsLock.lock();
        errors[0] = "No error";
        errors[203] = "This process name pattern isn't registered";
        errors[204] = "Process with same pid already registered";
        errors[205] = "This process name pattern is already registered";
        errors[206] = "Empty parameter";
        errorsLock.unlock();

        dispIdNamesLock.lock();
        dispIdNames.insert("UpdateStatuses", 9);
        dispIdNames.insert("RegisterProcessByName", 12);
        dispIdNames.insert("UnregisterProcessByName", 13);
        dispIdNames.insert("UnregisterAllNames", 14);
        dispIdNamesLock.unlock();
    }

    virtual ~CProcessMonitorExImpl() {
        this->delegateDisp->Release();
        this->delegatePM->Release();
        this->delegatePMR->Release();
    }
};
#endif // COMPONENTIMPL_H
