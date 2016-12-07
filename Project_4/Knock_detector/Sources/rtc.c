/*
 * rtc.c
 *
 *  Created on: Dec 6, 2016
 *      Author: richa
 */
#include "rtc.h"
#include "main.h"

void Clock_Configuration (void)
{
	extern volatile int seconds_rtc, minutes_rtc;
		extern volatile uint8_t interrupt_rtc;

		interrupt_rtc = 0;
		seconds_rtc = 0;
		minutes_rtc = 0;

		SIM_SCGC5 |= SIM_SCGC5_PORTC_MASK;

	 SIM_CLKDIV1 = ( 0
	                         | SIM_CLKDIV1_OUTDIV1(0)
	                         | SIM_CLKDIV1_OUTDIV4(1) );


	MCG_C1 |= MCG_C1_IRCLKEN_MASK; //Enable internal reference clock

	MCG_C2 &= ~(MCG_C2_IRCS_MASK);  //Internal Reference Clock -->Slow

	//RTC_CLKIN
	PORTC_PCR1 |= PORT_PCR_MUX(1);       //PTC1 as RTC_CLKIN
	SIM_SOPT1 |= SIM_SOPT1_OSC32KSEL(0b10);  //32 Khz clock source for RTC

	//32k
	SIM_SOPT2 |= SIM_SOPT2_CLKOUTSEL(0b100); //Clockout pin --> 32 KHz

	PORTC_PCR3 |= (PORT_PCR_MUX(0x5)); //PTC3 as CLKOUT*/
}

void rtc_init()
{
    /*enable the clock to SRTC module register space*/
	SIM_SCGC6 |= SIM_SCGC6_RTC_MASK;

	/*Clear Registers*/
    RTC_CR  = RTC_CR_SWR_MASK;
    RTC_CR  &= ~RTC_CR_SWR_MASK;

    if (RTC_SR & RTC_SR_TIF_MASK){
        RTC_TSR = 0x00000000;   //  this action clears the TIF
    }

    /*Set time compensation parameters*/
    RTC_TCR = RTC_TCR_CIR(1) | RTC_TCR_TCR(0xFF);

    /*Enable RTC seconds irq*/
    NVIC_EnableIRQ(RTC_Seconds_IRQn);

    /*Enable Seconds Interrupt*/
    RTC_IER |= RTC_IER_TSIE_MASK; //Seconds interrupt enable

    /*Timer enable*/
    RTC_SR |= RTC_SR_TCE_MASK;

    /*Configure the timer seconds and alarm registers*/
    RTC_TSR = 0xFF;

}

/*Out pointer has the msb part and the return value is the lsb part*/
unsigned char hex_to_ascii(unsigned char hex_value, unsigned char * out)
{
    unsigned char output=0x00,temp_output1,temp_output2,m,n;
    if(hex_value<=0x09)						//For single digit hex numbers
    {
        output=(hex_value+0x30);
        *out=0x30;
    }
    else									//Split the data m is the MSB of the data; n is the LSB
    {
    m=hex_value&0x0F;
    n=hex_value&0xF0;
    n=n>>4;									//Shift n to the right so that we can work with it

        if(m<=0x09)							//Make the lsb part into hex if below 10
        {
        	output=(m+0x30);
        }
		else if(m>=0x09)
		{
			temp_output1=m-0x09;
			output=(temp_output1+0x40);
		}


        if(n<=0x09)								//Make the msb into hex
        {
        *out=(n+0x30);
        }
        else
        {
			temp_output2=n-0x09;
			*out=(temp_output2+0x40);
		}
    }
    return output;
}

void rtc_start()
{
	Clock_Configuration();
	rtc_init();
}

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
					outer=hex_to_ascii(seconds_rtc,ptr);
									print_string(ptr,1);
									print_string(&outer,1);
					print("\n\r");
					interrupt_rtc = 0;
}

void RTC_Seconds_IRQHandler(void)
{
	extern volatile int seconds_rtc,minutes_rtc;
	extern volatile uint8_t interrupt_rtc;
	interrupt_rtc = 1;
	seconds_rtc = RTC_TSR;
    if (seconds_rtc >59){
    	minutes_rtc++;
    	RTC_SR &= ~RTC_SR_TCE_MASK;
    	RTC_TSR = 0x00; //Reset counter
    	seconds_rtc = RTC_TSR;
    	RTC_SR |= RTC_SR_TCE_MASK;
    }
}

