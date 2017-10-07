#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <math.h>
#include <float.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>

double log_sum(double log_a, double log_b);
double trigamma(double x);
double digamma(double x);
double loggamma(double x);
void make_directory(char* name);
int argmax(double* x, int n);

char *strconcat(const char *s, const char *t);

#endif


#ifndef GAMMA_H
#define GAMMA_H

// Note that the functions Gamma and LogGamma are mutually dependent.
double lgamma(double);
double Gamma(double);

#endif