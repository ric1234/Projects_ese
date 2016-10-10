
#include <stdio.h>
#include <stdint.h>
#include "log.h"
#include "ftoa.h"
#include "uart.h"
#include "main.h"


#if 0
 int main()
{
	 uart0_init();
	 uart0_tx();
 int32_t len=0,i,Arch,size;
  #if FTOA
    char transfer[20];
    char *b=transfer;
    float n = 233.007;
    ftoa(n, transfer, 3);
    #else
  char transfer[]="\r\nThis is sparta";
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
  print_string(logger.log_data, logger.length);
 /* uart code*/
  #endif
  return 0 ;
}
#endif

 





