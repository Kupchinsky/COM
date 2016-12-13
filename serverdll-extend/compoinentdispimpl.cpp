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
    HRESULT result = S_OK;

    dispIdNamesLock.lock();

    if (dispIdNames.contains(name)) {
        rgDispId[0] = dispIdNames[name];
    } else {
        result = E_NOTIMPL;
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

    if (name == "LastError" && wFlags == DISPATCH_PROPERTYGET) {
        lastErrorLock.lock();
        pVarResult->vt = VT_INT;
        pVarResult->intVal = this->iLastError;
        lastErrorLock.unlock();
    } else if (name == "LastErrorMsg" && wFlags == DISPATCH_PROPERTYGET) {
        lastErrorLock.lock();
        pVarResult->vt = VT_BSTR;

        const wchar_t *cbstr = this->lastErrorMsg.toStdWString().c_str();
        wchar_t *bstr = wcsdup(cbstr);

        pVarResult->bstrVal = bstr;
        lastErrorLock.unlock();
    } else if (name == "pushPid") {
        DISPPARAMS param = *pDispParams;
        VARIANT arg1 = (param.rgvarg)[0];
        HRESULT res = VariantChangeType(&arg1, &arg1, 0, VT_UINT);

        if (res != S_OK) {
            // TODO: generate exception
            *puArgErr = 1;
        }

        this->pushPid(arg1.uintVal);
    } else if (name == "removePid") {
        DISPPARAMS param = *pDispParams;
        VARIANT arg1 = (param.rgvarg)[0];
        HRESULT res = VariantChangeType(&arg1, &arg1, 0, VT_UINT);

        if (res != S_OK) {
            // TODO: generate exception
            *puArgErr = 1;
        }

        this->removePid(arg1.uintVal);
    } else if (name == "clearPids") {
        this->clearPids();
    } else if (name == "updateStatuses") {
        this->updateStatuses();
    } else if (name == "getChangedStatusFirst") {
        // TODO
    } else if (name == "getChangedStatusNext") {
        // TODO
    } else {
        return E_NOTIMPL;
    }

    return S_OK;
}
