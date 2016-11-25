/*
 * i2c.c
 *
 *  Created on: Nov 19, 2016
 *      Author: richa
 */
#include "i2c.h"
//#include "derivative.h"

void i2c0_init(void)
{
	SIM->SCGC4 |= SIM_SCGC4_I2C0_MASK;				//turn on the clok to i2c0
	SIM->SCGC5 |= SIM_SCGC5_PORTE_MASK;				//CLock port E
	PORTE->PCR[24]= 0x0500;
	//PORTE->PCR[24]=PORT_PCR_MUX[6];				//In mask form
	PORTE->PCR[25]= 0x0500;


	I2C0->C1=0;							//Disable I2C
		I2C0->S=2;							//Clear interrupt
		I2C0->F=0x1C;						//97.09Khz @13.981Mhz bus cycle
		I2C0_C1 = I2C_C1_IICEN(1);				//I2c enable, intrrupt disabled by default
		I2C0_C1 = I2C_C1_IICIE(1);
}

void i2c0_tx_data(uint8_t ch)
{
	int i;
	//while(I2C->S & 0x20);
	//pg716
	//I2C0_A1= I2C_A1_AD(0x1D);				//Shifting and masking done in the header file

I2C0_C1 = I2C_C1_TX(1);					//Starts the transmission
	I2C0_C1 = I2C_C1_MST(1);				//Generates start bit


	I2C0_D	= 0x1D<<1;				//Slave address


//	while(!(I2C0->S & 0x02));			//Wait for transfer to complete
	I2C0->S |= 0x02;				//Clear interrupt
	if(I2C0->S & 0x10)
	{
		I2C0->S |= 0x10;
		print("Arbitration lost\n\r");
	}
	if(I2C0->S & 0x01)
	{
		print("No ack\n\r");
	}


	for(i=0;i<500;i++);		//delay



	//I2C0->D = memaddr


	I2C0_D=MMA8451_CTRL_REG_1;
	//	while(!(I2C0->S & 0x02));			//Wait for transfer to complete
		I2C0->S |= 0x02;				//Clear interrupt
		if(I2C0->S & 0x10)
		{
			I2C0->S |= 0x10;
			print("Arbitration lost\n\r");
		}
		if(I2C0->S & 0x01)
		{
			print("No ack\n\r");
		}


		for(i=0;i<500;i++);		//delay

	I2C0_D=MMA8451_ACTIVE_BIT_MASK;
	//	while(!(I2C0->S & 0x02));			//Wait for transfer to complete
		I2C0->S |= 0x02;				//Clear interrupt
		if(I2C0->S & 0x10)
		{
			I2C0->S |= 0x10;
			print("Arbitration lost\n\r");
		}
		if(I2C0->S & 0x01)
		{
			print("No ack\n\r");
		}


		for(i=0;i<500;i++);		//delay

	I2C0_C1 = I2C_C1_MST(0);			// Generates stop bit


}

void i2c0_rx_data(uint8_t ch)
{
	int i;
	//while(I2C->S & 0x20);
	//pg716
	//I2C0_A1= I2C_A1_AD(0x1D);				//Shifting and masking done in the header file

	I2C0_C1 = I2C_C1_TX(0);					//Starts the transmission
	I2C0_C1 = I2C_C1_MST(1);				//Generates start bit


	I2C0_D	= 0x1D<<1;				//Slave address




//	while(!(I2C0->S & 0x02));			//Wait for transfer to complete
	I2C0->S |= 0x02;				//Clear interrupt
	if(I2C0->S & 0x10)
	{
		I2C0->S |= 0x10;
		print("Arbitration lost\n\r");
	}
	if(I2C0->S & 0x01)
	{
		print("No ack\n\r");
	}


	for(i=0;i<500;i++);		//delay



	//I2C0->D = memaddr


	I2C0_D=MMA8451_CTRL_REG_1;
	//	while(!(I2C0->S & 0x02));			//Wait for transfer to complete
		I2C0->S |= 0x02;				//Clear interrupt
		if(I2C0->S & 0x10)
		{
			I2C0->S |= 0x10;
			print("Arbitration lost\n\r");
		}
		if(I2C0->S & 0x01)
		{
			print("No ack\n\r");
		}


		for(i=0;i<500;i++);		//delay



		I2C0_C1 |= I2C_C1_RSTA(1);
		I2C0_D	= 0x1D<<1;				//Slave address
			I2C0_D 	|= 0x01;

			for(i=0;i<500;i++);		//delay
		send_data(I2C0_D);

	I2C0_C1 = I2C_C1_MST(0);			// Generates stop bit


}



/*

es = MMA8451_WriteReg(MMA8451_CTRL_REG_1, MMA8451_ACTIVE_BIT_MASK);
while(1)
{
res = MMA8451_ReadReg(MMA8451_OUT_X_MSB, (uint8_t*)&xyz, 3);
LED1_Put(xyz[0]>50);

uint8_t MMA8451_WriteReg(uint8_t addr, uint8_t val)
{
uint8_t buf[2], res;
buf[0] = addr;
buf[1] = val;
res = I2C2_MasterSendBlock(deviceData.handle, &buf, 2U, LDD_I2C_SEND_STOP); // Send OutData (3 bytes with address) on the I2C bus and generates not a stop condition to end transmission
}

uint8_t MMA8451_ReadReg(uint8_t addr, uint8_t *data, short dataSize) {
uint8_t res;
*/
/**************************************************************************************/
void I2C_WriteRegister(unsigned char u8SlaveAddress, unsigned char u8RegisterAddress, /*unsigned*/ char u8Data)
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

void Pause(int number)
{
	int cnt;
	for(cnt=0; cnt<number; cnt++)
	{
		//asm("nop");
	};
}

