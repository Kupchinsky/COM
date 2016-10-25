#ifndef UNKNOWN_H
#define UNKNOWN_H

#define ULONG long
#define HRESULT long

#define IID_IUnknown 0
#define IID_IClassFactory 1


#undef S_OK
#undef E_NOINTERFACE
#undef E_INVALIDARG

#define S_OK 0
#define E_NOINTERFACE 1
#define E_INVALIDARG 2

class IUnknownPseudo {
public:
    virtual ULONG AddRef() = 0;
    virtual HRESULT QueryInterface(int riid, void **ppvObject) = 0;
    virtual ULONG Release() = 0;
};

class IClassFactoryPseudo : public IUnknownPseudo {
public:
    virtual HRESULT CreateInstance(int riid, void **ppvObject) = 0;
};
#endif // UNKNOWN_H
