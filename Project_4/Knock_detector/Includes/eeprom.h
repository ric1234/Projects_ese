/*
 * eeprom.h
 *
 *  Created on: Dec 7, 2016
 *      Author: richa
 */

#ifndef INCLUDES_EEPROM_H_
#define INCLUDES_EEPROM_H_

//added the page number field to support upto 16K bit EEPROMs
void EEPROM_WriteByte(unsigned char eeprom_Address, unsigned char eeprom_Data, unsigned char Page_Number);
unsigned char EEPROM_ReadByte(unsigned char eeprom_Address,unsigned char Page_Number);
/*void EEPROM_WriteNBytes(unsigned char EepromAddr, unsigned char *RamAddr, char NoOfBytes,unsigned char Page_Number);
void EEPROM_ReadNBytes(unsigned char EepromAddr, unsigned char *RamAddr, char NoOfBytes,unsigned char Page_Number);
void EEPROM_WriteString(unsigned char eeprom_address, unsigned char * source_address,unsigned char Page_Number);
void EEPROM_ReadString(unsigned char eeprom_address, unsigned char * destination_address,unsigned char Page_Number);
void EEPROM_Erase();*/


#define EEPROM_ID 0x50			//Actual address is 0xA0 but there is a left shift in the I2C function


#endif /* INCLUDES_EEPROM_H_ */
