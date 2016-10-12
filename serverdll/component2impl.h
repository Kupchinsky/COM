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
        } else if (riid == IID_IComponent2faceX) {
            *ppvObject = (void**)(IComponent2faceX*)this;
            this->AddRef();
        } else if (riid == IID_IComponent2faceY) {
            *ppvObject = (void**)(IComponent2faceY*)this;
            this->AddRef();
        }

        return *ppvObject != 0 ? S_OK : E_NOINTERFACE;
    }
};

#endif // COMPONENT2IMPL_H
