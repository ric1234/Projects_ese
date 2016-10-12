/*
 * ftoa.h
 *
 * Created on: Oct 1, 2016
 *     Author: Richard Noronha and Omkar Purandare
 *  University:University of Colorado Boulder
 *      Course: ECEN Fall 2016
 */
#ifndef _FTOA_H
#define _FTOA_H
#define FTOA 1

#include<stdio.h>

void reverse(char *str, int len);
int intToStr(int x, char str[], int d);
void ftoa(float n, char *res, int afterpoint);
int power(int a, int n);

#endif
