/*
 * accelerometer.c
 *
 *  Created on: Nov 25, 2016
 *      Author: richa
 */
#include "main.h"
/******************************************************************************
* MCU initialization function
******************************************************************************/

void MCU_Init(void)
{
	//I2C0 module initialization
	SIM_SCGC4 |= SIM_SCGC4_I2C0_MASK;		// Turn on clock to I2C0 module
	SIM_SCGC5 |= SIM_SCGC5_PORTE_MASK;		// Turn on clock to Port E module
	PORTE_PCR24 = PORT_PCR_MUX(5);			// PTE24 pin is I2C0 SCL line
	PORTE_PCR25 = PORT_PCR_MUX(5);			// PTE25 pin is I2C0 SDA line
	I2C0_F  = 0x14; 						// SDA hold time = 2.125us, SCL start hold time = 4.25us, SCL stop hold time = 5.125us *
	I2C0_C1 = I2C_C1_IICEN_MASK;    		// Enable I2C0 module

	//Configure the PTA14 pin (connected to the INT1 of the MMA8451Q) for falling edge interrupts

	SIM_SCGC5 |= SIM_SCGC5_PORTA_MASK;		// Turn on clock to Port A module
	PORTA_PCR14 |= (0|PORT_PCR_ISF_MASK|	// Clear the interrupt flag
					  PORT_PCR_MUX(0x1)|	// PTA14 is configured as GPIO
					  PORT_PCR_IRQC(0xA));	// PTA14 is configured for falling edge interrupts

	//Enable PORTA interrupt on NVIC

	//NVIC_ICPR |= 1 << ((PORTA_IRQn - 16)%32);
	//NVIC->ISER[0] |= 1 << ((PORTA_IRQn - 16)%32);
	//NVIC->ISER[0] |= 0x40000000;

	//NVIC_EnableIRQ(PORTA_IRQn);


}

/******************************************************************************
* Accelerometer initialization function
******************************************************************************/

void Accelerometer_Init (void)
{
	unsigned char reg_val = 0;

	/*Test = I2C_ReadRegister(MMA845x_I2C_ADDRESS, WHO_AM_I_REG);

	I2C_WriteRegister(MMA845x_I2C_ADDRESS, CTRL_REG2, 0x40);		// Reset all registers to POR values

	do		// Wait for the RST bit to clear
	{
		reg_val = I2C_ReadRegister(MMA845x_I2C_ADDRESS, CTRL_REG2) & 0x40;
	} 	while (reg_val);*/

	I2C_WriteRegister(MMA845x_I2C_ADDRESS, XYZ_DATA_CFG_REG, 0x00);		// +/-2g range -> 1g = 16384/4 = 4096 counts
	I2C_WriteRegister(MMA845x_I2C_ADDRESS, CTRL_REG2, 0x02);		// High Resolution mode
	I2C_WriteRegister(MMA845x_I2C_ADDRESS, CTRL_REG3, 0x00);		// Push-pull, active low interrupt
	I2C_WriteRegister(MMA845x_I2C_ADDRESS, CTRL_REG4, 0x01);		// Enable DRDY interrupt
	I2C_WriteRegister(MMA845x_I2C_ADDRESS, CTRL_REG5, 0x01);		// DRDY interrupt routed to INT1 - PTC5
	I2C_WriteRegister(MMA845x_I2C_ADDRESS, CTRL_REG1, 0x3D);	// ODR = 1.56Hz, Reduced noise, Active mode
}

/******************************************************************************
* Simple offset calibration
******************************************************************************/

void Calibrate (void)
{
	unsigned char reg_val = 0;

	while (!reg_val)		// Wait for a first set of data
	{
		reg_val = I2C_ReadRegister(MMA845x_I2C_ADDRESS, STATUS_REG) & 0x08;
	}

	I2C_ReadMultiRegisters(MMA845x_I2C_ADDRESS, OUT_X_MSB_REG, 6, AccData);		// Read data output registers 0x01-0x06

	Xout_14_bit = ((short) (AccData[0]<<8 | AccData[1])) >> 2;		// Compute 14-bit X-axis output value
	Yout_14_bit = ((short) (AccData[2]<<8 | AccData[3])) >> 2;		// Compute 14-bit Y-axis output value
	Zout_14_bit = ((short) (AccData[4]<<8 | AccData[5])) >> 2;		// Compute 14-bit Z-axis output value

	Xoffset = Xout_14_bit / 8 * (-1);		// Compute X-axis offset correction value
	Yoffset = Yout_14_bit / 8 * (-1);		// Compute Y-axis offset correction value
	Zoffset = (Zout_14_bit - SENSITIVITY_2G) / 8 * (-1);		// Compute Z-axis offset correction value

	I2C_WriteRegister(MMA845x_I2C_ADDRESS, CTRL_REG1, 0x00);		// Standby mode to allow writing to the offset registers
	I2C_WriteRegister(MMA845x_I2C_ADDRESS, OFF_X_REG, Xoffset);
	I2C_WriteRegister(MMA845x_I2C_ADDRESS, OFF_Y_REG, Yoffset);
	I2C_WriteRegister(MMA845x_I2C_ADDRESS, OFF_Z_REG, Zoffset);
	I2C_WriteRegister(MMA845x_I2C_ADDRESS, CTRL_REG3, 0x00);		// Push-pull, active low interrupt
	I2C_WriteRegister(MMA845x_I2C_ADDRESS, CTRL_REG4, 0x01);		// Enable DRDY interrupt
	I2C_WriteRegister(MMA845x_I2C_ADDRESS, CTRL_REG5, 0x01);		// DRDY interrupt routed to INT1 - PTA14
	I2C_WriteRegister(MMA845x_I2C_ADDRESS, CTRL_REG1, 0x3D);		// ODR = 1.56Hz, Reduced noise, Active mode
}

