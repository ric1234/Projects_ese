/*
 * buffertest.c
 *
 *  Created on: 10-Oct-2016
 *      Author: omkar
 */
#include<stdio.h>
#include<stdint.h>
#include"main.h"
#include"circbuff.h"

int tests()

{

    int i,j,l=5,passes=0,fails=0;
    CB c,*b;
    State s;
    b=&c;
  print("***TESTING OF THE CIRCULARBUFFER FUCTIONS BEGINS***\n");


c.circ_buffer=allocate(c,l);
  print("\rAllocate..pass\n");
  passes=passes+1;
    begin(&c,l);



for(i=0;i<5;i++)
{
  s = add_Item( &c, i);

 }
 if(s==Buffer_available)
 {
  print("\rAdd...pass\n");
  passes=passes+1;
 }
 else if(s==Buffer_full)
  {
   print("\rAdd...fail\n");
  fails=fails+1;
  }





for(i=0;i<l;i++)
{
  s = rem_Item(&c);
 }
if(s==Buffer_available || Buffer_full)
 {
  print("\rRemove...pass\n");
  passes=passes+1;
 }
 else
  {
   print("\rRemove...fail\n");
  fails=fails+1;
  }


s = check_Buff_empty(&c);
if(s==Buffer_available || Buffer_full)
 {
  print("\rEmpty...fail\n");
  fails=fails+1;
 }
 else if(s==Buffer_empty)
  {
   print("\rEmpty...pass\n");
  passes=passes+1;
  }




s = check_Buff_Full(&c,(c.head)+1);
 if(s==Buffer_available || Buffer_empty)
 {
  print("\rFull...fail\n");
  fails=fails+1;
 }
 else if(s==Buffer_full)
  {
   print("\rFull...pass\n");
  passes=passes+1;
  }



Destroy(c);
for(j=0;j<l;j++)
{

  b->circ_buffer++;
 }
  print("\rDestroy..pass\n");
  passes=passes+1;



printf("Total fails=%d\n",fails);
printf("Total Passes=%d\n",passes);

}



