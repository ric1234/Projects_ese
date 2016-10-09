#include<stdio.h>
#include "circbuff.h"
#include<stdint.h>


void main()

{

    uint8_t i,j,l;
    CB c,*b;
   
    printf("Enter the size of buffer you want:\n");
    scanf("%d",&l);
    
     b=&c;
  c.circ_buffer=allocate(c,l);
    begin(&c,l);
  i = rem_Item( &c);
  i = add_Item( &c, 8);

  i = add_Item( &c, 9);

  i = add_Item( &c, 10);
	  i = add_Item( &c, 10);
  i = add_Item( &c, 10);
 //Destroy(c);
 // i = add_Item( &c, 10);

   
  for(j=0;j<l;j++)
{

 

  printf("%d\t",*b->circ_buffer);
  b->circ_buffer++;
 }
printf("\n");

}

void begin(CB *cb1,size_t len)
{
    
    cb1->head=cb1->circ_buffer;
    cb1->tail=cb1->circ_buffer;
    cb1->Length=cb1->circ_buffer+(len+1);
    cb1->num_items=0;
} 

State check_Buff_Full(CB * cb, uint8_t * ahead)

{

     if(ahead == cb-> tail)//Buffer full if next the tail is after the head

          return Buffer_full;                

     else

          return Buffer_available;

               

}

 

State check_Buff_empty(CB * cb)

{

     if(cb->head == cb->tail)                                           //Buffer empty if head and tail point to same data

          return Buffer_empty;

     else

          return Buffer_available;

}

 

uint8_t add_Item(CB * cb, uint8_t data)

{              State status;
                uint8_t *next = (cb -> head)+1;
		                                             //The buffer is full
                if (next >= cb->Length)
                     next = cb->circ_buffer;                 //Wrap around to circ_buffer
                  status=check_Buff_Full(cb, next);
               if(status==Buffer_full)
              {  printf("Bufferfull\n");
		 return 1; }
             

                else

                {
                   
                    *(cb->head)=data;                                          //Adding the data to Head

                cb->head = next;                                             //Incrementing the pointer of head
                
                return 0;

                }

}

 

uint8_t rem_Item(CB * cb)

{              State status;                                                       //Check state of buffer

                uint8_t *next = cb -> tail+1;                        //Points to the next value after tail
		  if (next >= cb->Length)               //Check if tail is on the edge

                                next =cb->circ_buffer;

                status=check_Buff_empty(cb);                 //Checks for empty buffer

                if(status==Buffer_empty)
                {printf("BufferEmpty\n");
                                return ;
                    }
                  else

                                { *(cb->tail)=0;                           //Extracts data from the tail

                            

                                }

              

                cb->tail = next;

                return 0;

}

void*allocate(CB cb,uint8_t len)
{
  return cb.circ_buffer = malloc(len*sizeof(uint8_t));
}

void Destroy(CB cb)
{
  free(cb.circ_buffer);
}
