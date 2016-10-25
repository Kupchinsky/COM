#include "component1impl.h"
#include <QDebug>

ULONG CComponent1Impl::AddRef() {
    iRefCount++;
    return iRefCount;
}

ULONG CComponent1Impl::Release() {
    iRefCount--;

    if (iRefCount == 0) {
        delete this;
    }

    return iRefCount;
}

HRESULT CComponent1Impl::QueryInterface(int riid, void **ppvObject) {
    if (!ppvObject) {
        return E_INVALIDARG;
    }

    *ppvObject = NULL;

    if (riid == IID_IUnknown) {
        *ppvObject = static_cast<IUnknownPseudo*>(this);
        this->AddRef();
    } else if (riid == IID_IComponent1faceX) {
        *ppvObject = static_cast<IComponent1faceX*>(this);
        this->AddRef();
    } else if (riid == IID_IComponent1faceY) {
        *ppvObject = static_cast<IComponent1faceY*>(this);
        this->AddRef();
    }

    return *ppvObject != NULL ? S_OK : E_NOINTERFACE;
}

void CComponent1Impl::methodX1() {
    qDebug() << "methodX1 in CComponent1Impl called";
}

int CComponent1Impl::methodX2() {
    qDebug() << "methodX2 in CComponent1Impl called";
    return 0;
}

double CComponent1Impl::methodX3() {
    qDebug() << "methodX3 in CComponent1Impl called";
    return 0;
}

void CComponent1Impl::methodY1() {
    qDebug() << "methodY1 in CComponent1Impl called";
}

double CComponent1Impl::methodY2() {
    qDebug() << "methodY2 in CComponent1Impl called";
    return 0;
}

int CComponent1Impl::methodY3() {
    qDebug() << "methodY3 in CComponent1Impl called";
    return 0;
}

ULONG CComponent1ClassFactory::AddRef() {
    iRefCount++;
    return iRefCount;
}

ULONG CComponent1ClassFactory::Release() {
    iRefCount--;

    if (iRefCount == 0) {
        delete this;
    }

    return iRefCount;
}

HRESULT CComponent1ClassFactory::QueryInterface(int riid, void **ppvObject) {
    if (!ppvObject) {
        return E_INVALIDARG;
    }

    *ppvObject = NULL;

    if (riid == IID_IUnknown || riid == IID_IClassFactory) {
        *ppvObject = static_cast<IClassFactoryPseudo*>(this);
        this->AddRef();
    }

    return *ppvObject != NULL ? S_OK : E_NOINTERFACE;
}

HRESULT CComponent1ClassFactory::CreateInstance(int riid, void **ppvObject) {
    if (!ppvObject) {
        return E_INVALIDARG;
    }

    CComponent1Impl *impl = new CComponent1Impl();
    return impl->QueryInterface(riid, ppvObject);
}
