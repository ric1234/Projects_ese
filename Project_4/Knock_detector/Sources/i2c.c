/*
 * i2c.c
 *
 *  Created on: Nov 19, 2016
 *      Author: richa
 */
#include "i2c.h"
void i2c0_init(void)
{
	/*****I2C0 module initialization*****/
	SIM_SCGC4 |= SIM_SCGC4_I2C0_MASK;		// Turn on clock to I2C0 module
	SIM_SCGC5 |= SIM_SCGC5_PORTE_MASK;		// Turn on clock to Port E module
	PORTE_PCR24 = PORT_PCR_MUX(5);			// PTE24 pin is I2C0 SCL line
	PORTE_PCR25 = PORT_PCR_MUX(5);			// PTE25 pin is I2C0 SDA line
	I2C0_F  = 0x14; 						// SDA hold time = 2.125us, SCL start hold time = 4.25us, SCL stop hold time = 5.125us *
	I2C0_C1 = I2C_C1_IICEN_MASK;    		// Enable I2C0 module

	SIM_SCGC5 |= SIM_SCGC5_PORTC_MASK;
		PORTC_PCR8 |= PORT_PCR_MUX(2);       //PTC1 as RTC_CLKIN
		PORTC_PCR9 |= PORT_PCR_MUX(2);       //PTC1 as RTC_CLKIN



	//Configure the PTA14 pin (connected to the INT1 of the MMA8451Q) for falling edge interrupts

	SIM_SCGC5 |= SIM_SCGC5_PORTA_MASK;		// Turn on clock to Port A module
	PORTA_PCR14 |= (0|PORT_PCR_ISF_MASK|	// Clear the interrupt flag
					  PORT_PCR_MUX(0x1)|	// PTA14 is configured as GPIO
					  PORT_PCR_IRQC(0xA));	// PTA14 is configured for falling edge interrupts



}


/**************Writing data out using i2c***********/
void I2C_WriteRegister(unsigned char u8SlaveAddress, unsigned char u8RegisterAddress, unsigned char u8Data)
{
	I2C_Start();
	I2C0_D = u8SlaveAddress << 1;									/* Send I2C device address with W/R bit = 0 */
	I2C_Wait();

	I2C0_D = u8RegisterAddress;										/* Send register address */
	I2C_Wait();

	I2C0_D = u8Data;												/* Send the data */
	I2C_Wait();

	I2C_Stop();

    Pause(50);
}

/**************Reading the data from i2c*********/

unsigned char I2C_ReadRegister_single(unsigned char u8SlaveAddress, unsigned char u8RegisterAddress)
{
	unsigned char result;

	I2C_Start();
	I2C0_D = u8SlaveAddress << 1;									/* Send I2C device address with W/R bit = 0 */
	I2C_EnableAck();
	//I2C_Wait();

	I2C0_D = u8RegisterAddress;										/* Send register address */
	I2C_EnableAck();
	//I2C_Wait();

	I2C_RepeatedStart();

	I2C0_D = (u8SlaveAddress << 1) | 0x01;							/* Send I2C device address this time with W/R bit = 1 */
	I2C_EnableAck();
	//I2C_Wait();
	//I2C_EnableAck();

	I2C_EnterRxMode();
	I2C_DisableAck();

	result = I2C0_D;
	I2C_Wait();
	I2C_Stop();
	result = I2C0_D;
	Pause(50);
	return result;
}


unsigned char I2C_ReadRegister(unsigned char u8SlaveAddress, unsigned char u8RegisterAddress)
{
	unsigned char result;

	I2C_Start();
	I2C0_D = u8SlaveAddress << 1;									/* Send I2C device address with W/R bit = 0 */
	I2C_Wait();

	I2C0_D = u8RegisterAddress;										/* Send register address */
	I2C_Wait();

	I2C_RepeatedStart();

	I2C0_D = (u8SlaveAddress << 1) | 0x01;							/* Send I2C device address this time with W/R bit = 1 */
	I2C_Wait();

	I2C_EnterRxMode();
	I2C_DisableAck();

	result = I2C0_D;
	I2C_Wait();
	I2C_Stop();
	result = I2C0_D;
	Pause(50);
	return result;
}


void I2C_ReadMultiRegisters(unsigned char u8SlaveAddress, unsigned char u8RegisterAddress, unsigned char n, unsigned char *r)
{
	char i;

	I2C_Start();
	I2C0_D = u8SlaveAddress << 1;									/* Send I2C device address with W/R bit = 0 */
	I2C_Wait();

	I2C0_D = u8RegisterAddress;										/* Send register address */
	I2C_Wait();

	I2C_RepeatedStart();

	I2C0_D = (u8SlaveAddress << 1) | 0x01;							/* Send I2C device address this time with W/R bit = 1 */
	I2C_Wait();

	I2C_EnterRxMode();
	I2C_EnableAck();

	i = I2C0_D;
	I2C_Wait();

	for(i=0; i<n-2; i++)
	{
	    *r = I2C0_D;
	    r++;
	    I2C_Wait();
	}

	I2C_DisableAck();
	*r = I2C0_D;
	r++;
	I2C_Wait();
	I2C_Stop();
	*r = I2C0_D;
	Pause(50);
}
/*****************************************************************/
//Check if pause can be eliminated by using delay functions instead
void Pause(int number)
{
	int cnt;
	for(cnt=0; cnt<number; cnt++)
	{
		//asm("nop");
	};
}
/*******************************************************************/

