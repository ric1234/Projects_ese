/*
 * Rx_Tx_buff.c
 *
 *  Created on: 10-Oct-2016
 *      Author: Richard Noronha and Omkar Purandare
 *  University:University of Colorado Boulder
 *      Course: ECEN Fall 2016
 */
/*Description: This file contains a function that interfaces the circular buffer to the main code*/
#include "Rx_Tx_buff.h"

void circBuff (void)

{
	//tests();												//Function to test the circular buffer. Not always required.
	int j,length_rx=20,length_tx=20,len=0;
	uint8_t Data_Rx_out,Data_Tx_in,Data_Tx_out;
	CB Rx,Tx;												//Rx is the Receive circular buffer
	char rec[20];											//Temporary buffer to take in the data
	State s;												//Enum representing the state of the buffer
	Rx.circ_buffer=allocate(Rx,length_rx);					//Memory allocation in receive buffer
	Tx.circ_buffer=allocate(Tx,length_tx);					//Memory allocation in transmit buffer
	begin(&Rx,length_rx);									//Start the rx buffer
	begin(&Tx,length_tx);									//Start the tx buffer
	len=receive_data(rec);									//Call the function to recieve the data. Data length is tored in len
	for(j=0;j<len;j++)
	{
		s = add_Item( &Rx, rec[j]);							//Add Items to the circular buffer
	}

	for(j=0;j<len;j++)
	{
		Data_Rx_out= rem_Item(&Rx);							//Remove data from the circular buffer
		s= add_Item(&Tx,Data_Rx_out);						//Copy data to the transmit buffer
	}
	for(j=0;j<len;j++)
	{
		Data_Tx_out = rem_Item( &Tx);						//Remove data from Tx buffer
		send_data(Data_Tx_out);								//Write data to the UART terminal
	}

}



