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
  
    extern bool load_REFPROP(std::string &err, const std::string &shared_library_path = "", const std::string &shared_library_name = "");
    
C) (default) Add definitions of the function pointers (for all the other files that call REFPROP when REFPROP is runtime linked):

    #include "REFPROP_lib.h"
    
Usage
-----

Please see the ``CMakeLists.txt`` cmake build system which includes examples of two files that both call into REFPROP.  Distribution of the ``REFPROP_lib.h`` file with your C++ code should be sufficient.

In order to build the cmake examples, do something like (in the root of code, next to ``CMakeLists.txt``):

    mkdir build
    cd build
    cmake ..
    cmake --build .
    
which uses all default flags.  For more information, read the cmake docs.
