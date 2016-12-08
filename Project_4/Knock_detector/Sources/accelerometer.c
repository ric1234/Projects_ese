/*
 * accelerometer.c
 *
 *  Created on: Nov 25, 2016
 *      Author: Richard Noronha and Omkar Purandare
 * Description:	This file contains the functions of the accelerometer that works over the i2c interface.
 */
#include "accelerometer.h"
/*****************************************************************************************************************************
 *Description: 	This function initializes the accelerometer by writing to the module using I2C.
 *****************************************************************************************************************************/
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
/****************************************************************************************************************************
 * Description:	This function contains the test for the accelerometer. It is to be called when the accelerometer is to be used.
 * 				The output of this is in terms of the x, y and z coordinates.
 *
 */
/****************************************************************************************************************************/
void test_accelerometer(void)
{
		DataReady = 0;																//declared in main modified in the interrupt

		I2C_ReadMultiRegisters(MMA845x_I2C_ADDRESS, OUT_X_MSB_REG, 6, AccData);		// Read data output registers 0x01-0x06

		Xout_14_bit = ((uint16_t) (AccData[0]<<8 | AccData[1])) ;					// Compute 14-bit X-axis output value >> 2

		Yout_14_bit = ((uint16_t) (AccData[2]<<8 | AccData[3])) ;				// Compute 14-bit Y-axis output value

		Zout_14_bit = ((uint16_t) (AccData[4]<<8 | AccData[5]));				// Compute 14-bit Z-axis output value

		Xout_g = ((float) Xout_14_bit) / SENSITIVITY_2G;						// Compute X-axis output value in g's

		Yout_g = ((float) Yout_14_bit) / SENSITIVITY_2G;						// Compute Y-axis output value in g's

		Zout_g = ((float) Zout_14_bit) / SENSITIVITY_2G;						// Compute Z-axis output value in g's
		if(Zout_g < 3.8)                                        				// Checking for any kind of knocking
		{
		alert(Zout_g);  							  							//calling the logging function
		}
		delay_ms(1);
}




