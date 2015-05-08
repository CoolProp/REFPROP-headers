
#ifndef REFPROP_LIB_H
#define REFPROP_LIB_H

// The idea here is to have a common header for Windows 
// and Linux systems. The Windows branch should cover the
// functions provided by the .dll and the Linux part covers
// the compiled .so file. Name changes caused by gfortran 
// are respected and should be accounted for. 

/* See http://stackoverflow.com/a/148610
 * See http://stackoverflow.com/questions/147267/easy-way-to-use-variables-of-enum-types-as-string-in-c#202511
 * This will be used to generate function names, pointers, etc. below
 */
#define LIST_OF_REFPROP_FUNCTION_NAMES \
    X(RPVersion) \
    X(SETPATHdll) \
    X(ABFL1dll) \
    X(ABFL2dll) \
    X(ACTVYdll) \
    X(AGdll) \
    X(CCRITdll) \
    X(CP0dll) \
    X(CRITPdll) \
    X(CSATKdll) \
    X(CV2PKdll) \
    X(CVCPKdll) \
    X(CVCPdll) \
    X(DBDTdll) \
    X(DBFL1dll) \
    X(DBFL2dll) \
    X(DDDPdll) \
    X(DDDTdll) \
    X(DEFLSHdll) \
    X(DHD1dll) \
    X(DHFL1dll) \
    X(DHFLSHdll) \
    X(DIELECdll) \
    X(DOTFILLdll) \
    X(DPDD2dll) \
    X(DPDDKdll) \
    X(DPDDdll) \
    X(DPDTKdll) \
    X(DPDTdll) \
    X(DPTSATKdll) \
    X(DSFLSHdll) \
    X(DSFL1dll) \
    X(ENTHALdll) \
    X(ENTROdll) \
    X(ESFLSHdll) \
    X(FGCTYdll) \
    X(FUGCOFdll) \
    X(FPVdll) \
    X(GERG04dll) \
    X(GETFIJdll) \
    X(GETKTVdll) \
    X(GIBBSdll) \
    X(HSFLSHdll) \
    X(INFOdll) \
    X(LIMITKdll) \
    X(LIMITSdll) \
    X(LIMITXdll) \
    X(MELTPdll) \
    X(MELTTdll) \
    X(MLTH2Odll) \
    X(NAMEdll) \
    X(PASSCMNdll) \
    X(PDFL1dll) \
    X(PDFLSHdll) \
    X(PEFLSHdll) \
    X(PHFL1dll) \
    X(PHFLSHdll) \
    X(PHIXdll) \
    X(PHI0dll) \
    X(PQFLSHdll) \
    X(PREOSdll) \
    X(PRESSdll) \
    X(PSFL1dll) \
    X(PSFLSHdll) \
    X(PUREFLDdll) \
    X(QMASSdll) \
    X(QMOLEdll) \
    X(RESIDUALdll) \
    X(REDXdll) \
    X(RMIX2dll) \
    X(SATDdll) \
    X(SATEdll) \
    X(SATHdll) \
    X(SATPdll) \
    X(SATSdll) \
    X(SATTdll) \
    X(SATTPdll) \
    X(SATSPLNdll) \
    X(SETAGAdll) \
    X(SETKTVdll) \
    X(SETMIXdll) \
    X(SETMODdll) \
    X(SETREFdll) \
    X(SETUPdll) \
    X(SPLNVALdll) \
    X(SUBLPdll) \
    X(SUBLTdll) \
    X(SURFTdll) \
    X(SURTENdll) \
    X(TDFLSHdll) \
    X(TEFLSHdll) \
    X(THERM0dll) \
    X(THERM2dll) \
    X(THERM3dll) \
    X(THERMdll) \
    X(THFLSHdll) \
    X(TPFLSHdll) \
    X(TPFL2dll) \
    X(TPRHOdll) \
    X(TQFLSHdll) \
    X(TRNPRPdll) \
    X(TSFLSHdll) \
    X(VIRBdll) \
    X(VIRCdll) \
    X(WMOLdll) \
    X(XMASSdll) \
    X(XMOLEdll)
    
// Some constants for REFPROP... defined by macros for ease of use
#define refpropcharlength 255
#define filepathlength 255
#define lengthofreference 3
#define errormessagelength 255
#define ncmax 20
#define numparams 72
#define maxcoefs 50

