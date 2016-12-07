

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.00.0603 */
/* at Wed Dec 07 15:13:46 2016
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

#pragma warning( disable: 4049 )  /* more than 64k source lines */


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

#ifndef __IProcessMonitorRegistrarEx_FWD_DEFINED__
#define __IProcessMonitorRegistrarEx_FWD_DEFINED__
typedef interface IProcessMonitorRegistrarEx IProcessMonitorRegistrarEx;

#endif 	/* __IProcessMonitorRegistrarEx_FWD_DEFINED__ */


#ifndef __IProcessMonitorRegistrarEx_FWD_DEFINED__
#define __IProcessMonitorRegistrarEx_FWD_DEFINED__
typedef interface IProcessMonitorRegistrarEx IProcessMonitorRegistrarEx;

#endif 	/* __IProcessMonitorRegistrarEx_FWD_DEFINED__ */


/* header files for imported files */
#include "unknwn.h"

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
    IProcessMonitorRegistrarEx : public IUnknown
    {
    public:
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE registerProcessByName( 
            wchar_t *name) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE registerProcessByPid( 
            unsigned int pid) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE unregisterProcessByName( 
            wchar_t *name) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE unregisterProcessByPid( 
            unsigned int pid) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE unregisterAllProcesses( void) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE getLastError( 
            /* [out] */ unsigned int *code,
            /* [size_is][size_is][out] */ wchar_t **msg,
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
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *registerProcessByName )( 
            IProcessMonitorRegistrarEx * This,
            wchar_t *name);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *registerProcessByPid )( 
            IProcessMonitorRegistrarEx * This,
            unsigned int pid);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *unregisterProcessByName )( 
            IProcessMonitorRegistrarEx * This,
            wchar_t *name);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *unregisterProcessByPid )( 
            IProcessMonitorRegistrarEx * This,
            unsigned int pid);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *unregisterAllProcesses )( 
            IProcessMonitorRegistrarEx * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *getLastError )( 
            IProcessMonitorRegistrarEx * This,
            /* [out] */ unsigned int *code,
            /* [size_is][size_is][out] */ wchar_t **msg,
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


#define IProcessMonitorRegistrarEx_registerProcessByName(This,name)	\
    ( (This)->lpVtbl -> registerProcessByName(This,name) ) 

#define IProcessMonitorRegistrarEx_registerProcessByPid(This,pid)	\
    ( (This)->lpVtbl -> registerProcessByPid(This,pid) ) 

#define IProcessMonitorRegistrarEx_unregisterProcessByName(This,name)	\
    ( (This)->lpVtbl -> unregisterProcessByName(This,name) ) 

#define IProcessMonitorRegistrarEx_unregisterProcessByPid(This,pid)	\
    ( (This)->lpVtbl -> unregisterProcessByPid(This,pid) ) 

#define IProcessMonitorRegistrarEx_unregisterAllProcesses(This)	\
    ( (This)->lpVtbl -> unregisterAllProcesses(This) ) 

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
#endif /* __ProcessManagerEx_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


