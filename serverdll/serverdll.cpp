#include "serverdll.h"

HRESULT SERVERDLLSHARED_EXPORT GetClassObjectPseudo(int rclsid, int riid, void **ppv) {
    if (!ppv) {
        return E_INVALIDARG;
    }

    *ppv = NULL;

    if (rclsid == CLSID_Component1) {
        CComponent1ClassFactory *cf = new CComponent1ClassFactory();
        return cf->QueryInterface(riid, ppv);
    } else if (rclsid == CLSID_Component2) {
        CComponent2ClassFactory *cf = new CComponent2ClassFactory();
        return cf->QueryInterface(riid, ppv);
    }

    return E_NOINTERFACE;
}

HRESULT SERVERDLLSHARED_EXPORT CreateInstancePseudo(int rclsid, int riid, void **ppv) {
   if (!ppv) {
       return E_INVALIDARG;
   }

   *ppv = NULL;

   IClassFactoryPseudo *cf = NULL;
   HRESULT result = GetClassObjectPseudo(rclsid, riid, (void**) &cf);

   if (result != S_OK) {
       return result;
   }

   result = cf->CreateInstance(riid, ppv);
   cf->Release();

   return result;
}