// Get the platform identifiers, some overlap with "PlatformDetermination.h" from CoolProp's main repo 
// See also http://stackoverflow.com/questions/5919996/how-to-detect-reliably-mac-os-x-ios-linux-windows-in-c-preprocessor
#if defined(_WIN32) || defined(__WIN32__) || defined(_WIN64) || defined(__WIN64__)
#    define __RPISWINDOWS__
#elif defined(__APPLE__)
#    define __RPISAPPLE__
#elif defined(__linux) || defined(__unix) || defined(__posix)
#    define __RPISLINUX__
#elif defined(__powerpc__)
#    define __RPISPOWERPC__
#else
#    pragma error
#endif

// Define compiler specific calling conventions
// for the shared library.
#if defined(__RPISWINDOWS__)
#    define RPCALLCONV __stdcall
#else
#    define RPCALLCONV
#endif

// define new macros for function names
// http://stackoverflow.com/questions/195975/how-to-make-a-char-string-from-a-c-macros-value
#include <string.h>
#define STR_VALUE(arg)      #arg
#define FUNCTION_NAME(name) STR_VALUE(name)
#define STRINGIFY(name) STR_VALUE(name)

// In C++, references are done using double &, and in C, using double *
// C++ can use C-style references or pointers
// C can only use pointers
#if !defined(__cplusplus) || defined(REFPROP_CSTYLE_REFERENCES)
	// For C compilation, must do double *, long * since C doesn't understand double &, long &
	#define DOUBLE_REF double *
	#define LONG_REF long *
#else
	#define DOUBLE_REF double &
	#define LONG_REF long &
#endif

