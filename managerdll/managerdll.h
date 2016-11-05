#ifndef MANAGERDLL_H
#define MANAGERDLL_H

#include "managerdll_global.h"
#include "../unknown.h"

extern "C" {
    _HRESULT MANAGERDLLSHARED_EXPORT GetClassObjectPseudo(_REFCLSID rclsid, _REFIID riid, void **ppv);
    _HRESULT MANAGERDLLSHARED_EXPORT CreateInstancePseudo(_REFCLSID rclsid, _REFIID riid, void **ppv);
    void MANAGERDLLSHARED_EXPORT FreeUnusedLibraries();
}
#endif // MANAGERDLL_H
