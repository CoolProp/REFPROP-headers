
// Only this file gets the implementation
#define REFPROP_IMPLEMENTATION
#define REFPROP_FUNCTION_MODIFIER
#include "REFPROP_lib.h"
#undef REFPROP_FUNCTION_MODIFIER
#undef REFPROP_IMPLEMENTATION

#include <stdlib.h>
#include <stdio.h>

// Prototype from the other file
void another_file(void);

int main()
{

    // Call a function in another file (and load the DLL, and then unload it)
    another_file();

    // Load the shared library
    std::string err;
    bool loaded_REFPROP = load_REFPROP(err, "D:/Code/PhiFit/_private/veric", "REFPRP64.DLL");
    printf("Loaded refprop (in main.cpp): %s @ address %zu\n", loaded_REFPROP ? "true" : "false", REFPROP_address());
    if (!loaded_REFPROP){
        return EXIT_FAILURE;
    }
 
    char mypath[] = "D:/Code/PhiFit/_private/veric";
    SETPATHdll(mypath, 400);

    int ierr = 0, nc = 1;
    char herr[255], hfld[] = "AMMONIA|WATER", hhmx[] = "HMX.BNC", href[] = "DEF";
    SETUPdll(nc,hfld,hhmx,href,ierr,herr,10000,255,3,255);
    if (ierr > 0) printf("This ierr: %d herr: %s\n", ierr, herr);
    {
        int ierr = 0;
        char herr[255];
        double z[] = {1.0}, x[] = {1.0}, y[] = {1.0}, T= 300, p = 101.325, d = -1, dl = -1, dv = -1, h = -1, s = -1, u = -1, cp = -1, cv = -1, q = -1, w = -1;
        TPFLSHdll(T, p, z, d, dl, dv, x, y, h,s,u,cp,cv,w,q,ierr,herr,255);
        if (ierr > 0) printf("This ierr: %d herr: %s\n", ierr, herr);
        printf("This d: %g mol/L\n", d);
        {
            double T = 293.15; double z[20] = { 0.20209999999999995, 0.7979}; int kph = 1;
            double P, rhol, rhov;
            double x[20], y[20];
            int ierr; char herr[255];
            SATTdll(T, z, kph, P, rhol, rhov, x, y, ierr, herr, 255);
            printf("This p: %g mol/L\n", p);
        }
    }

    // Call a function in another file (and load the DLL, and then unload it)
    another_file();

    return EXIT_SUCCESS;
}