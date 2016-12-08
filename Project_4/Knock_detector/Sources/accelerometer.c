/*
 * accelerometer.c
 *
 *  Created on: Nov 25, 2016
 *      Author: richa
 */
#include "main.h"

/******************************************************************************
* Accelerometer initialization function
******************************************************************************/

void Accelerometer_Init (void)
{
	unsigned char reg_val = 0;

	I2C_WriteRegister(MMA845x_I2C_ADDRESS, XYZ_DATA_CFG_REG, 0x00);		// +/-2g range -> 1g = 16384/4 = 4096 counts
	I2C_WriteRegister(MMA845x_I2C_ADDRESS, CTRL_REG2, 0x02);		// High Resolution mode
	I2C_WriteRegister(MMA845x_I2C_ADDRESS, CTRL_REG3, 0x00);		// Push-pull, active low interrupt
	I2C_WriteRegister(MMA845x_I2C_ADDRESS, CTRL_REG4, 0x01);		// Enable DRDY interrupt
	I2C_WriteRegister(MMA845x_I2C_ADDRESS, CTRL_REG5, 0x01);		// DRDY interrupt routed to INT1 - PTC5
	I2C_WriteRegister(MMA845x_I2C_ADDRESS, CTRL_REG1, 0x3D);	// ODR = 1.56Hz, Reduced noise, Active mode
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
					alert(Zout_g);
				    }
				//else
					//print_string(&Xout_14_bit,2);
					delay_ms(1);
}


/******************************************************************************
*REMOVE if not using
******************************************************************************/

/*void PORTA_IRQHandler()
{
	PORTA_PCR14 |= PORT_PCR_ISF_MASK;			// Clear the interrupt flag write 1 to clear
	DataReady = 1;
}*/

