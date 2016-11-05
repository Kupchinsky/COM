#ifndef COMPONENT1IMPL_H
#define COMPONENT1IMPL_H

#include "component1.h"

class CComponent1Impl: public IComponent1faceX, public IComponent1faceY {
    int iRefCount = 0;
public:
    void methodX1();
    int methodX2();
    double methodX3();

    void methodY1();
    double methodY2();
    int methodY3();

    virtual ~CComponent1Impl() {
    }

    _ULONG AddRef();
    _ULONG Release();
    _HRESULT QueryInterface(_REFIID riid, void **ppvObject);
};

class CComponent1ClassFactory: public IComponent1ClassFactory {
    int iRefCount = 0;
public:
    virtual ~CComponent1ClassFactory() {
    }

    _ULONG AddRef();
    _ULONG Release();
    _HRESULT QueryInterface(_REFIID riid, void **ppvObject);
    _HRESULT CreateInstance(_REFIID riid, void **ppvObject);
};
#endif // COMPONENT1IMPL_H
