#ifndef _LOG_H
#define _LOG_H
#define BBB 1
#define FRDM 0
#define LOGGER 1
#define FTOA 0
void log_0(char* data, uint32_t l);
void log_1(char* data, uint32_t l,uint32_t arch,uint32_t size);

   struct log {
	char log_data[10];
	uint32_t length;
	uint32_t Architecture;
	uint32_t DataType_size;
   }logger;

 enum architecture{
    Beagle=1,
    KL25Z=2
  }Arc;
#endif


