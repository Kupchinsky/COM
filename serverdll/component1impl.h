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

    ULONG AddRef();
    ULONG Release();
    HRESULT QueryInterface(int riid, void **ppvObject);
};
#endif // COMPONENT1IMPL_H
