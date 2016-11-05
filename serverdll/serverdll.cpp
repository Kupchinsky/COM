#include "serverdll.h"
#include "../localregistry.h"

#include <windows.h>
#include <QJsonValue>
#include <QDebug>

static HMODULE g_hModule = NULL;
static _ULONG g_ObjectsInUse = 0;

void IncrementObjectsInUse() {
    g_ObjectsInUse++;
}

void DecrementObjectsInUse() {
    g_ObjectsInUse--;

    if (g_ObjectsInUse < 0) {
        qDebug() << "g_ObjectsInUse < 0, something went wrong";
    }
}

BOOL APIENTRY DllMain(HANDLE hModule, DWORD dwReason, void* lpReserved) {
    if (dwReason == DLL_PROCESS_ATTACH) {
        g_hModule = (HMODULE) hModule;
    }

    return TRUE;
}

_HRESULT SERVERDLLSHARED_EXPORT DllRegisterServer() {
    CLocalRegistry *registry = CLocalRegistry::getInstance().get();
    QJsonObject jsonObject = registry->getRoot();

    char szBuff[MAX_PATH];
    GetModuleFileNameA(g_hModule, szBuff, sizeof(szBuff));

    jsonObject.insert(QString::number(CLSID_Component1), QJsonValue(szBuff));
    jsonObject.insert(QString::number(CLSID_Component2), QJsonValue(szBuff));

    registry->write();
    return _S_OK;
}

_HRESULT SERVERDLLSHARED_EXPORT DllUnregisterServer() {
    CLocalRegistry *registry = CLocalRegistry::getInstance().get();
    QJsonObject jsonObject = registry->getRoot();

    jsonObject.remove(QString::number(CLSID_Component1));
    jsonObject.remove(QString::number(CLSID_Component2));

    registry->write();
    return _S_OK;
}

_HRESULT SERVERDLLSHARED_EXPORT DllGetClassObjectPseudo(_REFCLSID rclsid, _REFIID riid, void **ppv) {
    if (!ppv) {
        return _E_INVALIDARG;
    }

    *ppv = NULL;

    if (rclsid == CLSID_Component1) {
        CComponent1ClassFactory *cf = new CComponent1ClassFactory();
        return cf->QueryInterface(riid, ppv);
    } else if (rclsid == CLSID_Component2) {
        CComponent2ClassFactory *cf = new CComponent2ClassFactory();
        return cf->QueryInterface(riid, ppv);
    }

    return _E_CLASSNOTAVAILABLE;
}

_HRESULT SERVERDLLSHARED_EXPORT DllCanUnloadNow() {
    return g_ObjectsInUse == 0 ? _S_OK : _S_FALSE;
}
