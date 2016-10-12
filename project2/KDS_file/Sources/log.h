/*
 * log.h
 *
 * Created on: Oct 8, 2016
 *     Author: Richard Noronha and Omkar Purandare
 *  University:University of Colorado Boulder
 *      Course: ECEN Fall 2016
 */
#ifndef _LOG_H
#define _LOG_H

#include <stdio.h>
#include <stdint.h>
#include "uart.h"
#include "main.h"

#define LOGGER 1
void log_0(char* data, uint32_t l);
void log_1(char* data, uint32_t l,uint32_t arch,uint32_t size);

struct log {															//Define the log structure
	char log_data[50];
	uint32_t length;
	uint32_t Architecture;
	uint32_t DataType_size;
	}logger;

enum architecture{														//Define an enum as architecture
    Beagle=1,
    KL25Z=2
	}Arc;
#endif


