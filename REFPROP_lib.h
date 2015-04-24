
#ifndef REFPROP_LIB_H
#define REFPROP_LIB_H

// The idea here is to have a common header for Windows 
// and Linux systems. The Windows branch should cover the
// functions provided by the .dll and the Linux part covers
// the compiled .so file. Name changes caused by gfortran 
// are repsected and should be accounted for. 

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
    X(DHFL2dll) \
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
    X(DSFL2dll) \
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
    X(SPECGRdll) \
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

// I'll try to follow this example from:
// http://www.gershnik.com/tips/cpp.asp
// function type: typedef void [compiler stuff]  func_t(int, float);
// function declaration: func_t func;
// pointer type: typedef func_t * func_ptr;
#ifdef __cplusplus
extern "C" {
#endif

    // For C calling conventions, replaced all "double &" with "double *", and "long &" with "long *"
    typedef void (RPCALLCONV RPVersion_TYPE)( char* , long);
    typedef void (RPCALLCONV SETPATHdll_TYPE)( const char* );
    typedef void (RPCALLCONV ABFL1dll_TYPE)(double *,double *,double *,long *,double *,double *,double *,double *,double *,double *,long *,char*,long );
    typedef void (RPCALLCONV ABFL2dll_TYPE)(double *,double *,double *,long *,long *,double *,double *,double *,double *,double *,double *,double *,double *,double *,double *,double *,double *,double *,double *,double *,double *,long *,char*,long );
    typedef void (RPCALLCONV ACTVYdll_TYPE)(double *,double *,double *,double *);
    typedef void (RPCALLCONV AGdll_TYPE)(double *,double *,double *,double *,double *);
    typedef void (RPCALLCONV CCRITdll_TYPE)(double *,double *,double *,double *,double *,double *,double *,double *,double *,long *,char*,long );
    typedef void (RPCALLCONV CP0dll_TYPE)(double *,double *,double *);
    typedef void (RPCALLCONV CRITPdll_TYPE)(double *,double *,double *,double *,long *,char*,long );
    typedef void (RPCALLCONV CSATKdll_TYPE)(long *,double *,long *,double *,double *,double *,long *,char*,long );
    typedef void (RPCALLCONV CV2PKdll_TYPE)(long *,double *,double *,double *,double *,long *,char*,long );
    typedef void (RPCALLCONV CVCPKdll_TYPE)(long *,double *,double *,double *,double *);
    typedef void (RPCALLCONV CVCPdll_TYPE)(double *,double *,double *,double *,double *);
    typedef void (RPCALLCONV DBDTdll_TYPE)(double *,double *,double *);
    typedef void (RPCALLCONV DBFL1dll_TYPE)(double *,double *,double *,double *,double *,double *,long *,char*,long );
    typedef void (RPCALLCONV DBFL2dll_TYPE)(double *,double *,double *,long *,double *,double *,double *,double *,double *,double *,double *,double *,long *,char*,long );
    typedef void (RPCALLCONV DDDPdll_TYPE)(double *,double *,double *,double *);
    typedef void (RPCALLCONV DDDTdll_TYPE)(double *,double *,double *,double *);
    typedef void (RPCALLCONV DEFLSHdll_TYPE)(double *,double *,double *,double *,double *,double *,double *,double *,double *,double *,double *,double *,double *,double *,double *,long *,char*,long );
    typedef void (RPCALLCONV DHD1dll_TYPE)(double *,double *,double *,double *,double *,double *,double *,double *,double *);
    typedef void (RPCALLCONV DHFL1dll_TYPE)(double *,double *,double *,double *,long *,char*,long );
    typedef void (RPCALLCONV DHFL2dll_TYPE)(double *,double *,double *,double *,double *,double *,double *,double *,double *,double *,long *,char*,long );
    typedef void (RPCALLCONV DHFLSHdll_TYPE)(double *,double *,double *,double *,double *,double *,double *,double *,double *,double *,double *,double *,double *,double *,double *,long *,char*,long );
    typedef void (RPCALLCONV DIELECdll_TYPE)(double *,double *,double *,double *);
    typedef void (RPCALLCONV DOTFILLdll_TYPE)(long *,double *,double *,double *,long *,char*,long );
    typedef void (RPCALLCONV DPDD2dll_TYPE)(double *,double *,double *,double *);
    typedef void (RPCALLCONV DPDDKdll_TYPE)(long *,double *,double *,double *);
    typedef void (RPCALLCONV DPDDdll_TYPE)(double *,double *,double *,double *);
    typedef void (RPCALLCONV DPDTKdll_TYPE)(long *,double *,double *,double *);
    typedef void (RPCALLCONV DPDTdll_TYPE)(double *,double *,double *,double *);
    typedef void (RPCALLCONV DPTSATKdll_TYPE)(long *,double *,long *,double *,double *,double *,double *,long *,char*,long );
    typedef void (RPCALLCONV DSFLSHdll_TYPE)(double *,double *,double *,double *,double *,double *,double *,double *,double *,double *,double *,double *,double *,double *,double *,long *,char*,long );
    typedef void (RPCALLCONV DSFL1dll_TYPE)(double *,double *,double *,double *,long *,char*,long );
    typedef void (RPCALLCONV DSFL2dll_TYPE)(double *,double *,double *,double *,double *,double *,double *,double *,double *,double *,long *,char*,long );
    typedef void (RPCALLCONV ENTHALdll_TYPE)(double *,double *,double *,double *);
    typedef void (RPCALLCONV ENTROdll_TYPE)(double *,double *,double *,double *);
    typedef void (RPCALLCONV ESFLSHdll_TYPE)(double *,double *,double *,double *,double *,double *,double *,double *,double *,double *,double *,double *,double *,double *,double *,long *,char*,long );
    typedef void (RPCALLCONV FGCTYdll_TYPE)(double *,double *,double *,double *);
    typedef void (RPCALLCONV FPVdll_TYPE)(double *,double *,double *,double *,double *);
    typedef void (RPCALLCONV FUGCOFdll_TYPE)(double *,double *,double *,double*, long *,char*,long );
    typedef void (RPCALLCONV GERG04dll_TYPE)(long *,long *,long *,char*,long );
    typedef void (RPCALLCONV GETFIJdll_TYPE)(char*,double *,char*,char*,long ,long ,long );
    typedef void (RPCALLCONV GETKTVdll_TYPE)(long *,long *,char*,double *,char*,char*,char*,char*,long ,long ,long ,long ,long );
    typedef void (RPCALLCONV GIBBSdll_TYPE)(double *,double *,double *,double *,double *);
    typedef void (RPCALLCONV HSFLSHdll_TYPE)(double *,double *,double *,double *,double *,double *,double *,double *,double *,double *,double *,double *,double *,double *,double *,long *,char*,long );
    typedef void (RPCALLCONV INFOdll_TYPE)(long *,double *,double *,double *,double *,double *,double *,double *,double *,double *,double *);
    typedef void (RPCALLCONV LIMITKdll_TYPE)(char*,long *,double *,double *,double *,double *,double *,double *,double *,long *,char*,long ,long );
    typedef void (RPCALLCONV LIMITSdll_TYPE)(char*,double *,double *,double *,double *,double *,long );
    typedef void (RPCALLCONV LIMITXdll_TYPE)(char*,double *,double *,double *,double *,double *,double *,double *,double *,long *,char*,long ,long );
    typedef void (RPCALLCONV MELTPdll_TYPE)(double *,double *,double *,long *,char*,long );
    typedef void (RPCALLCONV MELTTdll_TYPE)(double *,double *,double *,long *,char*,long );
    typedef void (RPCALLCONV MLTH2Odll_TYPE)(double *,double *,double *);
    typedef void (RPCALLCONV NAMEdll_TYPE)(long *,char*,char*,char*,long ,long ,long );
    typedef void (RPCALLCONV PASSCMNdll_TYPE)(char *,long *,long *,long *,char *,long*,double *, double *, long*, char*, long, long, long);
    typedef void (RPCALLCONV PDFL1dll_TYPE)(double *,double *,double *,double *,long *,char*,long );
    typedef void (RPCALLCONV PDFLSHdll_TYPE)(double *,double *,double *,double *,double *,double *,double *,double *,double *,double *,double *,double *,double *,double *,double *,long *,char*,long );
    typedef void (RPCALLCONV PEFLSHdll_TYPE)(double *,double *,double *,double *,double *,double *,double *,double *,double *,double *,double *,double *,double *,double *,double *,long *,char*,long );
    typedef void (RPCALLCONV PHFL1dll_TYPE)(double *,double *,double *,long *,double *,double *,long *,char*,long );
    typedef void (RPCALLCONV PHFLSHdll_TYPE)(double *,double *,double *,double *,double *,double *,double *,double *,double *,double *,double *,double *,double *,double *,double *,long *,char*,long );
    typedef void (RPCALLCONV PHIXdll_TYPE)(long *,long *,double *,double *,double *, double *);
    typedef void (RPCALLCONV PHI0dll_TYPE)(long *,long *,double *,double *,double *, double *);
    typedef void (RPCALLCONV PQFLSHdll_TYPE)(double *,double *,double *,long *,double *,double *,double *,double *,double *,double *,double *,double *,double *,double *,double *,double *,long *,char*,long );
    typedef void (RPCALLCONV PREOSdll_TYPE)(long *);
    typedef void (RPCALLCONV PRESSdll_TYPE)(double *,double *,double *,double *);
    typedef void (RPCALLCONV PSFL1dll_TYPE)(double *,double *,double *,long *,double *,double *,long *,char*,long );
    typedef void (RPCALLCONV PSFLSHdll_TYPE)(double *,double *,double *,double *,double *,double *,double *,double *,double *,double *,double *,double *,double *,double *,double *,long *,char*,long );
    typedef void (RPCALLCONV PUREFLDdll_TYPE)(long *);
    typedef void (RPCALLCONV QMASSdll_TYPE)(double *,double *,double *,double *,double *,double *,double *,double *,long *,char*,long );
    typedef void (RPCALLCONV QMOLEdll_TYPE)(double *,double *,double *,double *,double *,double *,double *,double *,long *,char*,long );
    typedef void (RPCALLCONV RESIDUALdll_TYPE)(double *,double *,double *,double *,double *,double *,double *,double *,double *,double *,double *);
    typedef void (RPCALLCONV REDXdll_TYPE)(double *,double *,double *);
    typedef void (RPCALLCONV RMIX2dll_TYPE)(double *,double *);
    typedef void (RPCALLCONV SATDdll_TYPE)(double *,double *,long *,long *,double *,double *,double *,double *,double *,double *,long *,char*,long );
    typedef void (RPCALLCONV SATEdll_TYPE)(double *,double *,long *,long *,long *,double *,double *,double *,long *,double *,double *,double *,long *,char*,long );
    typedef void (RPCALLCONV SATHdll_TYPE)(double *,double *,long *,long *,long *,double *,double *,double *,long *,double *,double *,double *,long *,char*,long );
    typedef void (RPCALLCONV SATPdll_TYPE)(double *,double *,long *,double *,double *,double *,double *,double *,long *,char*,long );
    typedef void (RPCALLCONV SATSdll_TYPE)(double *,double *,long *,long *,long *,double *,double *,double *,long *,double *,double *,double *,long *,double *,double *,double *,long *,char*,long );
    typedef void (RPCALLCONV SATTdll_TYPE)(double *,double *,long *,double *,double *,double *,double *,double *,long *,char*,long );
    typedef void (RPCALLCONV SATTPdll_TYPE)(double *,double *,double*,long *,long*,double *,double *,double *,double *,double *,double *, long *,char*,long );    
    typedef void (RPCALLCONV SATSPLNdll_TYPE)(double *,long *,char*,long );
    typedef void (RPCALLCONV SETAGAdll_TYPE)(long *,char*,long );
    typedef void (RPCALLCONV SETKTVdll_TYPE)(long *,long *,char*,double *,char*,long *,char*,long ,long ,long );
    typedef void (RPCALLCONV SETMIXdll_TYPE)(char*,char*,char*,long *,char*,double *,long *,char*,long ,long ,long ,long ,long );
    typedef void (RPCALLCONV SETMODdll_TYPE)(long *,char*,char*,char*,long *,char*,long ,long ,long ,long );
    typedef void (RPCALLCONV SETREFdll_TYPE)(char*,long *,double *,double *,double *,double *,double *,long *,char*,long ,long );
    typedef void (RPCALLCONV SETUPdll_TYPE)(long *,char*,char*,char*,long *,char*,long ,long ,long ,long );
    typedef void (RPCALLCONV SPLNVALdll_TYPE)(long *, long *, double *, double *, long *, char *, long);    
    typedef void (RPCALLCONV SPECGRdll_TYPE)(double *,double *,double *,double *);
    typedef void (RPCALLCONV SUBLPdll_TYPE)(double *,double *,double *,long *,char*,long );
    typedef void (RPCALLCONV SUBLTdll_TYPE)(double *,double *,double *,long *,char*,long );
    typedef void (RPCALLCONV SURFTdll_TYPE)(double *,double *,double *,double *,long *,char*,long );
    typedef void (RPCALLCONV SURTENdll_TYPE)(double *,double *,double *,double *,double *,double *,long *,char*,long );
    typedef void (RPCALLCONV TDFLSHdll_TYPE)(double *,double *,double *,double *,double *,double *,double *,double *,double *,double *,double *,double *,double *,double *,double *,long *,char*,long );
    typedef void (RPCALLCONV TEFLSHdll_TYPE)(double *,double *,double *,long *,double *,double *,double *,double *,double *,double *,double *,double *,double *,double *,double *,double *,long *,char*,long );
    typedef void (RPCALLCONV THERM0dll_TYPE)(double *,double *,double *,double *,double *,double *,double *,double *,double *,double *,double *,double *);
    typedef void (RPCALLCONV THERM2dll_TYPE)(double *,double *,double *,double *,double *,double *,double *,double *,double *,double *,double *,double *,double *,double *,double *,double *,double *,double *,double *,double *,double *,double *,double *,double *,double *);
    typedef void (RPCALLCONV THERM3dll_TYPE)(double *,double *,double *,double *,double *,double *,double *,double *,double *,double *,double *,double *,double *);
    typedef void (RPCALLCONV THERMdll_TYPE)(double *,double *,double *,double *,double *,double *,double *,double *,double *,double *,double *);
    typedef void (RPCALLCONV THFLSHdll_TYPE)(double *,double *,double *,long *,double *,double *,double *,double *,double *,double *,double *,double *,double *,double *,double *,double *,long *,char*,long );
    typedef void (RPCALLCONV TPFLSHdll_TYPE)(double *,double *,double *,double *,double *,double *,double *,double *,double *,double *,double *,double *,double *,double *,double *,long *,char*,long );
    typedef void (RPCALLCONV TPFL2dll_TYPE)(double *,double *,double *,double *,double *,double *,double *,double *,long *,char*,long );
    typedef void (RPCALLCONV TPRHOdll_TYPE)(double *,double *,double *,long *,long *,double *,long *,char*,long );
    typedef void (RPCALLCONV TQFLSHdll_TYPE)(double *,double *,double *,long *,double *,double *,double *,double *,double *,double *,double *,double *,double *,double *,double *,double *,long *,char*,long );
    typedef void (RPCALLCONV TRNPRPdll_TYPE)(double *,double *,double *,double *,double *,long *,char*,long );
    typedef void (RPCALLCONV TSFLSHdll_TYPE)(double *,double *,double *,long *,double *,double *,double *,double *,double *,double *,double *,double *,double *,double *,double *,double *,long *,char*,long );
    typedef void (RPCALLCONV VIRBdll_TYPE)(double *,double *,double *);
    typedef void (RPCALLCONV VIRCdll_TYPE)(double *,double *,double *);
    typedef void (RPCALLCONV WMOLdll_TYPE)(double *,double *);
    typedef void (RPCALLCONV XMASSdll_TYPE)(double *,double *,double *);
    typedef void (RPCALLCONV XMOLEdll_TYPE)(double *,double *,double *);
    
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
	
	inline std::string lower(std::string str)
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
                function_name = lower(name); break;
            case LOWERCASE_AND_UNDERSCORE_NAME_MANGLING:
                function_name = lower(name) + "_"; break;
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
