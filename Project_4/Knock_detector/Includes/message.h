/*
 * message.h
 *
 *  Created on: 02-Nov-2016
 *      Author: omkar
 */

#ifndef SOURCES_MESSAGE_H_
#define SOURCES_MESSAGE_H_
#define MAX_DATA_SIZE 10

typedef enum Cmds_t {
RED_LED = 'r',
GREEN_LED = 'g',
BLUE_LED = 'b',
ACCELEROMETER = 'a'
} Cmds;

typedef struct CI_Msg_t{
Cmds command;                       // Command operation
uint8_t length;                    // Size of the data
uint8_t data[MAX_DATA_SIZE];       // Generic data payload
uint16_t checksum;                 // Error detection checksum
} CI_Msg;



typedef enum response_t {
ERROR = 0x01, // Provides a temperature Reading
SUCCESS = 0x02, // Sets speed for a motor Controller
} Response;

void message_input(CI_Msg *c);
Response message_functions();

#endif /* SOURCES_MESSAGE_H_ */
