
#define REFPROP_IMPLEMENTATION
#include "REFPROP_lib.h"
#undef REFPROP_IMPLEMENTATION

int main()
{
    // Load the shared library
	std::string err;
    bool loaded_REFPROP = load_REFPROP(err);
	long ierr = 0, nc = 1;
	char herr[255], hfld[] = "Water.fld", hhmx[] = "HMX.BNC", href[] = "DEF";
	SETUPdll(nc,hfld,hhmx,href,ierr,herr,10000,255,3,255);

	{
		long ierr = 0;
		char herr[255];
		double z[] = {1.0}, x[] = {1.0}, y[] = {1.0}, T= 300, p = 101.325, d = NULL, dl = NULL, dv = NULL, h = NULL, s = NULL, u = NULL, cp = NULL, cv = NULL, q = NULL, w = NULL;
		TPFLSHdll(T, p, z, d, dl, dv, x, y, h,s,u,cp,cv,w,q,ierr,herr,255);
	}
    return EXIT_SUCCESS;
}