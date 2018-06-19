

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.00.0603 */
/* at Tue Jun 12 13:46:48 2018
 */
/* Compiler settings for QMPlugin.odl:
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


#ifndef __QMPlugin_h_h__
#define __QMPlugin_h_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IQMPlugin_FWD_DEFINED__
#define __IQMPlugin_FWD_DEFINED__
typedef interface IQMPlugin IQMPlugin;

#endif 	/* __IQMPlugin_FWD_DEFINED__ */


#ifndef __IQMPluginStandard_FWD_DEFINED__
#define __IQMPluginStandard_FWD_DEFINED__
typedef interface IQMPluginStandard IQMPluginStandard;

#endif 	/* __IQMPluginStandard_FWD_DEFINED__ */


#ifndef __File_FWD_DEFINED__
#define __File_FWD_DEFINED__

#ifdef __cplusplus
typedef class File File;
#else
typedef struct File File;
#endif /* __cplusplus */

#endif 	/* __File_FWD_DEFINED__ */


#ifdef __cplusplus
extern "C"{
#endif 



#ifndef __QMPlugin_LIBRARY_DEFINED__
#define __QMPlugin_LIBRARY_DEFINED__

/* library QMPlugin */
/* [version][uuid] */ 


DEFINE_GUID(LIBID_QMPlugin,0xC7CC9058,0x59A4,0x4CE1,0xAC,0xB3,0x4E,0x2C,0x04,0x9E,0x4C,0x31);

#ifndef __IQMPlugin_DISPINTERFACE_DEFINED__
#define __IQMPlugin_DISPINTERFACE_DEFINED__

/* dispinterface IQMPlugin */
/* [uuid] */ 


DEFINE_GUID(DIID_IQMPlugin,0x1E7051CE,0x6430,0x4BA9,0xA9,0x65,0x3E,0xAC,0x6D,0x1A,0xC4,0x22);

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("1E7051CE-6430-4BA9-A965-3EAC6D1AC422")
    IQMPlugin : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct IQMPluginVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IQMPlugin * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IQMPlugin * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IQMPlugin * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IQMPlugin * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IQMPlugin * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IQMPlugin * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IQMPlugin * This,
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
    } IQMPluginVtbl;

    interface IQMPlugin
    {
        CONST_VTBL struct IQMPluginVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IQMPlugin_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IQMPlugin_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IQMPlugin_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IQMPlugin_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IQMPlugin_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IQMPlugin_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IQMPlugin_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __IQMPlugin_DISPINTERFACE_DEFINED__ */


#ifndef __IQMPluginStandard_DISPINTERFACE_DEFINED__
#define __IQMPluginStandard_DISPINTERFACE_DEFINED__

/* dispinterface IQMPluginStandard */
/* [uuid] */ 


DEFINE_GUID(DIID_IQMPluginStandard,0xEE1035BA,0x1025,0x4cde,0xAD,0x4C,0xA0,0x4B,0x38,0x78,0xBF,0x00);

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("EE1035BA-1025-4cde-AD4C-A04B3878BF00")
    IQMPluginStandard : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct IQMPluginStandardVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IQMPluginStandard * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IQMPluginStandard * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IQMPluginStandard * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IQMPluginStandard * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IQMPluginStandard * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IQMPluginStandard * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IQMPluginStandard * This,
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
    } IQMPluginStandardVtbl;

    interface IQMPluginStandard
    {
        CONST_VTBL struct IQMPluginStandardVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IQMPluginStandard_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IQMPluginStandard_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IQMPluginStandard_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IQMPluginStandard_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IQMPluginStandard_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IQMPluginStandard_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IQMPluginStandard_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __IQMPluginStandard_DISPINTERFACE_DEFINED__ */


DEFINE_GUID(CLSID_File,0x57477331,0x126E,0x4FC8,0xB4,0x30,0x1C,0x61,0x43,0x48,0x4A,0xA9);

#ifdef __cplusplus

class DECLSPEC_UUID("57477331-126E-4FC8-B430-1C6143484AA9")
File;
#endif
#endif /* __QMPlugin_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


