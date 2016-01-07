REFPROP-headers
===============

This is a tiny repository that contains header files for the REFPROP fluid property library. The header files should work with both C++ and C.

Options
-------

A) Generate function prototypes (only) - for static linkage:

    #define REFPROP_PROTOTYPES
    #include "REFPROP_lib.h"
    #undef REFPROP_PROTOTYPES
    
B) (In one file only!!!) Generate the interface code for runtime linkage of REFPROP (see main.cpp):

    #define REFPROP_IMPLEMENTATION
    #include "REFPROP_lib.h"
    #undef REFPROP_IMPLEMENTATION
    
  If you want to call these functions elsewhere, best to define a prototype in your own code:
  
    extern bool load_REFPROP(std::string &err)
    
C) (default) Add definitions of the function pointers (for all the other files that call REFPROP when REFPROP is runtime linked):

    #include "REFPROP_lib.h"