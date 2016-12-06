

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.00.0603 */
/* at Tue Dec 06 23:31:05 2016
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

// #pragma warning( disable: 4049 )  /* more than 64k source lines */


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


#ifndef __IProcessMonitor_FWD_DEFINED__
#define __IProcessMonitor_FWD_DEFINED__
typedef interface IProcessMonitor IProcessMonitor;

#endif 	/* __IProcessMonitor_FWD_DEFINED__ */


/* header files for imported files */
#include "unknwn.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IProcessMonitor_INTERFACE_DEFINED__
#define __IProcessMonitor_INTERFACE_DEFINED__

/* interface IProcessMonitor */
/* [object][version][uuid] */ 


EXTERN_C const IID IID_IProcessMonitor;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("2044b06d-c185-4e6e-a4c2-078a5b6f9ed6")
    IProcessMonitor : public IUnknown
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
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE updateStatuses( void) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE getChangedStatusFirst( 
            /* [out] */ unsigned int *pid,
            /* [size_is][size_is][out] */ wchar_t **pname,
            /* [out] */ unsigned int *pnamelen,
            /* [out] */ unsigned int *status) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE getChangedStatusNext( 
            /* [out] */ unsigned int *pid,
            /* [size_is][size_is][out] */ wchar_t **pname,
            /* [out] */ unsigned int *pnamelen,
            /* [out] */ unsigned int *status) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE getLastError( 
            /* [out] */ unsigned int *code,
            /* [size_is][size_is][out] */ wchar_t **msg,
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
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *registerProcessByName )( 
            IProcessMonitor * This,
            wchar_t *name);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *registerProcessByPid )( 
            IProcessMonitor * This,
            unsigned int pid);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *unregisterProcessByName )( 
            IProcessMonitor * This,
            wchar_t *name);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *unregisterProcessByPid )( 
            IProcessMonitor * This,
            unsigned int pid);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *unregisterAllProcesses )( 
            IProcessMonitor * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *updateStatuses )( 
            IProcessMonitor * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *getChangedStatusFirst )( 
            IProcessMonitor * This,
            /* [out] */ unsigned int *pid,
            /* [size_is][size_is][out] */ wchar_t **pname,
            /* [out] */ unsigned int *pnamelen,
            /* [out] */ unsigned int *status);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *getChangedStatusNext )( 
            IProcessMonitor * This,
            /* [out] */ unsigned int *pid,
            /* [size_is][size_is][out] */ wchar_t **pname,
            /* [out] */ unsigned int *pnamelen,
            /* [out] */ unsigned int *status);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *getLastError )( 
            IProcessMonitor * This,
            /* [out] */ unsigned int *code,
            /* [size_is][size_is][out] */ wchar_t **msg,
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


#define IProcessMonitor_registerProcessByName(This,name)	\
    ( (This)->lpVtbl -> registerProcessByName(This,name) ) 

#define IProcessMonitor_registerProcessByPid(This,pid)	\
    ( (This)->lpVtbl -> registerProcessByPid(This,pid) ) 

#define IProcessMonitor_unregisterProcessByName(This,name)	\
    ( (This)->lpVtbl -> unregisterProcessByName(This,name) ) 

#define IProcessMonitor_unregisterProcessByPid(This,pid)	\
    ( (This)->lpVtbl -> unregisterProcessByPid(This,pid) ) 

#define IProcessMonitor_unregisterAllProcesses(This)	\
    ( (This)->lpVtbl -> unregisterAllProcesses(This) ) 

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



#ifndef __ProcessManager_LIBRARY_DEFINED__
#define __ProcessManager_LIBRARY_DEFINED__

/* library ProcessManager */
/* [version][uuid] */ 



EXTERN_C const IID LIBID_ProcessManager;
#endif /* __ProcessManager_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


