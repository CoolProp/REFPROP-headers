from __future__ import print_function
import subprocess, sys, six, os, re
import numpy

def generate_interface_file(REFPROP_FORTRAN_path, interface_file_path, verbose = False, python_exe = 'python'):
    """
    Use f2py to parse PASS_FTN.FOR to generate a python-directed header file
    """
    # Call f2py to generate .pyf file
    from subprocess import Popen, PIPE
    print('Writing the .pyf file with numpy.f2py, please be patient...')
    args = [python_exe,'-m','numpy.f2py','--quiet','--no-lower','-h',interface_file_path,REFPROP_FORTRAN_path]
    # Force an overwrite if the PYF target is older than the PASS_FTN.FOR
    if os.path.exists(interface_file_path) and os.path.getmtime(interface_file_path) < os.path.getmtime(REFPROP_FORTRAN_path):
        print('The .PYF file file is older; will be over-written')
        args += ['--overwrite-signature']
    p = Popen(args, stdin=PIPE, stdout=PIPE, stderr=PIPE)
    output, err = p.communicate()
    rc = p.returncode
    # If the REFPROP.pyf file was not generated successfully, that's an error
    if not os.path.exists(interface_file_path):
        if verbose:
            print(output)
        raise ValueError('Unable to call f2py successfully: '+str(err))
        
def find_subroutine(lines, lineno):
    istart = -1; iend = -1
    for i in range(lineno, len(lines)):
        if 'subroutine' in lines[i]:
            if istart < 0 and iend < 0:
                istart = i
            elif istart >= 0 and iend < 0:
                iend = i
            else:
                break
                
    if istart < 0 and iend < 0:
        return None
    
    # Example: "subroutine pureflddll(icomp) ! in c:\Program Files (x86)\REFPROP\fortran\PASS_FTN.FOR"
    # Example: "subroutine unsetagadll ! in c:\Program Files (x86)\REFPROP\fortran\PASS_FTN.FOR"
    splitted = lines[istart].split(' ')
    sub, name_arguments = splitted[0], splitted[1]
    if '(' in name_arguments:
        name, arguments = name_arguments.split('(')
        arguments = arguments.rstrip(')').split(',')
    else:
        name, arguments = name_arguments, []    
    
    argument_list, string_arguments = [], []
    for offset, argument in enumerate(arguments):
        type, argname = lines[istart + 1 + offset].split(' :: ')

        """
        Examples:
        character*10000 intent(in) :: hfiles
        integer intent(out) :: ierr
        double precision dimension(20),intent(in) :: x0
        """
        # Split out the dimension and intent annotations
        matches = re.search(r'intent|dimension', type)
        intent_dimension = ''
        if matches:
            intent_dimension = type[matches.start(0)::]
            type = type[0:matches.start(0)]

        def get_dimension(intent_dimension):
            nummatches = re.findall(r'dimension\(+([0-9]*)\)+', intent_dimension)
            strmatches = re.findall(r'dimension\(+(\w*)\)+', intent_dimension)
            if nummatches:
                return nummatches[0]
            elif strmatches:
                return strmatches[0]
            else:
                raise ValueError('Unable to match dimension in this line:', intent_dimension)

        if 'character' in type:
            # Example: "     character*10000 :: hfld"
            if type.strip() == 'character*(*)':
                string_length = -1
            else:
                string_length = int(type.split('*')[1])
            string_arguments.append((argname.strip()+'_length', string_length))
            argument_list.append((argname.strip(), 'char *'))
        elif 'integer' in type:
            L = 0; 
            if 'dimension' in intent_dimension:
                L = get_dimension(intent_dimension)
            argument_list.append((argname.strip(), 'int *', L))
        elif 'double' in type:
            L = 0; 
            if 'dimension' in intent_dimension:
                L = get_dimension(intent_dimension)
            argument_list.append((argname.strip(), 'double *', L))
        else:
            raise ValueError(lines[istart + 1 + offset].strip())
        
    return dict(istart = istart,
                iend = iend,
                name = name,
                argument_list = argument_list,
                string_arguments = string_arguments
                )
        
def correct_name_case(name):
    """ Previously we had to modify the case; this function is a no-op now """
    return name
    
def arguments_to_string(args, string_arguments):
    outs = []
    for arg in args:
        if len(arg) == 2:
            outs.append(arg[1]+arg[0])
        elif len(arg) == 3:
            if arg[2] == 0:
                outs.append(arg[1]+arg[0])
            else:
                outs.append(arg[1]+arg[0]+'/* ' + arg[2] + " */")
        else:
            print(arg)
    for arg in string_arguments:
        outs.append('int '+arg[0]+'/* ' + str(arg[1]) + " */")
        
    return ', '.join(outs)
        
def generate_function_dict(pyf_file_path):
    """
    Returns JSON data structure for the functions
    """
    with open(pyf_file_path, 'r') as fp:
        lines = fp.readlines()
        funcs = {}
        output = True 
        istart = 0
        while output is not None:
            output = find_subroutine(lines, istart)
            if output is not None:
                funcname = correct_name_case(output['name'])
                funcs[funcname] = output
                istart = output['iend']+1
    return funcs

header = """
/*
This file was generated by a script in http://github.com/CoolProp/REFPROP-headers
originally written by Ian H. Bell, January 2016

This header should work on windows and linux
*/
"""
def write_header(function_dict, output_header_file):
    """
    Use python to parse the generated interface file
    """
    istart = 0
    ostring = header
    for function in sorted(function_dict.keys()):
        ostring += 'void ' + function + '(' + arguments_to_string(function_dict[function]['argument_list'],function_dict[function]['string_arguments']) + ');\n'

    with open(output_header_file,'w') as fp:
        fp.write(ostring)
    
if __name__=='__main__':
    # Uncomment for local testing
    # sys.argv += ['--FORTRAN-path', r'R:/FORTRAN','--keep-pyf']

    # Parse args first
    import argparse
    parser = argparse.ArgumentParser(description='Run the generator for .')
    parser.add_argument('--FORTRAN-path', nargs=1, required =True, default="", help="The directory containing the FORTRAN source files")
    parser.add_argument('--keep-pyf', nargs='?', const=True, default=False, help="If defined, the intermediate pyf file will be kept, otherwise it will be deleted")
    parser.add_argument('--python-exe', nargs=1, default=["python"], help="The python exe to be used to build the interface")
    args = parser.parse_args()

    # Change these paths as needed
    try:
        generate_interface_file(os.path.join(args.FORTRAN_path[0],'PASS_FTN.FOR'), 'REFPROP.pyf', python_exe = args.python_exe[0])
    except:
        generate_interface_file(os.path.join(args.FORTRAN_path[0],'DLLFILES','PASS_FTN.FOR'), 'REFPROP.pyf', python_exe = args.python_exe[0])
    dd = generate_function_dict('REFPROP.pyf')

    write_header(dd,'REFPROP.h')
    if not args.keep_pyf:
        print('Deleting REFPROP.pyf')
        os.remove('REFPROP.pyf')
