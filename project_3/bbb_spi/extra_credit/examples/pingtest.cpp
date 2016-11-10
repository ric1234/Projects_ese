/*
 Copyright (C) 2011 J. Coliz <maniacbug@ymail.com>

 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 version 2 as published by the Free Software Foundation.
 */

/**
 * Example RF Radio Ping Pair
 *
 * This is an example of how to use the RF24 class.  Write this sketch to two different nodes,
 * connect the role_pin to ground on one.  The ping node sends the current time to the pong node,
 * which responds by sending the value back.  The ping node can then see how long the whole cycle
 * took.
 */

#include <cstdlib>
#include <iostream>

#include "RF24.h"

//
// Hardware configuration
//

RF24 radio(115, 117);


// sets the role of this unit in hardware.  Connect to GND to be the 'pong' receiver
// Leave open to be the 'ping' transmitter
//const int role_pin = 7;

//
// Topology
//

// Radio pipe addresses for the 2 nodes to communicate.
//const uint64_t pipes[2] = { 0xF0F0F0F0E1LL, 0xF0F0F0F0D2LL };

//
// Role management
//
// Set up role.  This sketch uses the same software for all the nodes
// in this system.  Doing so greatly simplifies testing.  The hardware itself specifies
// which node it is.
//
// This is done through the role_pin
//

// The various roles supported by this sketch
typedef enum { role_ping_out = 1, role_pong_back } role_e;

// The debug-friendly names of those roles
//const char* role_friendly_name[] = { "invalid", "Ping out", "Pong back"};

// The role of the current running sketch
//role_e role;

void setup(void)
{
  //  role = role_ping_out;
  printf("\n\rBeginning the setup\n\r");
  radio.begin();

  // optionally, increase the delay between retries & # of retries
 // radio.setRetries(15,15);

 // radio.setChannel(0x4c);
 // radio.setPALevel(RF24_PA_MAX);

 
   // radio.openWritingPipe(pipes[0]);
    //radio.openReadingPipe(1,pipes[1]);
    // radio.startListening();
}

void loop(void)
{
    // First, stop listening. CE is off and fifos are cleared
   // radio.stopListening();

    // Take the time, and send it.  This will block until complete
    char time = 'A';
    printf("Now sending %c...",time);
	//Sets up as transmitter
    bool ok = radio.write( &time, sizeof(char) );
    
    if (ok)
      printf("ok...");
    else
      printf("failed.\n\r");


/*
    // Now, continue listening
    radio.startListening();

    // Wait here until we get a response, or timeout (250ms)
    unsigned long started_waiting_at = __millis();
    bool timeout = false;
    while ( ! radio.available() && ! timeout ) {
	__msleep(5); //add a small delay to let radio.available to check payload
      if (__millis() - started_waiting_at > 200 )
        timeout = true;
    }

    // Describe the results
    if ( timeout )
    {
      printf("Failed, response timed out.\n\r");
    }
    else
    {
      // Grab the response, compare, and send to debugging spew
      unsigned long got_time;
      radio.read( &got_time, sizeof(unsigned long) );

      // Spew it
      printf("Got response %lu, round-trip delay: %lu\n\r",got_time,__millis()-got_time);
    }

    // Try again 1s later
//    delay(1000);
sleep(1);

  //
  // Pong back role.  Receive each packet, dump it out, and send it back
  //

  if ( role == role_pong_back )
  {
    // if there is data ready
    if ( radio.available() )
    {
      // Dump the payloads until we've gotten everything
      unsigned long got_time;
      bool done = false;
      while (!done)
      {
        // Fetch the payload, and see if this was the last one.
        done = radio.read( &got_time, sizeof(unsigned long) );

        // Spew it
        printf("Got payload %lu...",got_time);

	// Delay just a little bit to let the other unit
	// make the transition to receiver
	delay(20);
      }

      // First, stop listening so we can talk
      radio.stopListening();

      // Send the final one back.
      printf("Sent response.\n\r");
      radio.write( &got_time, sizeof(unsigned long) );

      // Now, resume listening so we catch the next packets.
      radio.startListening();
    }
  }*/
}

int main(int argc, char** argv)
{
        setup();
        while(1)
	{
        loop();
	}

        return 0;
}


// vim:cin:ai:sts=2 sw=2 ft=cpp
