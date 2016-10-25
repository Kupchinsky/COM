#ifndef SERVERDLL_H
#define SERVERDLL_H

#include "unknown.h"
#include "component1.h"
#include "component1impl.h"
#include "component2.h"
#include "component2impl.h"
#include "serverdll_global.h"

extern "C" {
    HRESULT SERVERDLLSHARED_EXPORT GetClassObjectPseudo(int rclsid, int riid, void **ppv);
    HRESULT SERVERDLLSHARED_EXPORT CreateInstancePseudo(int rclsid, int riid, void **ppv);
}
#endif // SERVERDLL_H
