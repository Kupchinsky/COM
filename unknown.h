#ifndef UNKNOWN_H
#define UNKNOWN_H

#define _ULONG long
#define _HRESULT long

#define _REFCLSID int
#define _REFIID int

#define IID_IUnknownPseudo 0
#define IID_IClassFactoryPseudo 1

#define _S_OK 0
#define _E_NOINTERFACE 1
#define _E_INVALIDARG 2

class IUnknownPseudo {
public:
    virtual _ULONG AddRef() = 0;
    virtual _HRESULT QueryInterface(_REFIID riid, void **ppvObject) = 0;
    virtual _ULONG Release() = 0;
};

class IClassFactoryPseudo : public IUnknownPseudo {
public:
    virtual _HRESULT CreateInstance(_REFIID riid, void **ppvObject) = 0;
};
#endif // UNKNOWN_H
