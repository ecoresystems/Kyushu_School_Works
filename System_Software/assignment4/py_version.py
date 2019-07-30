# -*- eoding: utf-8 -*-
"""
Created on Fri Jun 28 13:20:40 2019

@author: Conan
"""

import csv
import numpy

A = numpy.loadtxt(open("test_matrix.csv", "rb"), delimiter=",", skiprows=0)
x0 = numpy.array([1,0,0,0,0,0,0,0,0,0,0,0])
for i in range (6):
    x0 = numpy.matmul(x0,A)
    print(x0)