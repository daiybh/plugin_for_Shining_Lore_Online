

/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


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


#ifdef __cplusplus
extern "C"{
#endif 


#include <rpc.h>
#include <rpcndr.h>

#ifdef _MIDL_USE_GUIDDEF_

#ifndef INITGUID
#define INITGUID
#include <guiddef.h>
#undef INITGUID
#else
#include <guiddef.h>
#endif

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        DEFINE_GUID(name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8)

#else // !_MIDL_USE_GUIDDEF_

#ifndef __IID_DEFINED__
#define __IID_DEFINED__

typedef struct _IID
{
    unsigned long x;
    unsigned short s1;
    unsigned short s2;
    unsigned char  c[8];
} IID;

#endif // __IID_DEFINED__

#ifndef CLSID_DEFINED
#define CLSID_DEFINED
typedef IID CLSID;
#endif // CLSID_DEFINED

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        const type name = {l,w1,w2,{b1,b2,b3,b4,b5,b6,b7,b8}}

#endif !_MIDL_USE_GUIDDEF_

MIDL_DEFINE_GUID(IID, LIBID_QMPlugin,0xC7CC9058,0x59A4,0x4CE1,0xAC,0xB3,0x4E,0x2C,0x04,0x9E,0x4C,0x31);


MIDL_DEFINE_GUID(IID, DIID_IQMPlugin,0x1E7051CE,0x6430,0x4BA9,0xA9,0x65,0x3E,0xAC,0x6D,0x1A,0xC4,0x22);


MIDL_DEFINE_GUID(IID, DIID_IQMPluginStandard,0xEE1035BA,0x1025,0x4cde,0xAD,0x4C,0xA0,0x4B,0x38,0x78,0xBF,0x00);


MIDL_DEFINE_GUID(CLSID, CLSID_File,0x57477331,0x126E,0x4FC8,0xB4,0x30,0x1C,0x61,0x43,0x48,0x4A,0xA9);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif



