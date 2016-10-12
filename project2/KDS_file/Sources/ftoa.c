/*
 * ftoa.c
 *
 * Created on: Oct 1, 2016
 *     Author: Richard Noronha and Omkar Purandare
 *  University:University of Colorado Boulder
 *      Course: ECEN Fall 2016
 */

#include"ftoa.h"

/*Function to reverse the string*/
void reverse(char *str, int len)
{
    int i=0, j=len-1, temp;
    while (i<j)
    {
    	temp = str[i];
        str[i] = str[j];
        str[j] = temp;
        i++;
        j--;
    }
}
 
/* Converts a given integer x to string str[].  d is the number of digits required in output. If d is more than the number
  of digits in x, then 0s are added at the beginning.*/
int intToStr(int x, char str[], int d)
{
    int i = 0;
    while (x)
    {
        str[i++] = (x%10) + '0';
        x = x/10;
    }
    /*If number of digits required is more, then add 0s at the beginning*/
    while (i < d)
        str[i++] = '0';
 
    reverse(str, i);
    str[i] = '\0';
    return i;
}
 
/*Converts a floating point number to string.*/
void ftoa(float n, char *res, int afterpoint)
{
    int ipart = (int)n;									// Extract integer part
    float fpart = n - (float)ipart;						// Extract floating part
    int i = intToStr(ipart, res, 0);					// convert integer part to string
 
    /*Check for display option after point*/
    if (afterpoint != 0)
    {
        res[i] = '.';  									// add dot
 
        /*Get the value of fraction part upto given no.
        /of points after dot. The third parameter is needed
        to handle cases like 233.007*/
        fpart = fpart * power(10, afterpoint);
        intToStr((int)fpart, res + i + 1, afterpoint);
    }
}

/*Function to perform the exponential part*/
int power(int a, int n)
{
  int i,b=1;
  for(i=0;i<n;i++)
   b=b*a;
  return b;
	
 }
