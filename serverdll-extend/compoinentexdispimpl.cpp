#include "componenteximpl.h"

HRESULT STDMETHODCALLTYPE CProcessMonitorExImpl::GetTypeInfoCount(UINT *pctinfo) {
    *pctinfo = 0;
    return S_OK;
}

HRESULT STDMETHODCALLTYPE CProcessMonitorExImpl::GetTypeInfo(UINT iTInfo, LCID lcid, ITypeInfo **ppTInfo) {
    *ppTInfo = NULL;
    return DISP_E_BADINDEX;
}

HRESULT STDMETHODCALLTYPE CProcessMonitorExImpl::GetIDsOfNames(REFIID riid, LPOLESTR *rgszNames, UINT cNames,
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

    if (result == E_NOTIMPL) {
        result = this->delegateDisp->GetIDsOfNames(riid, rgszNames, cNames, lcid, rgDispId);
    }

    return result;
}

HRESULT STDMETHODCALLTYPE CProcessMonitorExImpl::Invoke(DISPID dispIdMember, REFIID riid, LCID lcid, WORD wFlags,
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
    } else if (QString::compare(name, "RegisterProcessByName", Qt::CaseInsensitive) == 0) {
        DISPPARAMS param = *pDispParams;
        VARIANT arg1 = (param.rgvarg)[0];
        HRESULT res = VariantChangeType(&arg1, &arg1, 0, VT_BSTR);

        if (res != S_OK) {
            *puArgErr = 1;
            this->setError(206, "1");
        } else {
            isBoolResult = true;
            result = this->registerProcessByName(arg1.bstrVal);
        }
    } else if (QString::compare(name, "UnregisterProcessByName", Qt::CaseInsensitive) == 0) {
        DISPPARAMS param = *pDispParams;
        VARIANT arg1 = (param.rgvarg)[0];
        HRESULT res = VariantChangeType(&arg1, &arg1, 0, VT_BSTR);

        if (res != S_OK) {
            *puArgErr = 1;
            this->setError(206, "1");
        } else {
            isBoolResult = true;
            result = this->unregisterProcessByName(arg1.bstrVal);
        }
    } else if (QString::compare(name, "UnregisterAllNames", Qt::CaseInsensitive) == 0) {
        isBoolResult = true;
        result = this->unregisterAllNames();
    } else if (QString::compare(name, "UpdateStatuses", Qt::CaseInsensitive) == 0) {
        isBoolResult = true;
        result = this->updateStatuses();
    } else if (QString::compare(name, "ClearPids", Qt::CaseInsensitive) == 0) {
        isBoolResult = true;
        result = this->clearPids();
    } else if (QString::compare(name, "RemovePid", Qt::CaseInsensitive) == 0) {
        DISPPARAMS param = *pDispParams;
        VARIANT arg1 = (param.rgvarg)[0];
        HRESULT res = VariantChangeType(&arg1, &arg1, 0, VT_UINT);

        if (res != S_OK) {
            *puArgErr = 1;
            this->setError(206, "1");
        } else {
            isBoolResult = true;
            result = this->removePid(arg1.uintVal);
        }
    } else {
        return this->delegateDisp->Invoke(dispIdMember, riid, lcid, wFlags, pDispParams,
                                          pVarResult, pExcepInfo, puArgErr);
    }

    if (isBoolResult && pVarResult != NULL) {
        pVarResult->vt = VT_BOOL;
        pVarResult->boolVal = result == S_OK ? VARIANT_TRUE : VARIANT_FALSE;
    }

    return S_OK;
}
