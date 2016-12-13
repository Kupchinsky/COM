

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.00.0603 */
/* at Tue Dec 13 22:02:27 2016
 */
/* Compiler settings for componentex.idl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 8.00.0603 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

//#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __componentex_h__
#define __componentex_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IProcessMonitorRegistrarEx_FWD_DEFINED__
#define __IProcessMonitorRegistrarEx_FWD_DEFINED__
typedef interface IProcessMonitorRegistrarEx IProcessMonitorRegistrarEx;

#endif 	/* __IProcessMonitorRegistrarEx_FWD_DEFINED__ */


#ifndef __IProcessMonitorExDispatch_FWD_DEFINED__
#define __IProcessMonitorExDispatch_FWD_DEFINED__
typedef interface IProcessMonitorExDispatch IProcessMonitorExDispatch;

#endif 	/* __IProcessMonitorExDispatch_FWD_DEFINED__ */


#ifndef __IProcessMonitorRegistrarEx_FWD_DEFINED__
#define __IProcessMonitorRegistrarEx_FWD_DEFINED__
typedef interface IProcessMonitorRegistrarEx IProcessMonitorRegistrarEx;

#endif 	/* __IProcessMonitorRegistrarEx_FWD_DEFINED__ */


#ifndef __IProcessMonitorExDispatch_FWD_DEFINED__
#define __IProcessMonitorExDispatch_FWD_DEFINED__
typedef interface IProcessMonitorExDispatch IProcessMonitorExDispatch;

#endif 	/* __IProcessMonitorExDispatch_FWD_DEFINED__ */


/* header files for imported files */
#include "unknwn.h"
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IProcessMonitorRegistrarEx_INTERFACE_DEFINED__
#define __IProcessMonitorRegistrarEx_INTERFACE_DEFINED__

/* interface IProcessMonitorRegistrarEx */
/* [object][version][uuid] */ 


EXTERN_C const IID IID_IProcessMonitorRegistrarEx;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("2044b06d-c185-4e6e-a4c2-078a5b6f9ed0")
    IProcessMonitorRegistrarEx : public IDispatch
    {
    public:
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE registerProcessByName( 
            BSTR name) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE unregisterProcessByName( 
            BSTR name) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE unregisterAllNames( void) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE pushPid( 
            unsigned int pid) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE removePid( 
            unsigned int pid) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE clearPids( void) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE getLastError( 
            /* [out] */ unsigned int *code,
            /* [size_is][size_is][out] */ LPBSTR msg,
            /* [out] */ unsigned int *msglen) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IProcessMonitorRegistrarExVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IProcessMonitorRegistrarEx * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IProcessMonitorRegistrarEx * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IProcessMonitorRegistrarEx * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IProcessMonitorRegistrarEx * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IProcessMonitorRegistrarEx * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IProcessMonitorRegistrarEx * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IProcessMonitorRegistrarEx * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *registerProcessByName )( 
            IProcessMonitorRegistrarEx * This,
            BSTR name);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *unregisterProcessByName )( 
            IProcessMonitorRegistrarEx * This,
            BSTR name);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *unregisterAllNames )( 
            IProcessMonitorRegistrarEx * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *pushPid )( 
            IProcessMonitorRegistrarEx * This,
            unsigned int pid);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *removePid )( 
            IProcessMonitorRegistrarEx * This,
            unsigned int pid);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *clearPids )( 
            IProcessMonitorRegistrarEx * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *getLastError )( 
            IProcessMonitorRegistrarEx * This,
            /* [out] */ unsigned int *code,
            /* [size_is][size_is][out] */ LPBSTR msg,
            /* [out] */ unsigned int *msglen);
        
        END_INTERFACE
    } IProcessMonitorRegistrarExVtbl;

    interface IProcessMonitorRegistrarEx
    {
        CONST_VTBL struct IProcessMonitorRegistrarExVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IProcessMonitorRegistrarEx_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IProcessMonitorRegistrarEx_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IProcessMonitorRegistrarEx_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IProcessMonitorRegistrarEx_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IProcessMonitorRegistrarEx_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IProcessMonitorRegistrarEx_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IProcessMonitorRegistrarEx_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IProcessMonitorRegistrarEx_registerProcessByName(This,name)	\
    ( (This)->lpVtbl -> registerProcessByName(This,name) ) 

#define IProcessMonitorRegistrarEx_unregisterProcessByName(This,name)	\
    ( (This)->lpVtbl -> unregisterProcessByName(This,name) ) 

#define IProcessMonitorRegistrarEx_unregisterAllNames(This)	\
    ( (This)->lpVtbl -> unregisterAllNames(This) ) 

#define IProcessMonitorRegistrarEx_pushPid(This,pid)	\
    ( (This)->lpVtbl -> pushPid(This,pid) ) 

#define IProcessMonitorRegistrarEx_removePid(This,pid)	\
    ( (This)->lpVtbl -> removePid(This,pid) ) 

#define IProcessMonitorRegistrarEx_clearPids(This)	\
    ( (This)->lpVtbl -> clearPids(This) ) 

#define IProcessMonitorRegistrarEx_getLastError(This,code,msg,msglen)	\
    ( (This)->lpVtbl -> getLastError(This,code,msg,msglen) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IProcessMonitorRegistrarEx_INTERFACE_DEFINED__ */



#ifndef __ProcessManagerEx_LIBRARY_DEFINED__
#define __ProcessManagerEx_LIBRARY_DEFINED__

/* library ProcessManagerEx */
/* [version][uuid] */ 




EXTERN_C const IID LIBID_ProcessManagerEx;

#ifndef __IProcessMonitorExDispatch_DISPINTERFACE_DEFINED__
#define __IProcessMonitorExDispatch_DISPINTERFACE_DEFINED__

/* dispinterface IProcessMonitorExDispatch */
/* [uuid] */ 


EXTERN_C const IID DIID_IProcessMonitorExDispatch;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("2044b06d-c185-4e6e-a4c2-078a5b6f9ed1")
    IProcessMonitorExDispatch : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct IProcessMonitorExDispatchVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IProcessMonitorExDispatch * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IProcessMonitorExDispatch * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IProcessMonitorExDispatch * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IProcessMonitorExDispatch * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IProcessMonitorExDispatch * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IProcessMonitorExDispatch * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IProcessMonitorExDispatch * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        END_INTERFACE
    } IProcessMonitorExDispatchVtbl;

    interface IProcessMonitorExDispatch
    {
        CONST_VTBL struct IProcessMonitorExDispatchVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IProcessMonitorExDispatch_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IProcessMonitorExDispatch_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IProcessMonitorExDispatch_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IProcessMonitorExDispatch_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IProcessMonitorExDispatch_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IProcessMonitorExDispatch_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IProcessMonitorExDispatch_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __IProcessMonitorExDispatch_DISPINTERFACE_DEFINED__ */

#endif /* __ProcessManagerEx_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long *, unsigned long            , BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserMarshal(  unsigned long *, unsigned char *, BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserUnmarshal(unsigned long *, unsigned char *, BSTR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long *, BSTR * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


