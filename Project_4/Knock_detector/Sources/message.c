/*
 * message.c
 *
 *  Created on: 02-Nov-2016
 *      Author: omkar
 */
#include "main.h"

/*****Function to receive the message from the terminal*******/
  void inline message_input(CI_Msg *c)
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

}


 /*****Function to interpret the message coming from UART*****/

 Response message_functions()
 {
	 while(1)
	 {
			extern int old_time, new_time;  // old and new times
			old_time=0;
			new_time=0;
	 print("\r\nEnter the command you want to run:\n");
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

     if((cmd_ptr->command)==ACCELEROMETER)
	 {
		 print("\r\n Your knock detector is ON");
		 uart0_rx_int_based();			          	//Uart receive is interrupt handled
		 while(1)
		 {
			ptr_test_accelerometer= &test_accelerometer;
		  (*ptr_test_accelerometer)();                  //calling the test accelerometer
		  if(superuser)                               //if input to shut the accelerometer is received
		  {
			  uart0_rx();
			  superuser=0;
			  print("\n\rYour knock detector is OFF");
			  break;                                     //go back to the messaging interface
		  }
		 }
	 }
	 }
	 return SUCCESS;


 }
