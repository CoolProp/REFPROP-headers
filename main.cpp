
#define REFPROP_IMPLEMENTATION
#include "REFPROP_lib.h"
#undef REFPROP_IMPLEMENTATION

int main()
{
    // Load the DLL
	std::string err;
    bool loaded_REFPROP = load_REFPROP(err);
    
    return EXIT_SUCCESS;
}