// I'll try to follow this example from:
// http://www.gershnik.com/tips/cpp.asp
// function type: typedef void [compiler stuff]  func_t(int, float);
// function declaration: func_t func;
// pointer type: typedef func_t * func_ptr;
#ifdef __cplusplus
extern "C" {
#endif

    // For C calling conventions, replaced all "double &" with "double *", and "long &" with "long *"
    
    #define ABFL1dll_ARGS DOUBLE_REF,DOUBLE_REF,double *,LONG_REF,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,LONG_REF,char*,long 
    #define ABFL2dll_ARGS DOUBLE_REF,DOUBLE_REF,double *,LONG_REF,LONG_REF,char*,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,double *,double *,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,double *,double *,DOUBLE_REF,LONG_REF,char*,long,long 
    #define ACTVYdll_ARGS DOUBLE_REF,DOUBLE_REF,double *,double *,double *,LONG_REF, char *, long
    #define AGdll_ARGS DOUBLE_REF,DOUBLE_REF,double *,DOUBLE_REF,DOUBLE_REF
	// B12
	// Blcrvdll
    #define CCRITdll_ARGS DOUBLE_REF,DOUBLE_REF,double *,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,LONG_REF,char*,long
	// CHEMPOT
    #define CP0dll_ARGS DOUBLE_REF, double *, DOUBLE_REF
	#define CRITPdll_ARGS double *,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,LONG_REF,char*,long 
    #define CSATKdll_ARGS LONG_REF,DOUBLE_REF,LONG_REF,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,LONG_REF,char*,long 
	// Cstar
    #define CV2PKdll_ARGS LONG_REF,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,LONG_REF,char*,long 
    #define CVCPdll_ARGS DOUBLE_REF,DOUBLE_REF,double *,DOUBLE_REF,DOUBLE_REF
	#define CVCPKdll_ARGS LONG_REF,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF
    #define DBDTdll_ARGS DOUBLE_REF,double *,DOUBLE_REF
    #define DBFL1dll_ARGS DOUBLE_REF,DOUBLE_REF,double *,char *,DOUBLE_REF,DOUBLE_REF,LONG_REF,char*,long, long
    #define DBFL2dll_ARGS DOUBLE_REF,DOUBLE_REF,double *,LONG_REF,char *,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,double *,double *,DOUBLE_REF,LONG_REF,char*,long, long    
	#define DDDPdll_ARGS DOUBLE_REF,DOUBLE_REF,double *,DOUBLE_REF
    #define DDDTdll_ARGS DOUBLE_REF,DOUBLE_REF,double *,DOUBLE_REF
	// DEFL1dll
    #define DEFLSHdll_ARGS DOUBLE_REF,DOUBLE_REF,double *,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,double *,double *,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,LONG_REF,char*,long 
    #define DHD1dll_ARGS DOUBLE_REF,DOUBLE_REF,double *,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF
	#define DHFL1dll_ARGS DOUBLE_REF,DOUBLE_REF,double *,DOUBLE_REF,LONG_REF,char*,long 
	#define DHFLSHdll_ARGS DOUBLE_REF,DOUBLE_REF,double *,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,double *,double *,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,LONG_REF,char*,long 
    #define DIELECdll_ARGS DOUBLE_REF,DOUBLE_REF,double *,DOUBLE_REF
    // DLsatK
	#define DOTFILLdll_ARGS double *,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,LONG_REF,char*,long 
    #define DPDD2dll_ARGS DOUBLE_REF,DOUBLE_REF,double *,DOUBLE_REF
    #define DPDDdll_ARGS DOUBLE_REF,DOUBLE_REF,double *,DOUBLE_REF
	#define DPDDKdll_ARGS LONG_REF,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF
    #define DPDTdll_ARGS DOUBLE_REF,DOUBLE_REF,double *,DOUBLE_REF
	#define DPDTKdll_ARGS LONG_REF,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF
    #define DPTSATKdll_ARGS LONG_REF,DOUBLE_REF,LONG_REF,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,LONG_REF,char*,long 
    // DQFL2
	#define DSFL1dll_ARGS DOUBLE_REF,DOUBLE_REF,double *,DOUBLE_REF,LONG_REF,char*,long 
	#define DSFLSHdll_ARGS DOUBLE_REF,DOUBLE_REF,double *,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,double *,double *,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,LONG_REF,char*,long 
    // DVDATKdll
    #define ENTHALdll_ARGS DOUBLE_REF,DOUBLE_REF,double *,DOUBLE_REF
    #define ENTROdll_ARGS DOUBLE_REF,DOUBLE_REF,double *,DOUBLE_REF
	#define ESFLSHdll_ARGS DOUBLE_REF,DOUBLE_REF,double *,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,double *,double *,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,LONG_REF,char*,long 
	// ETAK0
	// ETAK1
	// ETAKB
	// ETAKR
	// EXCESS
    // FGCTY2
	#define FGCTYdll_ARGS DOUBLE_REF,DOUBLE_REF,double *,double *
	#define FPVdll_ARGS DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,double *,DOUBLE_REF
	#define FUGCOFdll_ARGS DOUBLE_REF,DOUBLE_REF,double *,double *, LONG_REF,char*,long 
    #define GERG04dll_ARGS LONG_REF,LONG_REF,LONG_REF,char*,long 
	#define GETFIJdll_ARGS char*,double *,char*,char*,long ,long ,long 
	#define GETKTVdll_ARGS LONG_REF,LONG_REF,char*,double *,char*,char*,char*,char*,long ,long ,long ,long ,long 
	// GETMOD
    #define GIBBSdll_ARGS DOUBLE_REF,DOUBLE_REF,double *,DOUBLE_REF,DOUBLE_REF
	// HEAT
	// HEATFRM
	// HSFL1
    #define HSFLSHdll_ARGS DOUBLE_REF,DOUBLE_REF,double *,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,double *,double *,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,LONG_REF,char*,long 
	// IDCRV
    #define INFOdll_ARGS LONG_REF,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF
	// JICRV
	// JTCRV
    #define LIMITKdll_ARGS char*,LONG_REF,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,LONG_REF,char*,long ,long
	#define LIMITSdll_ARGS char*,double *,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,long 
    #define LIMITXdll_ARGS char*,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,double *,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,LONG_REF,char*,long ,long 
	// LIQSPNDL
	// MASSFLUX
	// MAXPDLL
	// MAXTDLL
    #define MELTPdll_ARGS DOUBLE_REF,double *,DOUBLE_REF,LONG_REF,char*,long 
    #define MELTTdll_ARGS DOUBLE_REF,double *,DOUBLE_REF,LONG_REF,char*,long 
    #define MLTH2Odll_ARGS DOUBLE_REF,DOUBLE_REF,DOUBLE_REF
    #define NAMEdll_ARGS LONG_REF,char*,char*,char*,long ,long ,long 
    #define PASSCMNdll_ARGS char *,LONG_REF,LONG_REF,LONG_REF,char *,long*,DOUBLE_REF, double *, long*, char*, long, long, long
	// OMEGA
    #define PDFL1dll_ARGS DOUBLE_REF,DOUBLE_REF,double *,DOUBLE_REF,LONG_REF,char*,long 
    #define PDFLSHdll_ARGS DOUBLE_REF,DOUBLE_REF,double *,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,double *,double *,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,LONG_REF,char*,long 
    // PEFL1
	#define PEFLSHdll_ARGS DOUBLE_REF,DOUBLE_REF,double *,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,double *,double *,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,LONG_REF,char*,long 
    #define PHFL1dll_ARGS DOUBLE_REF,DOUBLE_REF,double *,LONG_REF,DOUBLE_REF,DOUBLE_REF,LONG_REF,char*,long 
    #define PHFLSHdll_ARGS DOUBLE_REF,DOUBLE_REF,double *,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,double *,double *,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,LONG_REF,char*,long 
	#define PHI0dll_ARGS LONG_REF,LONG_REF,DOUBLE_REF,DOUBLE_REF,double *, DOUBLE_REF
    #define PHIXdll_ARGS LONG_REF,LONG_REF,DOUBLE_REF,DOUBLE_REF,double *, DOUBLE_REF
    #define PQFLSHdll_ARGS DOUBLE_REF,DOUBLE_REF,double *,LONG_REF,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,double *,double *,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,LONG_REF,char*,long 
    #define PREOSdll_ARGS LONG_REF
    #define PRESSdll_ARGS DOUBLE_REF,DOUBLE_REF,double *,DOUBLE_REF
	// PSATK
    #define PSFL1dll_ARGS DOUBLE_REF,DOUBLE_REF,double *,LONG_REF,DOUBLE_REF,DOUBLE_REF,LONG_REF,char*,long 
    #define PSFLSHdll_ARGS DOUBLE_REF,DOUBLE_REF,double *,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,double *,double *,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,LONG_REF,char*,long 
    #define PUREFLDdll_ARGS LONG_REF
	#define QMASSdll_ARGS DOUBLE_REF,double *,double *,DOUBLE_REF,double *,double *,DOUBLE_REF,DOUBLE_REF,LONG_REF,char*,long 
    #define QMOLEdll_ARGS DOUBLE_REF,double *,double *,DOUBLE_REF,double *,double *,DOUBLE_REF,DOUBLE_REF,LONG_REF,char*,long 
	// RDXHMX
	#define REDXdll_ARGS DOUBLE_REF,DOUBLE_REF,DOUBLE_REF
    #define RESIDUALdll_ARGS DOUBLE_REF,DOUBLE_REF,double *,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF
	// RIEM
    #define RMIX2dll_ARGS double *,DOUBLE_REF
	#define RPVersion_ARGS char*, long
    #define SATDdll_ARGS DOUBLE_REF,double *,LONG_REF,LONG_REF,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,double *,double *,LONG_REF,char*,long 
    #define SATEdll_ARGS DOUBLE_REF,double *,LONG_REF,LONG_REF,LONG_REF,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,LONG_REF,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,LONG_REF,char*,long 
	// SATGUESS
	// SATGV
    #define SATHdll_ARGS DOUBLE_REF,double *,LONG_REF,LONG_REF,LONG_REF,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,LONG_REF,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,LONG_REF,char*,long 
    #define SATPdll_ARGS DOUBLE_REF,double *,LONG_REF,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,double *,double *,LONG_REF,char*,long 
	// SATPEST
    #define SATSdll_ARGS DOUBLE_REF,double *,LONG_REF,LONG_REF,LONG_REF,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,LONG_REF,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,LONG_REF,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,LONG_REF,char*,long 
    #define SATSPLNdll_ARGS double *,LONG_REF,char*,long 
	#define SATTdll_ARGS DOUBLE_REF,double *,LONG_REF,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,double *,double *,LONG_REF,char*,long 
    // SATTEST
	#define SATTPdll_ARGS DOUBLE_REF,DOUBLE_REF,double *,LONG_REF,long*,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,double *,double *,DOUBLE_REF, LONG_REF,char*,long     
    #define SETAGAdll_ARGS LONG_REF,char*,long 
    #define SETKTVdll_ARGS LONG_REF,LONG_REF,char*,double *,char*,LONG_REF,char*,long ,long ,long 
    #define SETMIXdll_ARGS char*,char*,char*,LONG_REF,char*,double *,LONG_REF,char*,long ,long ,long ,long ,long 
	#define SETMODdll_ARGS LONG_REF,char*,char*,char*,LONG_REF,char*,long ,long ,long ,long 
	#define SETPATHdll_ARGS const char*
    #define SETREFdll_ARGS char*,LONG_REF,double *,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,LONG_REF,char*,long ,long 
    #define SETUPdll_ARGS LONG_REF,char*,char*,char*,LONG_REF,char*,long ,long ,long ,long 
	// SPLNROOT
	#define SPLNVALdll_ARGS LONG_REF, LONG_REF, DOUBLE_REF, DOUBLE_REF, LONG_REF, char *, long    
    #define SUBLPdll_ARGS DOUBLE_REF,double *,DOUBLE_REF,LONG_REF,char*,long 
    #define SUBLTdll_ARGS DOUBLE_REF,double *,DOUBLE_REF,LONG_REF,char*,long 
    #define SURFTdll_ARGS DOUBLE_REF,DOUBLE_REF,double *,DOUBLE_REF,LONG_REF,char*,long 
    #define SURTENdll_ARGS DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,double *,double *,DOUBLE_REF,LONG_REF,char*,long 
	// TCXK0
	// TCXKB
	// TCKKC
    #define TDFLSHdll_ARGS DOUBLE_REF,DOUBLE_REF,double *,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,double *,double *,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,LONG_REF,char*,long 
    //TEFL1
	#define TEFLSHdll_ARGS DOUBLE_REF,DOUBLE_REF,double *,LONG_REF,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,double *,double *,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,LONG_REF,char*,long 
    #define THERM0dll_ARGS DOUBLE_REF,DOUBLE_REF,double *,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF
    #define THERM2dll_ARGS DOUBLE_REF,DOUBLE_REF,double *,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF
    #define THERM3dll_ARGS DOUBLE_REF,DOUBLE_REF,double *,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF
    #define THERMdll_ARGS DOUBLE_REF,DOUBLE_REF,double *,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF
	// THFL1
    #define THFLSHdll_ARGS DOUBLE_REF,DOUBLE_REF,double *,LONG_REF,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,double *,double *,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,LONG_REF,char*,long 
    #define TPFL2dll_ARGS DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,LONG_REF,char*,long 
	#define TPFLSHdll_ARGS DOUBLE_REF,DOUBLE_REF,double *,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,double *,double *,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,LONG_REF,char*,long 
    #define TPRHOdll_ARGS DOUBLE_REF,DOUBLE_REF,double *,LONG_REF,LONG_REF,DOUBLE_REF,LONG_REF,char*,long 
	// TPPROPR
    #define TQFLSHdll_ARGS DOUBLE_REF,DOUBLE_REF,double *,LONG_REF,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,double *,double *,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,LONG_REF,char*,long 
    #define TRNPRPdll_ARGS DOUBLE_REF,DOUBLE_REF,double *,DOUBLE_REF,DOUBLE_REF,LONG_REF,char*,long
	// TSATD
	// TSFL1
    #define TSFLSHdll_ARGS DOUBLE_REF,DOUBLE_REF,double *,LONG_REF,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,double *,double *,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,DOUBLE_REF,LONG_REF,char*,long 
	// UNSETAGA
	// VAPSPNDL
	// VIRBA
    #define VIRBdll_ARGS DOUBLE_REF,double *,DOUBLE_REF
    // VIRCA
	#define VIRCdll_ARGS DOUBLE_REF,double *,DOUBLE_REF
    #define WMOLdll_ARGS double *,DOUBLE_REF
    #define XMASSdll_ARGS double *,double *,DOUBLE_REF
    #define XMOLEdll_ARGS double *,double *,DOUBLE_REF
    
	/* Define explicit function pointers
	 * Each will look something like: typedef void (RPCALLCONV ACTVYdll_TYPE)(ACTVYdll_ARGS);
	 * 
	 * The ## are needed to escape the _ character in the variable names
	 * 
	 * ***MAGIC WARNING**!! X Macros in use
	 * See http://stackoverflow.com/a/148610
	 * See http://stackoverflow.com/questions/147267/easy-way-to-use-variables-of-enum-types-as-string-in-c#202511
	 */
	#define X(name)  typedef void (RPCALLCONV name ## _TYPE)(name ## _ARGS);
		LIST_OF_REFPROP_FUNCTION_NAMES
	#undef X

	/* Define explicit function pointers
	 * Each will look something like: typedef RPVersion_TYPE * RPVersion_POINTER;
	 * 
	 * The ## are needed to escape the _ character in the variable names
	 * 
	 * ***MAGIC WARNING**!! X Macros in use
	 * See http://stackoverflow.com/a/148610
	 * See http://stackoverflow.com/questions/147267/easy-way-to-use-variables-of-enum-types-as-string-in-c#202511
	 */
	#define X(name) typedef name ## _TYPE * name ## _POINTER;
		LIST_OF_REFPROP_FUNCTION_NAMES
	#undef X

#ifdef __cplusplus
} // extern "C"
#endif // __cplusplus

