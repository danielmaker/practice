#!/usr/bin/python
import os
import string
import re

def visit(arg, dir, files):
    global f
    dir = string.replace(dir, '\\','/')
    if 'svn' in dir : return          #skip svn folder
    if '.svn' in dir : return         #skip svn folder
    if 'bak' in dir : return          #skip bak folder
    if 'tmp' in dir : return          #skip tmp folder

    headers = []
    sources = []

    for file in files:
        if file.endswith('.cpp'):
            sources.append(dir+'/'+file)
        if file.endswith('.c'):
            sources.append(dir+'/'+file)


    f.write('#####################\n')
    f.write('# %s\n\n' % dir)
    f.write('include_directories( %s )\n\n' % dir)

    if sources:
       f.write('set( SOURCES ${SOURCES} ' +
            string.join(sources, ' \n           ') )
       f.write(')\n\n')

f = file('source_file.txt', 'wt')
os.path.walk('../source', visit, None)
f.close()
