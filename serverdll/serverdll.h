#ifndef SERVERDLL_H
#define SERVERDLL_H

#include "component.h"
#include "componentimpl.h"
#include "componentfactory.h"
#include "serverdll_global.h"

#include <windows.h>

static HMODULE g_hModule = NULL;
static ULONG g_ObjectsInUse = 0;

#define ProgId "Kupchinskiy.ProcessManager"

extern "C" {
    BOOL APIENTRY DllMain(HANDLE hModule, DWORD dwReason, void* lpReserved);

    HRESULT SERVERDLLSHARED_EXPORT DllRegisterServer();
    HRESULT SERVERDLLSHARED_EXPORT DllUnregisterServer();
    HRESULT SERVERDLLSHARED_EXPORT DllGetClassObject(REFCLSID rclsid, REFIID riid, void **ppv);
    HRESULT SERVERDLLSHARED_EXPORT DllCanUnloadNow();
}
#endif // SERVERDLL_H
