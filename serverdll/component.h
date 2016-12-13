

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.00.0603 */
/* at Tue Dec 13 19:11:01 2016
 */
/* Compiler settings for component.idl:
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

#ifndef __component_h__
#define __component_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IProcessMonitor_FWD_DEFINED__
#define __IProcessMonitor_FWD_DEFINED__
typedef interface IProcessMonitor IProcessMonitor;

#endif 	/* __IProcessMonitor_FWD_DEFINED__ */


#ifndef __IProcessMonitorRegistrar_FWD_DEFINED__
#define __IProcessMonitorRegistrar_FWD_DEFINED__
typedef interface IProcessMonitorRegistrar IProcessMonitorRegistrar;

#endif 	/* __IProcessMonitorRegistrar_FWD_DEFINED__ */


#ifndef __IProcessMonitorDisp_FWD_DEFINED__
#define __IProcessMonitorDisp_FWD_DEFINED__
typedef interface IProcessMonitorDisp IProcessMonitorDisp;

#endif 	/* __IProcessMonitorDisp_FWD_DEFINED__ */


#ifndef __IProcessMonitor_FWD_DEFINED__
#define __IProcessMonitor_FWD_DEFINED__
typedef interface IProcessMonitor IProcessMonitor;

#endif 	/* __IProcessMonitor_FWD_DEFINED__ */


#ifndef __IProcessMonitorRegistrar_FWD_DEFINED__
#define __IProcessMonitorRegistrar_FWD_DEFINED__
typedef interface IProcessMonitorRegistrar IProcessMonitorRegistrar;

#endif 	/* __IProcessMonitorRegistrar_FWD_DEFINED__ */


#ifndef __IProcessMonitorDisp_FWD_DEFINED__
#define __IProcessMonitorDisp_FWD_DEFINED__
typedef interface IProcessMonitorDisp IProcessMonitorDisp;

#endif 	/* __IProcessMonitorDisp_FWD_DEFINED__ */


/* header files for imported files */
#include "unknwn.h"
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IProcessMonitor_INTERFACE_DEFINED__
#define __IProcessMonitor_INTERFACE_DEFINED__

/* interface IProcessMonitor */
/* [local][uuid][object] */ 


