"""
A script to scrape all the function exports from the PASS_FTN.FOR

By Ian Bell, NIST, January 2018
"""
import os
from generate_header import generate_interface_file, generate_function_dict

if __name__=='__main__':
    generate_interface_file('R:/FORTRAN/PASS_FTN.FOR','REFPROP.PYF',verbose=False,python_exe='python')    
    funcs = generate_function_dict('REFPROP.PYF')
    for func in sorted(funcs):
        print('    X(' + func + ') \\')

    for func in sorted(funcs):
        string_lengths = []
        types = []
        for arg in funcs[func]['argument_list']:
            if len(arg) == 3:
                name, _type, size = arg
            else:
                name, _type = arg
                size = 0
            if _type == 'double *' and size == 0:
                types.append('DOUBLE_REF')
            elif _type == 'double *' and size != 0:
                types.append('double *')
            elif _type == 'int *' and size == 0:
                types.append('INT_REF')
            elif _type == 'int *' and size != 0:
                types.append('int *')
            elif _type == 'char *':
                types.append('char *')
                string_lengths.append('RP_SIZE_T')
            else: 
                print(types)
                raise ValueError()
        print(' '*4+'#define '+func+'_ARGS '+','.join(types+string_lengths))