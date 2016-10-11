#include <stdio.h>
#include <stdint.h>
#include "log.h"
#include "uart.h"
#include "main.h"

void log_0(char* data, uint32_t l)
{
  char*b;
  int i;
  for(i=0;i<l;i++)
{ 
   logger.log_data[i]=*data;
   data++;
  
}
  b=logger.log_data;
  logger.length=l;
  #ifdef BBB
  for(i=0;i<logger.length;i++)
 {
  printf("%c",*b);
  b++;
 }
 printf("\n");
 #endif
#ifdef FRDM
 print_string(logger.log_data, logger.length);
#endif
}

void log_1(char* data, uint32_t l,uint32_t arch,uint32_t size)
{
  char*b;
  int i;
  for(i=0;i<l;i++)
{ 
   logger.log_data[i]=*data;
   data++;
}
  b=logger.log_data;
  logger.length=l;
  logger.DataType_size=size;
  logger.Architecture= arch;
  if(logger.Architecture==1)
  Arc=KL25Z;
  else
  Arc=Beagle;
  logger.DataType_size=size;
   #ifdef BBB
  for(i=0;i<logger.length;i++)
 {
  printf("%c",*b);
  b++;
 }
 printf("\n");
 #endif
#ifdef FRDM
 print_string(logger.log_data, logger.length);
#endif
}