EXTERN_C const IID IID_IProcessMonitor;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("2044b06d-c185-4e6e-a4c2-078a5b6f9ed6")
    IProcessMonitor : public IUnknown
    {
    public:
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE updateStatuses( void) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE getChangedStatusFirst( 
            /* [out] */ unsigned int *pid,
            /* [size_is][size_is][out] */ LPBSTR pname,
            /* [out] */ unsigned int *pnamelen,
            /* [out] */ unsigned int *status) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE getChangedStatusNext( 
            /* [out] */ unsigned int *pid,
            /* [size_is][size_is][out] */ LPBSTR pname,
            /* [out] */ unsigned int *pnamelen,
            /* [out] */ unsigned int *status) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE getLastError( 
            /* [out] */ unsigned int *code,
            /* [size_is][size_is][out] */ LPBSTR msg,
            /* [out] */ unsigned int *msglen) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IProcessMonitorVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IProcessMonitor * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IProcessMonitor * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IProcessMonitor * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *updateStatuses )( 
            IProcessMonitor * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *getChangedStatusFirst )( 
            IProcessMonitor * This,
            /* [out] */ unsigned int *pid,
            /* [size_is][size_is][out] */ LPBSTR pname,
            /* [out] */ unsigned int *pnamelen,
            /* [out] */ unsigned int *status);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *getChangedStatusNext )( 
            IProcessMonitor * This,
            /* [out] */ unsigned int *pid,
            /* [size_is][size_is][out] */ LPBSTR pname,
            /* [out] */ unsigned int *pnamelen,
            /* [out] */ unsigned int *status);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *getLastError )( 
            IProcessMonitor * This,
            /* [out] */ unsigned int *code,
            /* [size_is][size_is][out] */ LPBSTR msg,
            /* [out] */ unsigned int *msglen);
        
        END_INTERFACE
    } IProcessMonitorVtbl;

    interface IProcessMonitor
    {
        CONST_VTBL struct IProcessMonitorVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IProcessMonitor_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IProcessMonitor_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IProcessMonitor_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IProcessMonitor_updateStatuses(This)	\
    ( (This)->lpVtbl -> updateStatuses(This) ) 

#define IProcessMonitor_getChangedStatusFirst(This,pid,pname,pnamelen,status)	\
    ( (This)->lpVtbl -> getChangedStatusFirst(This,pid,pname,pnamelen,status) ) 

#define IProcessMonitor_getChangedStatusNext(This,pid,pname,pnamelen,status)	\
    ( (This)->lpVtbl -> getChangedStatusNext(This,pid,pname,pnamelen,status) ) 

#define IProcessMonitor_getLastError(This,code,msg,msglen)	\
    ( (This)->lpVtbl -> getLastError(This,code,msg,msglen) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IProcessMonitor_INTERFACE_DEFINED__ */


#ifndef __IProcessMonitorRegistrar_INTERFACE_DEFINED__
#define __IProcessMonitorRegistrar_INTERFACE_DEFINED__

/* interface IProcessMonitorRegistrar */
/* [local][uuid][object] */ 


EXTERN_C const IID IID_IProcessMonitorRegistrar;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("2044b06d-c185-4e6e-a4c2-078a5b6f9ed7")
    IProcessMonitorRegistrar : public IUnknown
    {
    public:
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

    typedef struct IProcessMonitorRegistrarVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IProcessMonitorRegistrar * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IProcessMonitorRegistrar * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IProcessMonitorRegistrar * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *pushPid )( 
            IProcessMonitorRegistrar * This,
            unsigned int pid);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *removePid )( 
            IProcessMonitorRegistrar * This,
            unsigned int pid);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *clearPids )( 
            IProcessMonitorRegistrar * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *getLastError )( 
            IProcessMonitorRegistrar * This,
            /* [out] */ unsigned int *code,
            /* [size_is][size_is][out] */ LPBSTR msg,
            /* [out] */ unsigned int *msglen);
        
        END_INTERFACE
    } IProcessMonitorRegistrarVtbl;

    interface IProcessMonitorRegistrar
    {
        CONST_VTBL struct IProcessMonitorRegistrarVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IProcessMonitorRegistrar_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IProcessMonitorRegistrar_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IProcessMonitorRegistrar_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IProcessMonitorRegistrar_pushPid(This,pid)	\
    ( (This)->lpVtbl -> pushPid(This,pid) ) 

#define IProcessMonitorRegistrar_removePid(This,pid)	\
    ( (This)->lpVtbl -> removePid(This,pid) ) 

#define IProcessMonitorRegistrar_clearPids(This)	\
    ( (This)->lpVtbl -> clearPids(This) ) 

#define IProcessMonitorRegistrar_getLastError(This,code,msg,msglen)	\
    ( (This)->lpVtbl -> getLastError(This,code,msg,msglen) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IProcessMonitorRegistrar_INTERFACE_DEFINED__ */



#ifndef __ProcessManager_LIBRARY_DEFINED__
#define __ProcessManager_LIBRARY_DEFINED__

/* library ProcessManager */
/* [uuid] */ 





EXTERN_C const IID LIBID_ProcessManager;

#ifndef __IProcessMonitorDisp_DISPINTERFACE_DEFINED__
#define __IProcessMonitorDisp_DISPINTERFACE_DEFINED__

/* dispinterface IProcessMonitorDisp */
/* [uuid] */ 


EXTERN_C const IID DIID_IProcessMonitorDisp;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("2044b06d-c185-4e6e-a4c2-078a5b6f9ed8")
    IProcessMonitorDisp : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct IProcessMonitorDispVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IProcessMonitorDisp * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IProcessMonitorDisp * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IProcessMonitorDisp * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IProcessMonitorDisp * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IProcessMonitorDisp * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IProcessMonitorDisp * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IProcessMonitorDisp * This,
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
    } IProcessMonitorDispVtbl;

    interface IProcessMonitorDisp
    {
        CONST_VTBL struct IProcessMonitorDispVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IProcessMonitorDisp_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IProcessMonitorDisp_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IProcessMonitorDisp_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IProcessMonitorDisp_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IProcessMonitorDisp_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IProcessMonitorDisp_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IProcessMonitorDisp_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __IProcessMonitorDisp_DISPINTERFACE_DEFINED__ */

#endif /* __ProcessManager_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


