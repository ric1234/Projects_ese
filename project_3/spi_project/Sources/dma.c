/*
 * dma.c
 *
 *  Created on: 27-Oct-2016
 *      Author: omkar
 */

#include "main.h"
#define FOURBYTE
#define MEMZERO 1
/*memmove for 1byte mode*/
void dma_setup8(uint8_t*arr1,uint8_t*arr2,uint32_t length)
{
	SIM->SCGC6|=0x2u; //Enabling clock to DMAMUX
	SIM->SCGC7|=0x100u;//Enable clock for DMA
	DMAMUX0_CHCFG0 = 0x00; // Disable DMA Mux channel first
	DMA_SAR0 = arr1; // Set Source Address
	DMA_DSR_BCR0 |= length; //Select number of bytes to be transfered
	DMA_DCR0 &= ~(DMA_DCR_SSIZE_MASK | DMA_DCR_DSIZE_MASK);// Clear Source size and Destination size fields.
	NVIC->ISER[0]=0x1; //select interrupt for DMA channel 0
    #if MEMZERO
	DMA_DCR0 = 0x801A0000u; //Selecting 8 bit transfer mode and destination as incrementing after each transfer for memzero
    #else
	DMA_DCR0 = 0x805A0000u; //Selecting 8 bit transfer mode and source/destination as incrementing after each transfer
    #endif
	DMA_DCR0 = 0x805A0000u; //Selecting 8 bit transfer mode and source/destination as incrementing after each transfer
	DMA_DAR0 = arr2; //Setting Destination address
	DMAMUX0_CHCFG0 |= 0x39u; //Using 60th option of always enabled DMA channel for channel 0
	DMAMUX0_CHCFG0 |= 0x80u; //enable the channel
	timer_on();
	DMA_DCR0 |= 0x00010000u; //setting the start bit

}

/*memmove for 4 byte mode*/
void dma_setup32(uint32_t*arr1,uint32_t*arr2,uint32_t length)
{
	uint32_t len=length%4; // checking if bytes are divisible by 4
	length= length-len;
	SIM->SCGC6|=0x2u; //Enabling clock to DMAMUX
	SIM->SCGC7|=0x100u;//Enable clock for DMA
	DMAMUX0_CHCFG0 = 0x00; // Disable DMA Mux channel first
	DMA_SAR0 = arr1; // Set Source Address
	DMA_DAR0 = arr2; //Setting Destination address
	DMA_DSR_BCR0 |= length; //Select number of bytes to be transfered
	DMA_DCR0 &= ~(DMA_DCR_SSIZE_MASK | DMA_DCR_DSIZE_MASK);// Clear Source size and Destination size fields.
	if(len==0)
	{
#if MEMZERO
		DMA_DCR0 = 0x80080000u; //Selecting 32 bit transfer mode and destination as incrementing after each transfer for memmove
#else
		DMA_DCR0 = 0x80480000u; //Selecting 32 bit transfer mode and source/destination as incrementing after each transfer
#endif
		NVIC->ISER[0]=0x1; //select interrupt for DMA channel 0
		DMAMUX0_CHCFG0 |= 0x39u; //Using 60th option of always enabled DMA channel for channel 0
		DMAMUX0_CHCFG0 |= 0x80u; //enable the channel
		timer_on();
		DMA_DCR0 |= 0x00010000u; //setting the start bit
	}
	else
	{
#if MEMZERO
		DMA_DCR0 = 0x00080000u; //Selecting 32 bit transfer mode and destination as incrementing after each transfer for memmove
#else
		DMA_DCR0 = 0x00480000u; //Selecting 32 bit transfer mode and source/destination as incrementing after each transfer
#endif
		DMAMUX0_CHCFG0 |= 0x39u; //Using 60th option of always enabled DMA channel for channel 0
		DMAMUX0_CHCFG0 |= 0x80u; //enable the channel
		timer_on();
		DMA_DCR0 |= 0x00010000u; //setting the start bit
		//DMAMUX0_CHCFG0 = 0x00; // Disable DMA Mux channel first

    #if MEMZERO
	DMA_DCR0 = 0x801A0000u; //Selecting 8 bit transfer mode and destination as incrementing after each transfer for memzero
	DMA_DSR_BCR0 |= len; //Select number of extra bytes to be transfered
    #else
	DMA_DCR0 = 0x805A0000u; //Selecting 8 bit transfer mode and source/destination as incrementing after each transfer
	DMA_DSR_BCR0 = len; //Select number of extra bytes to be transfered
    #endif
	NVIC->ISER[0]=0x1; //select interrupt for DMA channel 0
		DMAMUX0_CHCFG0 |= 0x39u; //Using 60th option of always enabled DMA channel for channel 0
		DMAMUX0_CHCFG0 |= 0x80u; //enable the channel
		DMA_DCR0 |= 0x00010000u; //setting the start bit
	}
}

void dma_memmove(void)
  {
#ifdef ONEBYTE //arrays for 1 byte transfer mode
	uint8_t array1[5000],array2[5000];
	uint32_t length=5000;
	dma_setup8(array1,array2,length);
#endif
#ifdef FOURBYTE //arrays for 4 byte transfer mode
	uint32_t array1[3],array2[3];
	uint32_t length=10;
	dma_setup32(array1,array2,length);
#endif
  }

void dma_memzero(void)
  {
#ifdef ONEBYTE //arrays for 1 byte transfer mode
	uint8_t array[5000],zero=0;
	uint8_t* a=&zero;
	uint32_t length=5000;
	dma_setup8(a,array,length);
#endif
#ifdef FOURBYTE //arrays for 4 byte transfer mode
	uint32_t array[3],zero=0;
	uint32_t length=10;
	uint32_t* a=&zero;
	dma_setup32(a,array,length);
#endif
  }

void DMA0_IRQHandler(void)
{
	DMA_DSR_BCR0 |= 0x1000000u; //setting interrupt off
	timer_off();
	print("Time taken to memzero 10 bytes in 32-bit transfer mode is:");
	timer_print();
	if(DMA_DSR_BCR0 & 0x70000000)  //monitoring any error due to overlap of address
		print("....FAIL\n\r");
	else
		print("....SUCCESS\n\r");
	}



