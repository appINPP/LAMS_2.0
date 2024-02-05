#!/usr/bin/env python
import os, time, sys
from util.aafabricate import *
from setup import *

sources = ['PatternTest.C', 'PatternVisualDerivatives.C','Convert.C', 'Revisit2009.C', 'spyrosTest.C','FilterTest.C', 'FindBeta.C', 'FindBeta2.C', 'TestNewPattern.C', 'FindBetaOld.C', 'FakeData.C', 'ComTests.C', 'IntHundreds.C', 'CompleteOld.C', 'CompleteNew.C', 'CalibrationTests.C']

def base( s ):
    return s.rsplit('.',1)[0]

def make_exe( s ):
    print " ===== compiling ", s 
   
    exe = base(s)
    run('g++  {gccopt} -o {exe} -I../evt {incaa} {incroot} {incjpp} {libjpp} {libroot} {libaa} {s}')
    #run('g++  {gccopt} -o {exe} -I../evt {incroot}{libroot} {s}')

def build():

    print '\n === compile code === '
    t0 = time.time()
    for s in sources : make_exe(s)
    after()
    t1 = time.time()
    
    print "\n\n---- succesfull compilation! -----"
    print " compiled regular code : %3.2f s"% (t1-t0)
    print "----------------------------------"


def clean():
    autoclean()

main(parallel_ok=True, jobs=10)

