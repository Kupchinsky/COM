#include "serverdll.h"
#include <windows.h>

static HMODULE g_hModule = NULL;
static ULONG g_ObjectsInUse = 0;

BOOL APIENTRY DllMain(HANDLE hModule, DWORD dwReason, void* lpReserved) {
    if (dwReason == DLL_PROCESS_ATTACH) {
        g_hModule = (HMODULE) hModule;
    }

    return TRUE;
}

HRESULT SERVERDLLSHARED_EXPORT DllRegisterServer() {
    char szBuff[MAX_PATH];
    GetModuleFileNameA(g_hModule, szBuff, sizeof(szBuff));

    // TODO

    return S_OK;
}

HRESULT SERVERDLLSHARED_EXPORT DllUnregisterServer() {
    // TODO

    return S_OK;
}

HRESULT SERVERDLLSHARED_EXPORT DllGetClassObject(REFCLSID rclsid, REFIID riid, void **ppv) {
    if (!ppv) {
        return E_INVALIDARG;
    }

    *ppv = NULL;

    // TODO

    return CLASS_E_CLASSNOTAVAILABLE;
}

HRESULT SERVERDLLSHARED_EXPORT DllCanUnloadNow() {
    return g_ObjectsInUse == 0 ? S_OK : S_FALSE;
}
