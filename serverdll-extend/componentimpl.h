#ifndef COMPONENTIMPL_H
#define COMPONENTIMPL_H

#include "component.h"
#include <QMap>
#include <QList>
#include <QPair>
#include <QMutex>
#include <QMapIterator>
#include <QString>

class CProcessMonitorImpl:
        public IProcessMonitorDisp,
        public IProcessMonitor,
        public IProcessMonitorRegistrar {
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

    QList<unsigned int> pids;
    QMutex pidsLock;

    QMap<unsigned int, QPair<unsigned int, QString>> statuses;
    QMapIterator<unsigned int, QPair<unsigned int, QString>> *statusesIterator = NULL;
    QMutex statusesLock;

    QMap<unsigned int, unsigned int> oldStatuses;
    QMutex oldStatusesLock;

    QMap<unsigned int, HANDLE> phandles;
    QMutex phandlesLock;

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

    // IProcessMonitor
    HRESULT STDMETHODCALLTYPE pushPid(unsigned int pid);
    HRESULT STDMETHODCALLTYPE removePid(unsigned int pid);
    HRESULT STDMETHODCALLTYPE clearPids();

    HRESULT STDMETHODCALLTYPE updateStatuses(void);

    HRESULT STDMETHODCALLTYPE getChangedStatusFirst(unsigned int *pid,
                                                    LPBSTR pname,
                                                    unsigned int *pnamelen,
                                                    unsigned int *status);

    HRESULT STDMETHODCALLTYPE getChangedStatusNext(unsigned int *pid,
                                                   LPBSTR pname,
                                                   unsigned int *pnamelen,
                                                   unsigned int *status);

    // Shared in IProcessMonitor/IProcessMonitorRegistrar
    HRESULT STDMETHODCALLTYPE getLastError(unsigned int *code,
                                           LPBSTR msg,
                                           unsigned int *msglen);

    CProcessMonitorImpl() {
        errorsLock.lock();
        errors[0] = "No error";
        errors[101] = "Process with this pid not found";
        errors[102] = "Process with this pid not registered";
        errors[103] = "Process with same pid already registered";
        errors[104] = "Empty parameter";
        errors[105] = "Something went wrong";
        errorsLock.unlock();

        dispIdNamesLock.lock();
        dispIdNames.insert("LastError", 1);
        dispIdNames.insert("LastErrorMsg", 2);
        dispIdNames.insert("pushPid", 3);
        dispIdNames.insert("removePid", 4);
        dispIdNames.insert("clearPids", 5);
        dispIdNames.insert("updateStatuses", 6);
        dispIdNames.insert("getChangedStatusFirst", 7);
        dispIdNames.insert("getChangedStatusNext", 8);
        dispIdNamesLock.unlock();
    }

    virtual ~CProcessMonitorImpl() {
        if (statusesIterator != NULL) {
            delete statusesIterator;
            statusesIterator = NULL;
        }

        // Close handles
        this->clearPids();
    }
};
#endif // COMPONENTIMPL_H
