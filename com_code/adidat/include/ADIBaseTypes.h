

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 7.00.0500 */
/* Compiler settings:
    Oicf, W1, Zp8, env=Win32 (32b run)
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
//@@MIDL_FILE_HEADING(  )

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


#ifndef __ADIBaseTypes_midl_h__
#define __ADIBaseTypes_midl_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include "Utility/ADIIDLStuff.h"

/* Forward Declarations */ 

/* header files for imported files */
#include "wtypes.h"
#include "oaidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


/* interface __MIDL_itf_ADIBaseTypes_0000_0000 */
/* [local] */ 

#if 0
typedef signed small int8;

typedef short int16;

typedef long int32;

typedef hyper int64;

typedef unsigned small uint8;

typedef unsigned short uint16;

typedef unsigned long uint32;

typedef MIDL_uhyper uint64;

#endif
typedef unsigned long ulong;

typedef const OLECHAR *CONST_BSTR;

typedef unsigned short ushort;

typedef unsigned int uint;


enum AutoBoolValues
    {	kAutoFalse	= 0,
	kAutoTrue	= -1
    } ;
#ifndef __cplusplus
typedef VARIANT_BOOL AutoBool;

#else
#pragma pack(push,1)
 struct AutoBool                                                                           
 {                                                                                         
 VARIANT_BOOL X;                                                                            
 AutoBool () {X = kAutoFalse;}                                                              
 AutoBool (bool x) {X = x ? kAutoTrue : kAutoFalse;}                                        
 AutoBool (AutoBoolValues x) {X = x;}                                                       
 AutoBool (const AutoBool &x) {X = x.X ? kAutoTrue : kAutoFalse;}                           
 AutoBool &operator = (const AutoBool &x) {X = x.X ? kAutoTrue : kAutoFalse; return *this;} 
 AutoBool &operator = (bool x) {X = x ? kAutoTrue : kAutoFalse; return *this;}              
 AutoBool &operator = (AutoBoolValues x) {X = x ? kAutoTrue : kAutoFalse; return *this;}    
 AutoBool &operator |= (AutoBoolValues x) {X |= x; return *this;}                           
 AutoBool &operator &= (AutoBoolValues x) {X &= x; return *this;}                           
 bool operator == (AutoBoolValues x) const {return (X==0) == (x==0);}
 bool operator != (AutoBoolValues x) const {return (X==0) != (x==0);}
 AutoBoolValues operator ! () {return X == 0 ? kAutoTrue : kAutoFalse;}                     
 operator bool () const {return X !=0 ;}                         
 };                                                                                         
#pragma pack(pop)
#endif
typedef const GUID ConstGUID;

// int8, int16, int32, uint8, uint16, uint32

#include "CrossPlatform/Utility/CrossTypes.h" 

typedef uint32 TGenericFlags;

typedef uint32 TEnumCount;

typedef int32 TCount;

typedef uint32 TUCount;

typedef uint64 ADIStreamSize;

typedef uint32 TCAFIdRep;

#ifndef __cplusplus
typedef /* [public] */ TCAFIdRep TCAFId;

#else
struct TCAFId
{
TCAFIdRep mRep;
TCAFId(TCAFIdRep rep = 0) {mRep = rep;}
TCAFIdRep& Val() {return mRep;}
TCAFIdRep Val() const {return mRep;}
bool operator == (const TCAFId& other) const {return mRep == other.mRep;}
bool operator != (const TCAFId& other) const {return mRep != other.mRep;}
bool operator < (const TCAFId& other) const {return mRep < other.mRep;}
bool operator > (const TCAFId& other) const {return mRep > other.mRep;}
bool operator <= (const TCAFId& other) const {return mRep <= other.mRep;}
bool operator >= (const TCAFId& other) const {return mRep >= other.mRep;}
bool IsNil() const {return mRep==0;}
};
#endif
typedef TCAFId TTypeId;

#if defined(PUBLIC_OEM_UTIL) || !defined(__cplusplus)
#if defined(__cplusplus)
struct ADIRational64
{//C.f. Boost rational template 
   int64 num; ///< Numerator
   int64 den; ///< Denominator (> 0)
ADIRational64(int64 numIn = 0, int64 denIn = 1): num(numIn),den(denIn){}
};
#else
typedef struct ADIRational64
    {
    int64 num;
    int64 den;
    } 	ADIRational64;

#endif
#else
 }//extern C 
 #include "Utility/ADIRationalDecl.h" 
 #include <boost/static_assert.hpp> 
 namespace ADIRationalChecks                                          
 {                                                                    
 BOOST_STATIC_ASSERT(sizeof(ADIRational64) == 2*sizeof(int64));          
 }
 extern "C" {
#endif
typedef ADIRational64 ADIRational;

#ifndef __cplusplus
typedef struct ADIComplexDouble
    {
    double mReal;
    double mImag;
    } 	ADIComplexDouble;

#else
 }//extern C 
 #include <complex> 
 typedef std::complex<double> ADIComplexDouble; 
#if !defined(PUBLIC_OEM_UTIL) && defined(__cplusplus)
 #include <boost/static_assert.hpp> 
 namespace ADIComplexChecks
 { 
 BOOST_STATIC_ASSERT(sizeof(ADIComplexDouble) == 2*sizeof(double)); 
 }
#endif
 extern "C" {
#endif
typedef ADIComplexDouble ADIComplex;

typedef long TTickIndex;

typedef int64 TTickIndex64;

typedef uint32 TUTickIndex;



extern RPC_IF_HANDLE __MIDL_itf_ADIBaseTypes_0000_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_ADIBaseTypes_0000_0000_v0_0_s_ifspec;

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


