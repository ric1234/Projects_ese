/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
/*
 * main.c
 *
 * Created on: Sept 26, 2016
 *     Author: Richard Noronha and Omkar Purandare
 *  University:University of Colorado Boulder
 *      Course: ECEN Fall 2016
 */
#include "main.h"


int main(void)
{

	/*you can select the architecture to compile for in the main.h*/
	__disable_irq();  //function for disabling the interrupts
	uart0_init();             //function for initializing the rgb leds
	uart0_tx();               //function for initializing the transmit data*/
	uart0_rx();             //function for initializing the receive data
    //profile_timer_init();   //function for initializing the time profiling*/
	//rgb_pwm_init();           //initialize rgb pwm
	MCU_Init();
    Accelerometer_Init();
	__enable_irq();         //function for enabling the interrupts
	//dma_memmove();          //test memmove based on dma
	/*dma_memzero();          //test memmove based on dma*/
	Response msg= message_functions(); //calling messaging interface
	//Initialize Spi as a master
	//spi_init();
	//spi_master();

	//temp_calc();

	/*
	 * Accelerometer part
	 */


	/**************************/
	while(1)
	{
		//test_accelerometer();
		//nrf_config_tx();
		//delay_us(500);

		/*//For required elements:
		 nrf_test();
		 */

		/*Extra Credit: Set as receiver nrf module*/
		/*nrf_air_rx();
		while(1)
		{
			nrf_fifo_status();

		}*/


	}
    return 0;
}


////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