//******************************************************************************
//******************************************************************************
//*********************  REFPROP IMPLEMENTATION  *******************************
//******************************************************************************
//******************************************************************************

// Define this preprocessor flag to also define the function prototypes and connect function pointers
// N.B. Define this macro in only one location
// N.B. This is C++-only, though with some work it could be made C compatible
#ifdef REFPROP_IMPLEMENTATION

	#ifndef __cplusplus
	#error REFPROP_IMPLEMENTATION can only be used in C++
	#endif

	#include <string>
    #include <algorithm>

	static std::string RPVersion_loaded = "";

    #if defined(__powerpc__)
        static void *RefpropdllInstance=NULL;
    #elif defined(__RPISLINUX__) || defined(__RPISAPPLE__)
        #include <dlfcn.h>
        static void *RefpropdllInstance=NULL;
    #elif defined(__RPISWINDOWS__)
        #define NOMINMAX
        #include <windows.h>
        #undef NOMINMAX
        static HINSTANCE RefpropdllInstance=NULL;
    #else
        #pragma error
    #endif

    enum DLLNameManglingStyle{ NO_NAME_MANGLING = 0, LOWERCASE_NAME_MANGLING, LOWERCASE_AND_UNDERSCORE_NAME_MANGLING };

    /* Define functions as pointers and initialise them to NULL
    * Declare the functions for direct access
    *
    * Example: SETPATHdll_POINTER SETPATHdll;
    *
    * ***MAGIC WARNING**!! X Macros in use
    * See http://stackoverflow.com/a/148610
    * See http://stackoverflow.com/questions/147267/easy-way-to-use-variables-of-enum-types-as-string-in-c#202511
    */
    #define X(name)  name ## _POINTER name;
     LIST_OF_REFPROP_FUNCTION_NAMES
    #undef X
	
	inline std::string RPlower(std::string str)
    {
        std::transform(str.begin(), str.end(), str.begin(), ::tolower);
        return str;
    }

    void *getFunctionPointer(const char *name, DLLNameManglingStyle mangling_style = NO_NAME_MANGLING)
    {
        std::string function_name;
        switch(mangling_style){
            case NO_NAME_MANGLING:
                function_name = name; break;
            case LOWERCASE_NAME_MANGLING:
                function_name = RPlower(name); break;
            case LOWERCASE_AND_UNDERSCORE_NAME_MANGLING:
                function_name = RPlower(name) + "_"; break;
        }
        #if defined(__RPISWINDOWS__)
            return (void *) GetProcAddress(RefpropdllInstance, function_name.c_str());
        #elif defined(__RPISLINUX__)
            return dlsym(RefpropdllInstance, function_name.c_str());
        #elif defined(__RPISAPPLE__)
            return dlsym(RefpropdllInstance, function_name.c_str());
        #else
            return NULL;
        #endif
    }

    /**
     * @brief Set the function pointers in the DLL/SO
     */
    bool setFunctionPointers(std::string &err)
    {
        if (RefpropdllInstance==NULL)
        { 
            err = "REFPROP is not loaded, make sure you call this function after loading the library using load_REFPROP";
            return false;
        }
        /* First determine the type of name mangling in use.
         * A) RPVersion -> RPVersion
         * B) RPVersion -> rpversion
         * C) RPVersion -> rpversion_
         */
         DLLNameManglingStyle mangling_style = NO_NAME_MANGLING; // defaults to no mangling

         SETUPdll = (SETUPdll_POINTER) getFunctionPointer("SETUPdll");
         if (SETUPdll == NULL){ // some mangling in use
             SETUPdll = (SETUPdll_POINTER) getFunctionPointer("setupdll");
             if (SETUPdll != NULL){
                mangling_style = LOWERCASE_NAME_MANGLING;
             }
             else{
                 SETUPdll = (SETUPdll_POINTER) getFunctionPointer("setupdll_");
                 if (SETUPdll != NULL){
                     mangling_style = LOWERCASE_AND_UNDERSCORE_NAME_MANGLING;
                 }
                 else{
                     err = "Could not load the symbol SETUPdll or any of its mangled forms; REFPROP shared library broken";
					 return false;
                 }
             }
         }

        /* Set the pointers, platform independent
         *
         * Example: RPVersion = (RPVersion_POINTER) getFunctionPointer(STRINGIFY(RPVersion));
         *
         * ***MAGIC WARNING**!! X Macros in use
         * See http://stackoverflow.com/a/148610
         * See http://stackoverflow.com/questions/147267/easy-way-to-use-variables-of-enum-types-as-string-in-c#202511
         */
        #define X(name)  name = (name ## _POINTER) getFunctionPointer(STRINGIFY(name), mangling_style);
           LIST_OF_REFPROP_FUNCTION_NAMES
        #undef X

        return true;
    }
    /*
    std::string get_REFPROP_fluid_path(std::string alt_refprop_path = "")
    {
        std::string rpPath = refpropPath;
        
        if (!alt_rp_path.empty()){ rpPath = alt_refprop_path; }
        
        #if defined(__RPISLINUX__) || defined(__RPISAPPLE__)
            return rpPath + std::string("/fluids/");
        #else
            return rpPath;
        #endif
    }
    */
    bool load_REFPROP(std::string &err)
    {
        // If REFPROP is not loaded
        if (RefpropdllInstance == NULL)
        {

            // Load it
            #if defined(__RPISWINDOWS__)
                /* We need this logic on windows because if you use the bitness
                 * macros it requires that the build bitness and the target bitness
                 * are the same which is in general not the case.  Therefore, checking
                 * both is safe
                 */
                // First try to load the 64-bit version
                // 64-bit code here.
                TCHAR refpropdllstring[100] = TEXT("refprp64.dll");
                RefpropdllInstance = LoadLibrary(refpropdllstring);

                if (RefpropdllInstance==NULL){
                    // That didn't work, let's try the 32-bit version
                    // 32-bit code here.
                    TCHAR refpropdllstring32[100] = TEXT("refprop.dll");
                    RefpropdllInstance = LoadLibrary(refpropdllstring32);
                }
            #elif defined(__RPISLINUX__)
                RefpropdllInstance = dlopen ("librefprop.so", RTLD_NOW);
            #elif defined(__RPISAPPLE__)
                RefpropdllInstance = dlopen ("librefprop.dylib", RTLD_NOW);
            #else
                RefpropdllInstance = NULL;
            #endif

            if (RefpropdllInstance==NULL)
            {
                #if defined(__RPISWINDOWS__)
                    err = "Could not load refprop.dll, make sure it is in your system search path. In case you run 64bit and you have a REFPROP license, try installing the 64bit DLL from NIST.";
                #elif defined(__RPISLINUX__) || defined (__RPISLINUX__)
                    err = "Could not load librefprop.so, make sure it is in your system search path.";
                #else
                    err = "Something is wrong with the platform definition, you should not end up here.";
                #endif
                return false;
            }
			std::string err;
            if (setFunctionPointers(err) != true)
            {
                err = "There was an error setting the REFPROP function pointers, check types and names in header file";
                return false;
            }
            char rpv[1000];
            RPVersion(rpv, 1000);
            RPVersion_loaded = rpv;
            return true;
        }
        return true;
    }

#endif // REFPROP_IMPLEMENTATION

#endif // REFPROP_LIB_H