void test_accelerometer(void)
{
	//if (DataReady)		// Is a new set of data ready?

					DataReady = 0;		//declared in main modified in the interrupt

					I2C_ReadMultiRegisters(MMA845x_I2C_ADDRESS, OUT_X_MSB_REG, 6, AccData);		// Read data output registers 0x01-0x06

					Xout_14_bit = ((uint16_t) (AccData[0]<<8 | AccData[1])) ;		// Compute 14-bit X-axis output value >> 2
					/*ftoa(Xout_14_bit,&Xout_14_bit_in_ascii,1);
					print_string(&Xout_14_bit_in_ascii,4);
					print("\t");*/


					/*while(Xout_14_bit_in_ascii!='\0')
							  {
								  len++;
								  Xout_14_bit_in_ascii++;
							  }
					print_string(transfer, len);
					print("\t");*/

					Yout_14_bit = ((uint16_t) (AccData[2]<<8 | AccData[3])) ;		// Compute 14-bit Y-axis output value
					/*ftoa(Yout_14_bit,&Yout_14_bit_in_ascii,1);
									print_string(&Yout_14_bit_in_ascii,4);
									print("\t");*/
					/*while(Xout_14_bit_in_ascii!='\0')
											  {
												  len++;
												  b++;
											  }
									print_string(transfer, len);
									print("\t");*/

					Zout_14_bit = ((uint16_t) (AccData[4]<<8 | AccData[5]));		// Compute 14-bit Z-axis output value
					/*ftoa(Zout_14_bit,&Zout_14_bit_in_ascii,1);
									print_string(&Zout_14_bit_in_ascii,4);
									print("\t \n \r");*/
									/*while(Xout_14_bit_in_ascii!='\0')
															  {
																  len++;
																  b++;
															  }
													print_string(transfer, len);
													print("\t");*/

					Xout_g = ((float) Xout_14_bit) / SENSITIVITY_2G;		// Compute X-axis output value in g's
					/*ftoa(Xout_g,&Xout_14_bit_in_ascii,1);
										print_string(&Xout_14_bit_in_ascii,4);
										print("\t");*/
					Yout_g = ((float) Yout_14_bit) / SENSITIVITY_2G;		// Compute Y-axis output value in g's
					/*ftoa(Yout_g,&Yout_14_bit_in_ascii,1);
														print_string(&Yout_14_bit_in_ascii,4);
														print("\t");*/
					Zout_g = ((float) Zout_14_bit) / SENSITIVITY_2G;		// Compute Z-axis output value in g's
					if(Zout_g < 3.5)                                          // Checking for any kind of knocking
					{
					print("\n \r \t \t  !!!! ALERT !!!!");                  //Alert messages
					print("\n \r Excess knocking in the engine");
                    print("\n\r The knocking value is : ");
					ftoa(Zout_g,&Zout_14_bit_in_ascii,1);                    //Printing the knock value
                    print("\n \r");
					print_string(&Zout_14_bit_in_ascii,4);
					print("\n\r The engine temperature is : ");
					 ptr_temp_calc= &temp_calc;
					(*ptr_temp_calc)();                            // Calling the function to give the current engine knock value
				    }
				//else
					//print_string(&Xout_14_bit,2);
					delay_ms(1);
}


/******************************************************************************
* PORT A Interrupt handler
******************************************************************************/

void PORTA_IRQHandler()
{
	print("IN IRQ\n\r");
	PORTA_PCR14 |= PORT_PCR_ISF_MASK;			// Clear the interrupt flag write 1 to clear
	DataReady = 1;
}

