/*
 * spi.h
 *
 *  Created on: Oct 25, 2016
 *      Author: richa
 */

#ifndef INCLUDES_SPI_H_
#define INCLUDES_SPI_H_

#include "MKL25Z4.h"


#define CE_SHIFT		(1 << 8)

#define CE_ON			(GPIOC_PSOR = CE_SHIFT)
#define CE_OFF			(GPIOC_PCOR = CE_SHIFT)
#define CE_TOGGLE		(GPIOC_PTOR = CE_SHIFT)

#define CSN_SHIFT		(1 << 9)

#define CSN_ON			(GPIOC_PSOR = CSN_SHIFT)
#define CSN_OFF			(GPIOC_PCOR = CSN_SHIFT)
#define CSN_TOGGLE		(GPIOC_PTOR = CSN_SHIFT)

//////////////////////////////////////////////////

#define CE_IRQ_SHIFT		(0 << 10)
#define CE_IRQ_SHIFT		(0 << 10)
#define CE_IRQ_SHIFT		(0 << 10)


void spi_init(void);
void spi_master(void);
unsigned char spi_tx(unsigned char * data);



#endif /* INCLUDES_SPI_H_ */
