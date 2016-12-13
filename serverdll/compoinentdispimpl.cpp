#include "componentimpl.h"

HRESULT STDMETHODCALLTYPE CProcessMonitorImpl::GetTypeInfoCount(UINT *pctinfo) {
    *pctinfo = 0;
    return S_OK;
}

HRESULT STDMETHODCALLTYPE CProcessMonitorImpl::GetTypeInfo(UINT iTInfo, LCID lcid, ITypeInfo **ppTInfo) {
    *ppTInfo = NULL;
    return DISP_E_BADINDEX;
}

HRESULT STDMETHODCALLTYPE CProcessMonitorImpl::GetIDsOfNames(REFIID riid, LPOLESTR *rgszNames, UINT cNames,
                                                             LCID lcid, DISPID *rgDispId) {
    if (riid != IID_NULL) {
        return DISP_E_UNKNOWNINTERFACE;
    }

    if (cNames != 1) {
        return E_NOTIMPL;
    }

    QString name = QString::fromWCharArray(rgszNames[0]);
    HRESULT result = E_NOTIMPL;

    dispIdNamesLock.lock();

    QMapIterator<QString, DISPID> iterator(dispIdNames);

    while (iterator.hasNext()) {
        iterator.next();

        if (QString::compare(iterator.key(), name, Qt::CaseInsensitive) == 0) {
            rgDispId[0] = iterator.value();
            result = S_OK;

            break;
        }
    }

    dispIdNamesLock.unlock();
    return result;
}

HRESULT STDMETHODCALLTYPE CProcessMonitorImpl::Invoke(DISPID dispIdMember, REFIID riid, LCID lcid, WORD wFlags,
                                                      DISPPARAMS *pDispParams, VARIANT *pVarResult,
                                                      EXCEPINFO *pExcepInfo, UINT *puArgErr) {
    if (riid != IID_NULL) {
        return DISP_E_UNKNOWNINTERFACE;
    }

    dispIdNamesLock.lock();
    QString name = dispIdNames.key(dispIdMember, "");
    dispIdNamesLock.unlock();

    bool isBoolResult = false;
    HRESULT result;

    if (QString::compare(name, "LastError", Qt::CaseInsensitive) == 0) {
        lastErrorLock.lock();
        pVarResult->vt = VT_I2;
        pVarResult->iVal = this->iLastError;
        lastErrorLock.unlock();
    } else if (QString::compare(name, "LastErrorMsg", Qt::CaseInsensitive) == 0) {
        lastErrorLock.lock();
        pVarResult->vt = VT_BSTR;
        pVarResult->bstrVal = SysAllocString(this->lastErrorMsg.toStdWString().c_str());
        lastErrorLock.unlock();
    } else if (QString::compare(name, "StatusPid", Qt::CaseInsensitive) == 0) {
        if (pVarResult != NULL) {
            dispCurrentStatusLock.lock();
            pVarResult->vt = VT_I2;
            pVarResult->iVal = this->dispCurrentStatusPid;
            dispCurrentStatusLock.unlock();
        }
    } else if (QString::compare(name, "StatusPname", Qt::CaseInsensitive) == 0) {
        dispCurrentStatusLock.lock();
        pVarResult->vt = VT_BSTR;
        pVarResult->bstrVal = SysAllocString(this->dispCurrentStatusPname.toStdWString().c_str());
        dispCurrentStatusLock.unlock();
    } else if (QString::compare(name, "Status", Qt::CaseInsensitive) == 0) {
        if (pVarResult != NULL) {
            dispCurrentStatusLock.lock();
            pVarResult->vt = VT_I2;
            pVarResult->iVal = this->dispCurrentStatus;
            dispCurrentStatusLock.unlock();
        }
    } else if (QString::compare(name, "pushPid", Qt::CaseInsensitive) == 0) {
        DISPPARAMS param = *pDispParams;
        VARIANT arg1 = (param.rgvarg)[0];
        HRESULT res = VariantChangeType(&arg1, &arg1, 0, VT_UINT);

        if (res != S_OK) {
            *puArgErr = 1;
            this->setError(106, "1");
        } else {
            isBoolResult = true;
            result = this->pushPid(arg1.uintVal);
        }
    } else if (QString::compare(name, "removePid", Qt::CaseInsensitive) == 0) {
        DISPPARAMS param = *pDispParams;
        VARIANT arg1 = (param.rgvarg)[0];
        HRESULT res = VariantChangeType(&arg1, &arg1, 0, VT_UINT);

        if (res != S_OK) {
            *puArgErr = 1;
            this->setError(106, "1");
        } else {
            isBoolResult = true;
            result = this->removePid(arg1.uintVal);
        }
    } else if (QString::compare(name, "clearPids", Qt::CaseInsensitive) == 0) {
        isBoolResult = true;
        result = this->clearPids();
    } else if (QString::compare(name, "updateStatuses", Qt::CaseInsensitive) == 0) {
        isBoolResult = true;
        result = this->updateStatuses();
    } else if (QString::compare(name, "getChangedStatusFirst", Qt::CaseInsensitive) == 0) {
        isBoolResult = true;
        wchar_t *pname;
        unsigned int pnameLen;

        result = this->getChangedStatusFirst(&this->dispCurrentStatusPid,
                                             &pname, &pnameLen,
                                             &this->dispCurrentStatus);

        if (result == S_OK) {
            this->dispCurrentStatusPname = QString::fromWCharArray(pname, pnameLen);
        }
    } else if (QString::compare(name, "getChangedStatusNext", Qt::CaseInsensitive) == 0) {
        isBoolResult = true;
        wchar_t *pname;
        unsigned int pnameLen;

        result = this->getChangedStatusNext(&this->dispCurrentStatusPid,
                                             &pname, &pnameLen,
                                             &this->dispCurrentStatus);

        if (result == S_OK) {
            this->dispCurrentStatusPname = QString::fromWCharArray(pname, pnameLen);
        }
    } else {
        return E_NOTIMPL;
    }

    if (isBoolResult && pVarResult != NULL) {
        pVarResult->vt = VT_BOOL;
        pVarResult->boolVal = result == S_OK ? VARIANT_TRUE : VARIANT_FALSE;
    }

    return S_OK;
}
