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
	extern int old_time, new_time;
	old_time=0;
	new_time=0;
		/*you can select the architecture to compile for in the main.h*/
	__disable_irq();  //function for disabling the interrupts
	uart0_init();             //function for initializing the rgb leds
	uart0_tx();               //function for initializing the transmit data*/
	uart0_rx();             //function for initializing the receive data
	//rgb_pwm_init();           //initialize rgb pwm
	i2c0_init();					//Initializes the I2C
    Accelerometer_Init();
	rtc_start();		//Connect J1 05 and J10 12 on the board

	__enable_irq();         //function for enabling the interrupts
	message_functions_ptr=&message_functions; //using function pointer for messaging
	Response msg= (*message_functions_ptr)(); //calling messaging interface


	//EEprom
	/*unsigned char out, *ptr,out2;
				ptr=&out2;

				EEPROM_WriteByte(0x04, 0x62, 0x01);
				out=EEPROM_ReadByte(0x03,0x01);
									out=hex_to_ascii(out,ptr);
									print_string(ptr,1);
									print_string(&out,1);*/


		while(1)
		{


		}
    return 0;
}


////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
