/*
 * Rx_Tx_buff.c
 *
 *  Created on: 10-Oct-2016
 *      Author: omkar
 */
#include<stdio.h>
#include<stdint.h>
#include"circbuff.h"
#include "main.h"

void circBuff ()

{
	tests();
    int i,j,length_rx=10,length_tx=10;
    uint8_t Data_Rx_out,Data_Tx_in,Data_Tx_out;
    CB Rx,Tx;
    char rec[10];
    State s;
  Rx.circ_buffer=allocate(Rx,length_rx);
  Tx.circ_buffer=allocate(Tx,length_tx);
    begin(&Rx,length_rx);
     begin(&Tx,length_tx);
     receive_data(rec);
for(j=0;j<5;j++)
{
 s = add_Item( &Rx, rec[j]);
}

 for(j=0;j<5;j++)
{
 Data_Rx_out= rem_Item(&Rx);
 s= add_Item(&Tx,Data_Rx_out);
}
for(j=0;j<5;j++)
{
 Data_Tx_out = rem_Item( &Tx);
 send_data(Data_Tx_out);
}

}



