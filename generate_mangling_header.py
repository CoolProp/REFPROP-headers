with open('REFPROP_lib.h', 'r') as fp:
    lines = fp.readlines()
newfile = ''
for line in lines:
    if line.strip().startswith('X('):
        symb = line.rstrip('\\\n').strip().lstrip('X(').strip().rstrip(')')
        newfile += '#define' + ' ' + symb + ' _' + symb.lower() + '\n'
with open('REFPROP_underscore_lowercase_renaming.h', 'w') as fp:
    fp.write(newfile)