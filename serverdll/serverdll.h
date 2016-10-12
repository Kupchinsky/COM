#ifndef SERVERDLL_H
#define SERVERDLL_H

#include "unknown.h"
#include "component1.h"
#include "component1impl.h"
#include "component2.h"
#include "component2impl.h"
#include "serverdll_global.h"

HRESULT SERVERDLLSHARED_EXPORT CreateInstancePseudo(int rclsid, int riid, void **ppv) {
    if (!ppv) {
        return E_INVALIDARG;
    }

    *ppv = NULL;

    if (rclsid == CLSID_Component1) {
        if (riid == IID_IUnknown) {
            CComponent1Impl *ptr = new CComponent1Impl();
            ptr->AddRef();
            *ppv = (void**)ptr;
        } else if (riid == IID_IComponent1faceX) {
            CComponent1Impl *ptr = new CComponent1Impl();
            ptr->AddRef();
            *ppv = (void**)(IComponent1faceX*)ptr;
        } else if (riid == IID_IComponent1faceY) {
            CComponent1Impl *ptr = new CComponent1Impl();
            ptr->AddRef();
            *ppv = (void**)(IComponent1faceY*)ptr;
        }
    } else if (rclsid == CLSID_Component2) {
        if (riid == IID_IUnknown) {
            CComponent2Impl *ptr = new CComponent2Impl();
            ptr->AddRef();
            *ppv = (void**)ptr;
        } else if (riid == IID_IComponent2faceX) {
            CComponent2Impl *ptr = new CComponent2Impl();
            ptr->AddRef();
            *ppv = (void**)(IComponent2faceX*)ptr;
        } else if (riid == IID_IComponent2faceY) {
            CComponent2Impl *ptr = new CComponent2Impl();
            ptr->AddRef();
            *ppv = (void**)(IComponent2faceY*)ptr;
        }
    }

    return *ppv != NULL ? S_OK : E_NOINTERFACE;
}

#endif // SERVERDLL_H
