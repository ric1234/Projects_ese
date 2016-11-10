

#include <cstdlib>
#include <iostream>

#include "RF24.h"

//
// Hardware configuration
//

RF24 radio(115, 117);


void setup(void)
{
printf("Let this begin\n\r");


  radio.begin();  

 

  //
  // Start listening
  //

  radio.startListening();

}


int main(int argc, char** argv)
{
 
        while(1)
                setup();

        return 0;
}


