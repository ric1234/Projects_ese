/*
 * inter.c
 *
 *  Created on: Oct 10, 2016
 *      Author: richa
 */


#if UART_MODE == INTERRUPT
void UART0_IRQHandler (void)
{
  char c = 0;
  if (UART0_S1&UART_S1_RDRF_MASK)
  {
    c = UART0_D;
    //***********application code*************//
    switch (c){
    case ('g'):
    	color = 0;
    	break;
    case ('r'):
    	color = 1;
    	break;
    case ('b'):
    	color = 2;
    	break;
    }

    //**********************************//

    if ((UART0_S1&UART_S1_TDRE_MASK)||(UART0_S1&UART_S1_TC_MASK))
    {
    	UART0_D  = c;
    }
  }
}
#endif


