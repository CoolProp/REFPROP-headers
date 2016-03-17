
#define REFPROP_IMPLEMENTATION
#include "REFPROP_lib.h"
#undef REFPROP_IMPLEMENTATION
#include <stdlib.h>

// Prototype from the other file
void another_file(void);

int main()
{
    // Load the shared library
    std::string err;
    bool loaded_REFPROP = load_REFPROP(err);
 
    char mypath[] = "/opt/refprop/";
    SETPATHdll(mypath, 400);

    long ierr = 0, nc = 1;
    char herr[255], hfld[] = "WATER.FLD", hhmx[] = "HMX.BNC", href[] = "DEF";
    SETUPdll(nc,hfld,hhmx,href,ierr,herr,10000,255,3,255);
    if (ierr > 0) printf("This ierr: %ld herr: %s\n", ierr, herr);
    {
        long ierr = 0;
        char herr[255];
        double z[] = {1.0}, x[] = {1.0}, y[] = {1.0}, T= 300, p = 101.325, d = -1, dl = -1, dv = -1, h = -1, s = -1, u = -1, cp = -1, cv = -1, q = -1, w = -1;
        TPFLSHdll(T, p, z, d, dl, dv, x, y, h,s,u,cp,cv,w,q,ierr,herr,255);
        if (ierr > 0) printf("This ierr: %ld herr: %s\n", ierr, herr);
        printf("This d: %g mol/L\n", d);
    }

    // Call a function in another file
    another_file();

    return EXIT_SUCCESS;
}