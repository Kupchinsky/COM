#ifndef SERVERDLL_H
#define SERVERDLL_H

#include "../unknown.h"
#include "component1.h"
#include "component1impl.h"
#include "component2.h"
#include "component2impl.h"
#include "serverdll_global.h"

#include <windows.h>

extern "C" {
    BOOL APIENTRY DllMain(HANDLE hModule, DWORD dwReason, void* lpReserved);

    _HRESULT SERVERDLLSHARED_EXPORT DllRegisterServer();
    _HRESULT SERVERDLLSHARED_EXPORT DllUnregisterServer();
    _HRESULT SERVERDLLSHARED_EXPORT DllGetClassObjectPseudo(_REFCLSID rclsid, _REFIID riid, void **ppv);
    _HRESULT SERVERDLLSHARED_EXPORT DllCanUnloadNow();
}
#endif // SERVERDLL_H
