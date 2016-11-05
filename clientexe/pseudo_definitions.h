#ifndef PSEUDO_DEFINITIONS_H
#define PSEUDO_DEFINITIONS_H

#include "../unknown.h"
#include <QString>

// Server dll
typedef _HRESULT __stdcall (*Server_DllRegisterServer)();
typedef _HRESULT __stdcall (*Server_DllUnregisterServer)();
typedef _HRESULT __stdcall (*Server_DllGetClassObjectPseudo)(_REFCLSID rclsid, _REFIID riid, void **ppv);
typedef _HRESULT __stdcall (*Server_DllCanUnloadNow)();

// Manager dll
typedef _HRESULT __stdcall (*Manager_GetClassObjectPseudo)(_REFCLSID rclsid, _REFIID riid, void **ppv);
typedef _HRESULT __stdcall (*Manager_CreateInstancePseudo)(_REFCLSID rclsid, _REFIID riid, void **ppv);
typedef void __stdcall (*Manager_FreeUnusedLibraries)();

class InvalidResultException: public QException {
    _HRESULT result;
public:
    InvalidResultException();
    QString what();
};

void checkResult(_HRESULT result);

#endif // PSEUDO_DEFINITIONS_H
