#include "serverdll.h"

_HRESULT SERVERDLLSHARED_EXPORT GetClassObjectPseudo(_REFCLSID rclsid, _REFIID riid, void **ppv) {
    if (!ppv) {
        return _E_INVALIDARG;
    }

    *ppv = NULL;

    if (rclsid == CLSID_Component1) {
        CComponent1ClassFactory *cf = new CComponent1ClassFactory();
        return cf->QueryInterface(riid, ppv);
    } else if (rclsid == CLSID_Component2) {
        CComponent2ClassFactory *cf = new CComponent2ClassFactory();
        return cf->QueryInterface(riid, ppv);
    }

    return _E_NOINTERFACE;
}

_HRESULT SERVERDLLSHARED_EXPORT CreateInstancePseudo(_REFCLSID rclsid, _REFIID riid, void **ppv) {
   if (!ppv) {
       return _E_INVALIDARG;
   }

   *ppv = NULL;

   IClassFactoryPseudo *cf = NULL;
   _HRESULT result = GetClassObjectPseudo(rclsid, IID_IClassFactoryPseudo, (void**) &cf);

   if (result != _S_OK) {
       return result;
   }

   result = cf->CreateInstance(riid, ppv);
   cf->Release();

   return result;
}
