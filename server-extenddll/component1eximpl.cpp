#include "component1eximpl.h"
#include "serverextenddll.h"
#include <QDebug>
#include <cassert>

CComponentEx1Impl::CComponentEx1Impl() {
    this->hManager = GetModuleHandleA("managerdll.dll");
    assert(this->hManager != NULL);

    this->createInstancePseudo = (Manager_CreateInstancePseudo) GetProcAddress(this->hManager, "CreateInstancePseudo");
    assert(this->createInstancePseudo != NULL);

    this->freeUnusedLibraries = (Manager_FreeUnusedLibraries) GetProcAddress(this->hManager, "FreeUnusedLibraries");
    assert(this->freeUnusedLibraries != NULL);

    IUnknownPseudo *ptr;
    assert(this->createInstancePseudo(CLSID_Component1, IID_IUnknownPseudo, (void**) &ptr) == S_OK);

    assert(ptr->QueryInterface(IID_IComponent1faceX, (void**) &this->delegateX) == S_OK);
    assert(ptr->QueryInterface(IID_IComponent1faceY, (void**) &this->delegateY) == S_OK);

    ptr->Release();
}

CComponentEx1Impl::~CComponentEx1Impl() {
    if (this->delegateX != NULL) {
        this->delegateX->Release();
        this->delegateX = NULL;
    }

    if (this->delegateY != NULL) {
        this->delegateY->Release();
        this->delegateY = NULL;
    }
}

_ULONG CComponentEx1Impl::AddRef() {
    iRefCount++;
    IncrementObjectsInUse();

    return iRefCount;
}

_ULONG CComponentEx1Impl::Release() {
    iRefCount--;
    DecrementObjectsInUse();

    if (iRefCount == 0) {
        delete this;
    }

    return iRefCount;
}

_HRESULT CComponentEx1Impl::QueryInterface(_REFIID riid, void **ppvObject) {
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
    } else if (riid == IID_IComponentEx1face) {
        *ppvObject = static_cast<IComponentEx1face*>(this);
        this->AddRef();
    }

    return *ppvObject != NULL ? _S_OK : _E_NOINTERFACE;
}

void CComponentEx1Impl::methodX1() {
    this->delegateX->methodX1();
}

int CComponentEx1Impl::methodX2() {
    return this->delegateX->methodX2();
}

double CComponentEx1Impl::methodX3() {
    return this->delegateX->methodX3();
}

void CComponentEx1Impl::methodY1() {
    this->delegateY->methodY1();
}

double CComponentEx1Impl::methodY2() {
    return this->delegateY->methodY2();
}

int CComponentEx1Impl::methodY3() {
    return this->delegateY->methodY3();
}

void CComponentEx1Impl::methodX4() {
    qDebug() << "methodX4 in CComponentEx1Impl called";
}

_ULONG CComponentEx1ClassFactory::AddRef() {
    iRefCount++;
    IncrementObjectsInUse();

    return iRefCount;
}

_ULONG CComponentEx1ClassFactory::Release() {
    iRefCount--;
    DecrementObjectsInUse();

    if (iRefCount == 0) {
        delete this;
    }

    return iRefCount;
}

_HRESULT CComponentEx1ClassFactory::QueryInterface(_REFIID riid, void **ppvObject) {
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

_HRESULT CComponentEx1ClassFactory::CreateInstance(_REFIID riid, void **ppvObject) {
    if (!ppvObject) {
        return _E_INVALIDARG;
    }

    CComponentEx1Impl *impl = new CComponentEx1Impl();
    return impl->QueryInterface(riid, ppvObject);
}
