#pragma once

#include <stdio.h>
#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#define ALPHA                0.01    /* SIGNIFICANCE LEVEL */
#define isPositive(x)        ((x) >  0.e0 ?   1 : 0)
#define isNegative(x)        ((x) <  0.e0 ?   1 : 0)
#define isGreaterThanOne(x)  ((x) >  1.e0 ?   1 : 0)

void    Frequency(int n, int epsilon[]);
void    LongestRunOfOnes(int n, int epsilon[]);
void    Runs(int n, int epsilon[]);
void    Serial(int m, int n, int epsilon[]);
void    Universal(int n, int epsilon[]);
void    LinearComplexity(int M, int n, int epsilon[]);

double cephes_igamc(double a, double x);
double cephes_igam(double a, double x);
double cephes_lgam(double x);
double cephes_p1evl(double x, double *coef, int N);
double cephes_polevl(double x, double *coef, int N);
double cephes_erf(double x);
double cephes_erfc(double x);
double cephes_normal(double x);
