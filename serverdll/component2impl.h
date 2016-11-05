#ifndef COMPONENT2IMPL_H
#define COMPONENT2IMPL_H

#include "component2.h"

class CComponent2Impl: public IComponent2faceX, public IComponent2faceY {
    int iRefCount = 0;
public:
    void methodX1();
    int methodX2();
    double methodX3();

    void methodY1();
    double methodY2();
    int methodY3();

    virtual ~CComponent2Impl() {
    }

    _ULONG AddRef();
    _ULONG Release();
    _HRESULT QueryInterface(_REFIID riid, void **ppvObject);
};

class CComponent2ClassFactory: public IComponent2ClassFactory {
    int iRefCount = 0;
public:
    virtual ~CComponent2ClassFactory() {
    }

    _ULONG AddRef();
    _ULONG Release();
    _HRESULT QueryInterface(_REFIID riid, void **ppvObject);
    _HRESULT CreateInstance(_REFIID riid, void **ppvObject);
};
#endif // COMPONENT2IMPL_H
