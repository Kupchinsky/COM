#ifndef COMPONENT1EXIMPL_H
#define COMPONENT1EXIMPL_H

#include "../pseudo_definitions.h"
#include "../serverdll/component1.h"
#include "component1ex.h"
#include <windows.h>

class CComponentEx1Impl: public IComponentEx1face {
    HMODULE hManager;

    Manager_CreateInstancePseudo createInstancePseudo;
    Manager_FreeUnusedLibraries freeUnusedLibraries;

    IComponent1faceX *delegateX;
    IComponent1faceY *delegateY;

    int iRefCount = 0;
public:
    void methodX1();
    int methodX2();
    double methodX3();

    void methodY1();
    double methodY2();
    int methodY3();

    void methodX4();

    CComponentEx1Impl();
    virtual ~CComponentEx1Impl();

    _ULONG AddRef();
    _ULONG Release();
    _HRESULT QueryInterface(_REFIID riid, void **ppvObject);
};

class CComponentEx1ClassFactory: public IComponentEx1ClassFactory {
    int iRefCount = 0;
public:
    virtual ~CComponentEx1ClassFactory() {
    }

    _ULONG AddRef();
    _ULONG Release();
    _HRESULT QueryInterface(_REFIID riid, void **ppvObject);
    _HRESULT CreateInstance(_REFIID riid, void **ppvObject);
};
#endif // COMPONENT1EXIMPL_H
