
#include "REFPROP_lib.h"
#include <stdlib.h>
#include <stdio.h>

void another_file(const std::string & path, const std::string &DLL_file)
{

    // Load the shared library
    std::string err;
    bool loaded_REFPROP = load_REFPROP(err, path, DLL_file);
    printf("Loaded refprop (in other.cpp): %s @ address %zu\n", loaded_REFPROP ? "true" : "false", REFPROP_address());

    int ierr = 0, nc = 1;
    char herr[255], hfld[10000] = "R32.FLD", hhmx[255] = "HMX.BNC", href[255] = "DEF";
    SETUPdll(nc,hfld,hhmx,href,ierr,herr,10000,255,3,255);
    if (ierr > 0) printf("Other ierr: %ld herr: %s\n", ierr, herr);
    {
        int ierr = 0;
        char herr[255];
        double z[20] = {1.0}, x[20] = {1.0}, y[20] = {1.0}, T= 300, p = 101.325, d = -1, dl = -1, dv = -1, h = -1, s = -1, u = -1, cp = -1, cv = -1, q = -1, w = -1;
        TPFLSHdll(T, p, z, d, dl, dv, x, y, h,s,u,cp,cv,w,q,ierr,herr,255);
        if (ierr > 0) printf("Other ierr: %ld herr: %s\n", ierr, herr);
        printf("Other d: %g mol/L\n", d);
    }

    bool unloaded_REFPROP = unload_REFPROP(err);
    printf("Unloaded refprop (in other.cpp): %s\n", loaded_REFPROP ? "true" : "false");
}