#include "component2impl.h"
#include <QDebug>

ULONG CComponent2Impl::AddRef() {
    iRefCount++;
    return iRefCount;
}

ULONG CComponent2Impl::Release() {
    iRefCount--;

    if (iRefCount == 0) {
        delete this;
    }

    return iRefCount;
}

HRESULT CComponent2Impl::QueryInterface(int riid, void **ppvObject) {
    if (!ppvObject) {
        return E_INVALIDARG;
    }

    *ppvObject = NULL;

    if (riid == IID_IUnknown) {
        *ppvObject = static_cast<IUnknownPseudo*>(this);
        this->AddRef();
    } else if (riid == IID_IComponent2faceX) {
        *ppvObject = static_cast<IComponent2faceX*>(this);
        this->AddRef();
    } else if (riid == IID_IComponent2faceY) {
        *ppvObject = static_cast<IComponent2faceY*>(this);
        this->AddRef();
    }

    return *ppvObject != NULL ? S_OK : E_NOINTERFACE;
}

void CComponent2Impl::methodX1() {
    qDebug() << "methodX1 in CComponent2Impl called";
}

int CComponent2Impl::methodX2() {
    qDebug() << "methodX2 in CComponent2Impl called";
    return 0;
}

double CComponent2Impl::methodX3() {
    qDebug() << "methodX3 in CComponent2Impl called";
    return 0;
}

void CComponent2Impl::methodY1() {
    qDebug() << "methodY1 in CComponent2Impl called";
}

double CComponent2Impl::methodY2() {
    qDebug() << "methodY2 in CComponent2Impl called";
    return 0;
}

int CComponent2Impl::methodY3() {
    qDebug() << "methodY3 in CComponent2Impl called";
    return 0;
}

ULONG CComponent2ClassFactory::AddRef() {
    iRefCount++;
    return iRefCount;
}

ULONG CComponent2ClassFactory::Release() {
    iRefCount--;

    if (iRefCount == 0) {
        delete this;
    }

    return iRefCount;
}

HRESULT CComponent2ClassFactory::QueryInterface(int riid, void **ppvObject) {
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

HRESULT CComponent2ClassFactory::CreateInstance(int riid, void **ppvObject) {
    if (!ppvObject) {
        return E_INVALIDARG;
    }

    CComponent2Impl *impl = new CComponent2Impl();
    return impl->QueryInterface(riid, ppvObject);
}
