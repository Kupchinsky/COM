#ifndef UNKNOWN_H
#define UNKNOWN_H

#define ULONG long
#define HRESULT long

#define IID_IUnknown 0

#define S_OK 0
#define E_NOINTERFACE 1
#define E_INVALIDARG 2

class IUnknownPseudo {
public:
    virtual ULONG AddRef() = 0;
    virtual HRESULT QueryInterface(int riid, void **ppvObject) = 0;
    virtual ULONG Release() = 0;
};

#endif // UNKNOWN_H
