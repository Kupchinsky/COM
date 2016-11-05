#ifndef SERVERDLL_H
#define SERVERDLL_H

#include "../unknown.h"
#include "component1.h"
#include "component1impl.h"
#include "component2.h"
#include "component2impl.h"
#include "serverdll_global.h"

extern "C" {
    _HRESULT SERVERDLLSHARED_EXPORT GetClassObjectPseudo(_REFCLSID rclsid, _REFCLSID riid, void **ppv);
    _HRESULT SERVERDLLSHARED_EXPORT CreateInstancePseudo(_REFCLSID rclsid, _REFCLSID riid, void **ppv);
}
#endif // SERVERDLL_H
