
#include <stdio.h>
#include <stdint.h>
#include "log.h"
#include "ftoa.h"
 int main()
{
 int32_t len=0,i,Arch,size;
  #if FTOA
    char transfer[20];
    char *b=transfer;
    float n = 233.007;
    ftoa(n, transfer, 3);
    #else
  char transfer[]="omirocks";
  char *b=transfer;
  #endif
  while(*b!='\0')
  {
  len++;
  b++;
  }
  size=sizeof(char);
  #if FRDM
  Arch=1;
  #else
  Arch=2;
  #endif
  #if LOGGER
  log_1(transfer,len,Arch,size);
  #else
  return 1;
  #endif
 /* uart code*/
  return 0 ;
}
 





