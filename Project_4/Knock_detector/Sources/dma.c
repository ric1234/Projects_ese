/*
 * dma.c
 *
 *  Created on: 27-Oct-2016
 *      Author: Richard Noronha and Omkar Purandare
 */

#include "main.h"
#define MEMMOVE 1
/*memmove for 1byte mode*/
void dma_setup16(uint16_t*arr1,uint16_t*arr2,uint32_t length)
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
	DMA_DCR0 = 0x806C0000u; //Selecting 16 bit transfer mode and source/destination as incrementing after each transfer
    #endif
	DMA_DAR0 = arr2; //Setting Destination address
	DMAMUX0_CHCFG0 |= 0x39u; //Using 60th option of always enabled DMA channel for channel 0
	DMAMUX0_CHCFG0 |= 0x80u; //enable the channel
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


void DMA0_IRQHandler(void)
{
	DMA_DSR_BCR0 |= 0x1000000u; //setting interrupt off
		if(DMA_DSR_BCR0 & 0x70000000)  //monitoring any error due to overlap of address
			print("DMA TRANSFER FAILURE\n\r"); //logging error message
	}



