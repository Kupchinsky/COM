#ifndef SERVERDLLEXTEND_H
#define SERVERDLLEXTEND_H

#include "componentex.h"
#include "componenteximpl.h"
#include "componentexfactory.h"
#include "serverdll-extend_global.h"

#include <windows.h>

static HMODULE g_hModule = NULL;
static ULONG g_ObjectsInUse = 0;

#define ProgId "Kupchinskiy.ProcessManagerEx"

extern "C" {
    BOOL APIENTRY DllMain(HANDLE hModule, DWORD dwReason, void* lpReserved);

    HRESULT SERVERDLLEXTENDSHARED_EXPORT DllRegisterServer();
    HRESULT SERVERDLLEXTENDSHARED_EXPORT DllUnregisterServer();
    HRESULT SERVERDLLEXTENDSHARED_EXPORT DllGetClassObject(REFCLSID rclsid, REFIID riid, void **ppv);
    HRESULT SERVERDLLEXTENDSHARED_EXPORT DllCanUnloadNow();
}
#endif // SERVERDLLEXTEND_H
