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
        // Fix deleting object of polymorphic class type '...'
        // which has non-virtual destructor might cause undefined behaviour
    }

    ULONG AddRef() {
        iRefCount++;
        return iRefCount;
    }

    ULONG Release() {
        iRefCount--;

        if (iRefCount == 0) {
            delete this;
        }

        return iRefCount;
    }

    HRESULT QueryInterface(int riid, void **ppvObject) {
        if (!ppvObject) {
            return E_INVALIDARG;
        }

        *ppvObject = 0;

        if (riid == IID_IUnknown)
        {
            *ppvObject = (void**)this;
            this->AddRef();
        } else if (riid == IID_IComponent1faceX) {
            *ppvObject = (void**)(IComponent1faceX*)this;
            this->AddRef();
        } else if (riid == IID_IComponent1faceY) {
            *ppvObject = (void**)(IComponent1faceY*)this;
            this->AddRef();
        }

        return *ppvObject != 0 ? S_OK : E_NOINTERFACE;
    }
};

#endif // COMPONENT1IMPL_H
