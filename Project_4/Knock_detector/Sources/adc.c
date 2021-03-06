/*
 * adc.c
 *
 *  Created on: 20-Nov-2016
 *      Author: Richard Noronha and Omkar Purandare
 */
#include "main.h"

/*** Inline Function to get the adc value*****/
 uint16_t inline adc_temperature(void)
 {
	 uint16_t send=0,calib=0;
SIM_SCGC6 |= SIM_SCGC6_ADC0_MASK;		//Enabling clock to ADC0

ADC0_CFG1 |= (ADC_CFG1_MODE(2)  |  	// 10 bits mode
		  ADC_CFG1_ADICLK(1)|	// Input Bus Clock divided by 2 (20-25 MHz out of reset (FEI mode) / 2)
		  ADC_CFG1_ADIV(2)|      // Clock divide by 4 (2.5-3 MHz)
		  ADC_CFG1_ADLSMP_MASK) ;	// Selecting the long sample time

ADC0_SC3 |= ADC_SC3_AVGE_MASK |		// Enable HW average
				ADC_SC3_AVGS(3)   |		// Set HW average of 32 samples
				ADC_SC3_CAL_MASK;		// Start calibration process

	while(ADC0_SC3 & ADC_SC3_CAL_MASK){} // Wait for calibration to end

		calib += ADC0_CLPS + ADC0_CLP4 + ADC0_CLP3 +
				 ADC0_CLP2 + ADC0_CLP1 + ADC0_CLP0;
		calib /= 2;
		calib |= 0x8000; 	// Set MSB
		ADC0_PG = calib;
		calib = 0;
		calib += ADC0_CLMS + ADC0_CLM4 + ADC0_CLM3 +
				 ADC0_CLM2 + ADC0_CLM1 + ADC0_CLM0;
		calib /= 2;
		calib |= 0x8000;	// Set MSB
		ADC0_MG = calib;

		ADC0_CFG1 = 0; // Reset register

		ADC0_CFG1 |= (ADC_CFG1_MODE(2)  |  	// 10 bits mode
						  ADC_CFG1_ADICLK(0)|	// Input Bus Clock (20-25 MHz out of reset (FEI mode))
						  ADC_CFG1_ADIV(1)|     // Clock divide by 2 (10-12.5 MHz)
						  ADC_CFG1_ADLSMP_MASK) ;	// Selecting the long sample time

ADC0_SC2 |= ADC_SC2_DMAEN_MASK;    // DMA Enable
ADC0_SC3 = 0; // Reset SC3
ADC0_SC1A = 0x1A;  // Select tempreture sensor as input in single ended mode
while(ADC0_SC2 & ADC_SC2_ADACT_MASK){}	 // Conversion in progress
	while(!(ADC0_SC1A & ADC_SC1_COCO_MASK)){}// Run until the conversion is complete
    dma_setup16(&ADC0_RA,&send,2);    		//using DMA
	return send ; 							//returning the ADC hex result
 }


 /***Function for calculating the exact temperature***/
float temp_calc()
{
		uint16_t raw=0;
		float Vtemp=0,Temp=0,Temp1=0,Temp2=0,Tempf=0;
	raw = adc_temperature(); //storing 10-bit temperature value
	Vtemp = raw * 0.0029296875;  //Convert the ADC reading into voltage
	if (Vtemp >= 0.7012)    //Check for Hot or Cold Slope
	{
		Temp1 =Temp_conv (Vtemp) ;
		Temp = 25 - Temp1 ;      //Cold Slope
		Tempf = ((Temp - 32)/1.8) +10;  //F to C conversion
	}
	else
	{
		Temp2 = Temp_conv (Vtemp);
		Temp = 25 - Temp2 ;   //Hot Slope)
		Tempf = ((Temp - 32)/1.8) + 10;  //F to C conversion
	}
	return Tempf;
}

/*****Function for Vtemp calculations***/
float inline Temp_conv (float a) //calling an inline function for Vtemp calculations
{
	float b = (a-0.7012)/0.001646;
	return b;
	}

