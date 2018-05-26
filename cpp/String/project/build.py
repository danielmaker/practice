#!/usr/bin/python
# -*- coding: utf-8 -*-

from __future__ import absolute_import, division, print_function

import os, sys, shutil
import argparse
import platform
import subprocess

def copyToStdOut(stream):
    for line in stream:
        print(line.decode("utf-8"), end = '')

def runProcess(processParams):
    try:
        process = subprocess.Popen(processParams, stdout = subprocess.PIPE, stderr = subprocess.STDOUT)
        while process.poll() is None:
            copyToStdOut(process.stdout)
        copyToStdOut(process.stdout)
        return process.returncode
    except:
        print("{}: {}".format(sys.exc_value, processParams))

def main(argv):
    parser = argparse.ArgumentParser()
    parser.add_argument(
        '-c', '--clean',
        action='store_true',
        help='Cleans output folder'
    )
    parser.add_argument(
        '-v', '--verbose',
        action='store_true',
        help='Enables verbose'
    )
    args = parser.parse_args(sys.argv[1:])

    outputFolder = "Output"
    topLevelPath = os.path.dirname(os.path.realpath(__file__))
    buildDir = os.path.join(topLevelPath, outputFolder)

    if args.clean:
        print("clean {} folder".format(outputFolder))
        shutil.rmtree(buildDir, ignore_errors = True)
        return 0

    if not os.path.exists(buildDir):
        os.makedirs(buildDir)
    os.chdir(buildDir)

    cmakeExe = "cmake"
    cmakeParams = [cmakeExe, topLevelPath]
    runProcess(cmakeParams)

    buildCommand = "make"
    buildCommands = [buildCommand]
    runProcess(buildCommands)


########################
# Inline part
if __name__ == "__main__":
    sys.exit(main(sys.argv))
