/*
 * i2c.h
 *
 *  Created on: Nov 19, 2016
 *      Author: richa
 */

#ifndef INCLUDES_I2C_H_
#define INCLUDES_I2C_H_

#include "MKL25Z4.h"
#include "main.h"
#include "delay.h"

#include "uart.h"
#define FRDM
#ifdef FRDM
#define print print_stringl
#endif


#define MMA8451_CTRL_REG_1	0x2A
#define MMA8451_OUT_X_MSB 0x01

#define MMA8451_F_READ_BIT_MASK	0x02
#define MMA8451_ACTIVE_BIT_MASK 0x01

/*****************************/
#define I2C_DisableAck()       I2C0_C1 |= I2C_C1_TXAK_MASK
#define I2C_EnableAck()        I2C0_C1 &= ~I2C_C1_TXAK_MASK
#define I2C_RepeatedStart()    I2C0_C1 |= I2C_C1_RSTA_MASK
#define I2C_EnterRxMode()      I2C0_C1 &= ~I2C_C1_TX_MASK
#define I2C_write_byte(data)   I2C0_D = data

#define I2C_Start()            I2C0_C1 |= I2C_C1_TX_MASK;\
                               I2C0_C1 |= I2C_C1_MST_MASK

#define I2C_Stop()             I2C0_C1 &= ~I2C_C1_MST_MASK;\
                               I2C0_C1 &= ~I2C_C1_TX_MASK

#define I2C_Wait()             while((I2C0_S & I2C_S_IICIF_MASK)==0) {} \
                               I2C0_S |= I2C_S_IICIF_MASK;


void i2c0_init(void);

unsigned char I2C_ReadRegister(unsigned char u8SlaveAddress, unsigned char u8RegisterAddress);
void I2C_ReadMultiRegisters(unsigned char u8SlaveAddress, unsigned char u8RegisterAddress, unsigned char n, unsigned char *r);
//void Pause(int number);
unsigned char I2C_ReadRegister_single(unsigned char u8SlaveAddress, unsigned char u8RegisterAddress);

void I2C_WriteRegister(unsigned char u8SlaveAddress, unsigned char u8RegisterAddress, unsigned char u8Data);


#endif /* INCLUDES_I2C_H_ */
