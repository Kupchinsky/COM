#include "component1impl.h"
#include <QDebug>

_ULONG CComponent1Impl::AddRef() {
    iRefCount++;
    return iRefCount;
}

_ULONG CComponent1Impl::Release() {
    iRefCount--;

    if (iRefCount == 0) {
        delete this;
    }

    return iRefCount;
}

_HRESULT CComponent1Impl::QueryInterface(_REFIID riid, void **ppvObject) {
    if (!ppvObject) {
        return _E_INVALIDARG;
    }

    *ppvObject = NULL;

    if (riid == IID_IUnknownPseudo) {
        *ppvObject = static_cast<IUnknownPseudo*>(this);
        this->AddRef();
    } else if (riid == IID_IComponent1faceX) {
        *ppvObject = static_cast<IComponent1faceX*>(this);
        this->AddRef();
    } else if (riid == IID_IComponent1faceY) {
        *ppvObject = static_cast<IComponent1faceY*>(this);
        this->AddRef();
    }

    return *ppvObject != NULL ? _S_OK : _E_NOINTERFACE;
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

_ULONG CComponent1ClassFactory::AddRef() {
    iRefCount++;
    return iRefCount;
}

_ULONG CComponent1ClassFactory::Release() {
    iRefCount--;

    if (iRefCount == 0) {
        delete this;
    }

    return iRefCount;
}

_HRESULT CComponent1ClassFactory::QueryInterface(_REFIID riid, void **ppvObject) {
    if (!ppvObject) {
        return _E_INVALIDARG;
    }

    *ppvObject = NULL;

    if (riid == IID_IUnknownPseudo || riid == IID_IClassFactoryPseudo) {
        *ppvObject = static_cast<IClassFactoryPseudo*>(this);
        this->AddRef();
    }

    return *ppvObject != NULL ? _S_OK : _E_NOINTERFACE;
}

_HRESULT CComponent1ClassFactory::CreateInstance(_REFIID riid, void **ppvObject) {
    if (!ppvObject) {
        return _E_INVALIDARG;
    }

    CComponent1Impl *impl = new CComponent1Impl();
    return impl->QueryInterface(riid, ppvObject);
}
