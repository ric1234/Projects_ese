/*
 * SpecialProcess.c
 *
 *  Created on: 11-Oct-2016
 *      Author: omkar
 */

#include <stdio.h>
#include <stdint.h>
#include "main.h"
#define decimal


 void Specialprocessing()
{
 print("This is a floating point number:");   //the message you want to print goes here
#ifdef decimal                                //if you want to print an float after the message use this option
 char transfer[20];
     char *b=transfer;
     int len=0;
     float n = 1543.321;
     ftoa(n, transfer, 3);                 //calling the ftoa for converting into ASCII
   while(*b!='\0')                         //calculating length
   {
   len++;
   b++;
   }
  #endif
#ifdef integer                          //if you want to print an integer after the message use this option
   uint8_t a=200;
   uint32_t c=(uint32_t)a;
   char transfer[20];
   char *b=transfer;
        int len=0;

        my_itoa( transfer,c,10);      //calling itoa , will only work if file data.h is included
      while(*b!='\0')
      {
      len++;
      b++;
      }
#endif
   print_string(transfer,len);        //print the entire string out

}












