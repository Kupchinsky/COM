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
