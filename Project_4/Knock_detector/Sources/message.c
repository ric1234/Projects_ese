/*
 * message.c
 *
 *  Created on: 02-Nov-2016
 *      Author: omkar
 */
#include "main.h"

/*Function to receive the message from the terminal*/
 void message_input(CI_Msg *c)
{
uint8_t *a=(uint8_t*)c; //type casting the message structure to a byte pointer
uint8_t i;

for(i=0;i<2;i++) //Integrating through the entire message
 {
	*a=(uint8_t)receive_data_char(); //storing command and length received from the terminal
	a++;
}
for(i=0;i<(c->length-0x30);i++){
	*a=(uint8_t)receive_data_char(); //storing data received from the terminal
		a++;
}
a=a+MAX_DATA_SIZE-i;

for(i=0;i<2;i++){
	*a=(uint8_t)receive_data_char(); //storing checksum received from the terminal
		a++;
}
}


 /*Function to interpret the message coming from UART*/

 Response message_functions()
 {
	 CI_Msg Message;       //A variable for message structure
	 message_input(&Message);  //Passing variable to get the latest data
	 CI_Msg *cmd_ptr= &Message;
	 uint8_t i;
	 uint16_t calc_checksum= 0;
	 for (i= 0; i< 2+((cmd_ptr->length)-0x30); i++)  //calculating checksum
	 {
		 calc_checksum+= ((uint8_t *)(cmd_ptr))[i];
	 }
	 cmd_ptr->checksum=calc_checksum;
	 if (calc_checksum!= cmd_ptr->checksum)    //verifying checksum
	 {
	 return ERROR;  // Received an error, checksum fail
	 }
	 if((cmd_ptr->command)==RED_LED)    //for red led command
	 {
		 red();                      //Initialize red led
		 switch(cmd_ptr->data[0])      //setting brightness
		 {
		 case '0':
			 red_brightness(0xFFFF);
			 break;
		 case '1':
		 	  red_brightness(0xFF00);
		 	 break;
		 case '2':
			  red_brightness(0xF000);
			  break;
		 case '3':
			  red_brightness(0xD000);
			  break;
		 case '4':
					 red_brightness(0xB000);
					 break;
				 case '5':
				 	  red_brightness(0x9000);
				 	 break;
				 case '6':
					  red_brightness(0x5000);
					  break;
				 case '7':
					  red_brightness(0x1000);
					  break;
		 }
	 }
	 else if((cmd_ptr->command)==GREEN_LED)  //for green led command
	 {
				 green();                    //Initialize green led
				 switch(cmd_ptr->data[0])     //setting brightness
				 {
				 case '0':
					 green_brightness(0xFFFF);
					 break;
				 case '1':
				 	  green_brightness(0xFF00);
				 	 break;
				 case '2':
					  green_brightness(0xF000);
					  break;
				 case '3':
					  green_brightness(0xD000);
					  break;
				 case '4':
							 green_brightness(0xB000);
							 break;
						 case '5':
						 	  green_brightness(0x9000);
						 	 break;
						 case '6':
							  green_brightness(0x5000);
							  break;
						 case '7':
							  green_brightness(0x1000);
							  break;
				 }
	 }

	 else if((cmd_ptr->command)==BLUE_LED)
	 {
		 blue();

						 switch(cmd_ptr->data[0])
						 {
						 case '0':
							 blue_brightness(0xFFFF);
							 break;
						 case '1':
						 	  blue_brightness(0xFF00);
						 	 break;
						 case '2':
							  blue_brightness(0xF000);
							  break;
						 case '3':
							  blue_brightness(0xD000);
							  break;
						 case '4':
									 blue_brightness(0xB000);
									 break;
								 case '5':
								 	  blue_brightness(0x9000);
								 	 break;
								 case '6':
									  blue_brightness(0x5000);
									  break;
								 case '7':
									  blue_brightness(0x1000);
									  break;
						 }
	 }

	 else if((cmd_ptr->command)==ACCELEROMETER)
	 {
		 print("\r\n Your knock detector is ON");
		 while(1)
		 {
		 test_accelerometer();
		 }
	 }
	 return SUCCESS;


 }
