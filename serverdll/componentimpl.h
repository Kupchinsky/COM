#ifndef COMPONENTIMPL_H
#define COMPONENTIMPL_H

#include "component.h"
#include <QMap>
#include <QList>
#include <QPair>
#include <QMutex>
#include <QMapIterator>
#include <QString>

class CProcessMonitorImpl: public IProcessMonitor, public IProcessMonitorRegistrar {
    long lRefCount = 0;
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

    void setError(unsigned int code, QString msg = "") {
        lastErrorLock.lock();
        iLastError = code;
        lastErrorMsg = msg;
        lastErrorLock.unlock();
    }

    QString getLastErrorMsg() {
        LPWSTR bufPtr = NULL;
        DWORD err = GetLastError();
        FormatMessageW(FORMAT_MESSAGE_ALLOCATE_BUFFER |
                       FORMAT_MESSAGE_FROM_SYSTEM |
                       FORMAT_MESSAGE_IGNORE_INSERTS,
                       NULL, err, 0, (LPWSTR)&bufPtr, 0, NULL);
        const QString result =
            (bufPtr) ? QString::fromUtf16((const ushort*)bufPtr).trimmed() :
                       QString("Unknown Error %1").arg(err);
        LocalFree(bufPtr);
        return result;
    }
public:
    HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void **ppObj);
    ULONG STDMETHODCALLTYPE AddRef();
    ULONG STDMETHODCALLTYPE Release();

    HRESULT STDMETHODCALLTYPE pushPid(unsigned int pid);
    HRESULT STDMETHODCALLTYPE removePid(unsigned int pid);
    HRESULT STDMETHODCALLTYPE clearPids();

    HRESULT STDMETHODCALLTYPE updateStatuses(void);

    HRESULT STDMETHODCALLTYPE getChangedStatusFirst(unsigned int *pid, wchar_t **pname,
                                                    unsigned int *pnamelen, unsigned int *status);
    HRESULT STDMETHODCALLTYPE getChangedStatusNext(unsigned int *pid, wchar_t **pname,
                                                   unsigned int *pnamelen, unsigned int *status);

    HRESULT STDMETHODCALLTYPE getLastError(unsigned int *code, wchar_t **msg, unsigned int *msglen);

    CProcessMonitorImpl() {
        errorsLock.lock();
        errors[0] = "No error";
        errors[101] = "Process with this pid not found";
        errors[102] = "Process with this pid not registered";
        errors[103] = "Process with same pid already registered";
        errors[104] = "Empty parameter";
        errors[105] = "Something went wrong";
        errorsLock.unlock();
    }

    virtual ~CProcessMonitorImpl() {
        if (statusesIterator != NULL) {
            delete statusesIterator;
            statusesIterator = NULL;
        }

        this->clearPids();
    }
};
#endif // COMPONENTIMPL_H
