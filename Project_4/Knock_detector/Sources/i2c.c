/*
 * i2c.c
 *
 *  Created on: Nov 19, 2016
 *      Author: Richard Noronha and Omkar Purandare
 *      Description: The i2c file contains the functions that are used for the i2c protocol to communicate
 *      with the accelerometer and with the EEPROM. The master(here FRDM) generates the clock for synchronization.
 *
 */
#include "i2c.h"
/*****************************************************************************************************************************
 * Description: This function is used to initialize the i2c as well as clock the ports that will be used by the EEPROM and the Accelerometer.
 *****************************************************************************************************************************/
void i2c0_init(void)
{
	//I2C0 module initialization
	SIM_SCGC4 |= SIM_SCGC4_I2C0_MASK;		// Turn on clock to I2C0 module
	SIM_SCGC5 |= SIM_SCGC5_PORTE_MASK;		// Turn on clock to Port E module
	//Clocking port E for accelerometer
	PORTE_PCR24 = PORT_PCR_MUX(5);			// PTE24 pin is I2C0 SCL line
	PORTE_PCR25 = PORT_PCR_MUX(5);			// PTE25 pin is I2C0 SDA line

	I2C0_F  = 0x14; 						// SDA hold time = 2.125us, SCL start hold time = 4.25us, SCL stop hold time = 5.125us *
	I2C0_C1 = I2C_C1_IICEN_MASK;    		// Enable I2C0 module

	//Clocking for the port C which is used by EEPROM
	SIM_SCGC5 |= SIM_SCGC5_PORTC_MASK;
		PORTC_PCR8 |= PORT_PCR_MUX(2);       //PTC8 is SDA for EEPROM
		PORTC_PCR9 |= PORT_PCR_MUX(2);       //PTC9 is SCL for EEPROM
}
/*****************************************************************************************************************************
 * Description: This function writes data to the device that communicates with the FRDM board.
 * It starts with writing a start bit then sending the device address followed by the register in the device to write to.
 * The data is then sent on the SDA line. Finally, the stop bit is sent which tells the slave device that the communication is done.
*****************************************************************************************************************************/
void I2C_WriteRegister(unsigned char u8SlaveAddress, unsigned char u8RegisterAddress, unsigned char u8Data)
{
	I2C_Start();													//Start bit
	I2C0_D = u8SlaveAddress << 1;									// Send I2C device address with W/R bit = 0
	I2C_Wait();														//Wait for the ack

	I2C0_D = u8RegisterAddress;										// Send register address
	I2C_Wait();														//Wait for the ack

	I2C0_D = u8Data;												// Send the data
	I2C_Wait();

	I2C_Stop();														//Send stop bit

	delay_us(50);
}
/******************************************************************************************************************************
 * Description:  This function is used when an individual byte is to be read from the EEPROM.
 ******************************************************************************************************************************/
unsigned char I2C_ReadRegister_single(unsigned char u8SlaveAddress, unsigned char u8RegisterAddress)
{
	unsigned char result;

	I2C_Start();													//Start bit
	I2C0_D = u8SlaveAddress << 1;									// Send I2C device address with W/R bit = 0
	I2C_EnableAck();
	//I2C_Wait();

	I2C0_D = u8RegisterAddress;										// Send register address
	I2C_EnableAck();
	//I2C_Wait();

	I2C_RepeatedStart();

	I2C0_D = (u8SlaveAddress << 1) | 0x01;							// Send I2C device address this time with W/R bit = 1
	I2C_EnableAck();
	//I2C_Wait();
	//I2C_EnableAck();

	I2C_EnterRxMode();
	I2C_DisableAck();

	result = I2C0_D;
	I2C_Wait();
	I2C_Stop();														//Send stop bit
	result = I2C0_D;
	delay_us(50);
	return result;
}
/*****************************************************************************************************************************
 * Description:  This function is used when a byte is to be read from the Accelerometer.
*It differs from that of the EEPROM as it does not include ACKS in between the communication.
******************************************************************************************************************************/
unsigned char I2C_ReadRegister(unsigned char u8SlaveAddress, unsigned char u8RegisterAddress)
{
	unsigned char result;

	I2C_Start();													//Start bit
	I2C0_D = u8SlaveAddress << 1;									// Send I2C device address with W/R bit = 0
	I2C_Wait();

	I2C0_D = u8RegisterAddress;										// Send register address
	I2C_Wait();

	I2C_RepeatedStart();

	I2C0_D = (u8SlaveAddress << 1) | 0x01;							// Send I2C device address this time with W/R bit = 1
	I2C_Wait();

	I2C_EnterRxMode();
	I2C_DisableAck();

	result = I2C0_D;
	I2C_Wait();
	I2C_Stop();
	result = I2C0_D;
	delay_us(50);
	return result;
}

/********************************************************************************************************
 * Description: This function is used for reading multiple bytes from the slave device.
 *
 ********************************************************************************************************/
void I2C_ReadMultiRegisters(unsigned char u8SlaveAddress, unsigned char u8RegisterAddress, unsigned char n, unsigned char *r)
{
	char i;

	I2C_Start();
	I2C0_D = u8SlaveAddress << 1;									// Send I2C device address with W/R bit = 0
	I2C_Wait();														//Wait for the ack

	I2C0_D = u8RegisterAddress;										// Send register address
	I2C_Wait();														//Wait for the ack

	I2C_RepeatedStart();

	I2C0_D = (u8SlaveAddress << 1) | 0x01;							// Send I2C device address this time with W/R bit = 1
	I2C_Wait();														//Wait for the ack

	I2C_EnterRxMode();
	I2C_EnableAck();

	i = I2C0_D;
	I2C_Wait();														//Wait for the ack

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
	delay_us(50);
}

