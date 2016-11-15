#ifndef SERVEREXTENDDLL_H
#define SERVEREXTENDDLL_H

#include "server-extenddll_global.h"

#include "../unknown.h"

#include <windows.h>

void IncrementObjectsInUse();
void DecrementObjectsInUse();

extern "C" {
    BOOL APIENTRY DllMain(HANDLE hModule, DWORD dwReason, void* lpReserved);

    _HRESULT SERVEREXTENDDLLSHARED_EXPORT DllRegisterServer();
    _HRESULT SERVEREXTENDDLLSHARED_EXPORT DllUnregisterServer();
    _HRESULT SERVEREXTENDDLLSHARED_EXPORT DllGetClassObjectPseudo(_REFCLSID rclsid, _REFIID riid, void **ppv);
    _HRESULT SERVEREXTENDDLLSHARED_EXPORT DllCanUnloadNow();
}

#endif // SERVEREXTENDDLL_H
