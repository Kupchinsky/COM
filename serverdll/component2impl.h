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

    ULONG AddRef();
    ULONG Release();
    HRESULT QueryInterface(int riid, void **ppvObject);
};

#endif // COMPONENT2IMPL_H
