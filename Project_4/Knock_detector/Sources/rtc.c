/*
 * rtc.c
 *
 *  Created on: Dec 6, 2016
 *      Author: richa
 */
#include "main.h"
/*Description:  This function initializes the clocking and the ports used by the Real Time Clock.
 *
 * */
void Clock_Config_rtc (void)
{
	extern volatile int seconds_rtc, minutes_rtc;
	extern volatile uint8_t interrupt_rtc;

	interrupt_rtc = 0;
	seconds_rtc = 0;
	minutes_rtc = 0;


	SIM_SCGC5 |= SIM_SCGC5_PORTC_MASK;				//Gating the clock of port3
	SIM_CLKDIV1 = ( SIM_CLKDIV1_OUTDIV1(0)| SIM_CLKDIV1_OUTDIV4(1) );
	MCG_C1 |= MCG_C1_IRCLKEN_MASK; //Enable internal reference clock
	MCG_C2 &= ~(MCG_C2_IRCS_MASK);  //Internal Reference Clock -->Slow

	//RTC_CLKIN
	PORTC_PCR1 |= PORT_PCR_MUX(1);       //PTC1 as RTC_CLKIN
	SIM_SOPT1 |= SIM_SOPT1_OSC32KSEL(0b10);  //32 Khz clock source for RTC

	//Setting the oscillator cloak at 32kHz
	SIM_SOPT2 |= SIM_SOPT2_CLKOUTSEL(0b100); //Clockout pin --> 32 KHz

	PORTC_PCR3 |= (PORT_PCR_MUX(0x5)); //PTC3 as CLKOUT*/
}
/*Description:
 * This function initializes the Real Time Clock. It also enables the interrupt used by the RTC.
 */
void rtc_init()
{

	SIM_SCGC6 |= SIM_SCGC6_RTC_MASK;		//enable the clock to SRTC module register space
    RTC_CR  = RTC_CR_SWR_MASK;				//Clear Registers
    RTC_CR  &= ~RTC_CR_SWR_MASK;			//Clear Registers
    if (RTC_SR & RTC_SR_TIF_MASK){
        RTC_TSR = 0x00000000;   			//  this action clears the TIF
    }
    RTC_TCR = RTC_TCR_CIR(1) | RTC_TCR_TCR(0xFF);	  //Set time compensation parameters

    NVIC_EnableIRQ(RTC_Seconds_IRQn);				//Enable RTC seconds irq

    RTC_IER |= RTC_IER_TSIE_MASK; //Seconds interrupt enable
    RTC_SR |= RTC_SR_TCE_MASK;						//Timer enable
    RTC_TSR = 0xFF;									//Configure the timer seconds and alarm registers
}

/*Desciption:	This function calls the above two function in succession so as to properly initialize the RTC.
 * This function might be called directly for initiating the RTC.
 */
void rtc_start()
{
	Clock_Config_rtc();
	rtc_init();
}
/*Funtion to test the working of RTC*/
void print_rtc()
{
	extern volatile int seconds_rtc,minutes_rtc;
	extern volatile uint8_t interrupt_rtc;
	char * ptr;
	char a,outer,inner;

	ptr=&a;
	outer=hex_to_ascii(minutes_rtc,ptr);
	print_string(ptr,1);
	print_string(&outer,1);
	print(":");
	outer=hex_to_ascii(seconds_rtc,ptr);			//Convert data to ascii to print in uart
	print_string(ptr,1);
	print_string(&outer,1);
	print("\n\r");
	interrupt_rtc = 0;
}

void RTC_Seconds_IRQHandler(void)
{
	extern volatile int seconds_rtc;
	seconds_rtc = RTC_TSR;

}

