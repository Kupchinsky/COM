#include "component2impl.h"
#include "serverdll.h"
#include <QDebug>

_ULONG CComponent2Impl::AddRef() {
    iRefCount++;
    IncrementObjectsInUse();

    return iRefCount;
}

_ULONG CComponent2Impl::Release() {
    iRefCount--;
    DecrementObjectsInUse();

    if (iRefCount == 0) {
        delete this;
    }

    return iRefCount;
}

_HRESULT CComponent2Impl::QueryInterface(_REFIID riid, void **ppvObject) {
    if (!ppvObject) {
        return _E_INVALIDARG;
    }

    *ppvObject = NULL;

    if (riid == IID_IUnknownPseudo) {
        *ppvObject = static_cast<IUnknownPseudo*>(this);
        this->AddRef();
    } else if (riid == IID_IComponent2faceX) {
        *ppvObject = static_cast<IComponent2faceX*>(this);
        this->AddRef();
    } else if (riid == IID_IComponent2faceY) {
        *ppvObject = static_cast<IComponent2faceY*>(this);
        this->AddRef();
    }

    return *ppvObject != NULL ? _S_OK : _E_NOINTERFACE;
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

_ULONG CComponent2ClassFactory::AddRef() {
    iRefCount++;
    IncrementObjectsInUse();

    return iRefCount;
}

_ULONG CComponent2ClassFactory::Release() {
    iRefCount--;
    DecrementObjectsInUse();

    if (iRefCount == 0) {
        delete this;
    }

    return iRefCount;
}

_HRESULT CComponent2ClassFactory::QueryInterface(_REFIID riid, void **ppvObject) {
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

_HRESULT CComponent2ClassFactory::CreateInstance(_REFIID riid, void **ppvObject) {
    if (!ppvObject) {
        return _E_INVALIDARG;
    }

    CComponent2Impl *impl = new CComponent2Impl();
    return impl->QueryInterface(riid, ppvObject);
}
