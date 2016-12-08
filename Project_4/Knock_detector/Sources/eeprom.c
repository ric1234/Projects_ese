/*
 * eeprom.c
 *
 *  Created on: Dec 7, 2016
 *      Author: richa
 */
/*
 * eeprom.c
 *
 *  Created on: Dec 1, 2016
 *      Author: Richard Noronha and Omkar Purandare
 */

#include"i2c.h"



/*
Description:This function is used to write the data at specified EEPROM_address..
               At2404 ic is enabled by sending its ID on the i2c bus.
               After selecting At2404 ic,select the address where the data is to written
               Write the Data at selected EppromAddress
               Stop the I2c communication.
----------------------------------------------------------------------------------------*/
void EEPROM_WriteByte(unsigned char eeprom_Address, unsigned char eeprom_Data, unsigned char Page_Number)
{
	I2C_WriteRegister(EEPROM_ID | Page_Number, eeprom_Address, eeprom_Data);
}


/*-----------------------------------------------------------------------------------------
               unsigned char EEPROM_ReadByte(unsigned char eeprom_Address)
 ------------------------------------------------------------------------------------------
 * I/P Arguments: char-->eeprom_address from where eeprom_data is to be read.
 * Return value	: char-->data read from Eeprom.

 * description:
           This function is used to read the data from specified EEPROM_address.
           At2404 ic is enabled by sending its ID on the i2c bus.
           After selecting At2404 ic,select the address from where the data is to read
           Read the Data from selected EppromAddress
           Stop the I2c communication.
           Return the Data read from Eeprom
-----------------------------------------------------------------------------------------*/
unsigned char EEPROM_ReadByte(unsigned char eeprom_Address,unsigned char Page_Number)
{
  unsigned char eeprom_Data;

  eeprom_Data=I2C_ReadRegister(EEPROM_ID | Page_Number, eeprom_Address);
  return eeprom_Data;          // Return the Read data

}






/*---------------------------------------------------------------------------------------
void EEPROM_Write_multiple_Bytes(unsigned char EepromAddr, unsigned char *RamAddr, char NoOfBytes)
 ----------------------------------------------------------------------------------------
 * I/P Arguments: char,-->eeprom_address from where the N-bytes are to be written.
                  char*-->Pointer to the N-bytes of data to be written.
                  char --> Number of bytes to be written

 * Return value	: none

 * description:
            This function is used to write N-bytes of data at specified EEPROM_address.
            EEPROM_WriteByte() function is called to write a byte at atime.
            Source(RAM) and destination(EEPROM) address are incremented after each write
            NoOfBytes is Decemented each time a byte is written.
            Above Operation is carried out till all the bytes are written(NoOfBytes!=0)
---------------------------------------------------------------------------------------*/
/*****************************************************************************************/

/*****************************************************************************************/
//Written in report
/*****************************************************************************************/
/*void EEPROM_Write_multiple_Bytes(unsigned char EepromAddr, unsigned char *RamAddr, char NoOfBytes, unsigned char Page_Number)
 {
  while(NoOfBytes !=  0)
   {
	EEPROM_WriteByte(EepromAddr,*RamAddr,Page_Number); //Write a byte from RAM to EEPROM
	    EepromAddr++;					   //Incerement the Eeprom Address
		RamAddr++;						   //Increment the RAM Address
		NoOfBytes--;					   //Decrement NoOfBytes after writing each Byte
	   }
 }*/



/*---------------------------------------------------------------------------------------
void EEPROM_Read_multiple_Bytes(unsigned char EepromAddr, unsigned char *RamAddr, char NoOfBytes)
 ----------------------------------------------------------------------------------------
 * I/P Arguments: char,-->eeprom_address from where the N-bytes is to be read.
                  char*-->Pointer into which the N-bytes of data is to be read.
                  char --> Number of bytes to be Read

 * Return value	: none

 * description:
            This function is used to Read N-bytes of data from specified EEPROM_address.
            EEPROM_ReadByte() func is called to read a byte at a time.
            Source(RAM) and destination(EEPROM) address are incremented each time.
            NoOfBytes is Decemented after a byte is read.
            Above Operation is carried out till all the bytes are read(NoOfBytes!=0)
---------------------------------------------------------------------------------------*/
/*void EEPROM_Read_multiple_Bytes(unsigned char EepromAddr, unsigned char *RamAddr, char NoOfBytes,unsigned char Page_Number)
 {
   while(NoOfBytes !=  0)
	{
	 *RamAddr = EEPROM_ReadByte(EepromAddr,Page_Number);//Read a byte from EEPROM to RAM
	    EepromAddr++;						//Incerement the Eeprom Address
	 	RamAddr++;							//Increment the RAM Address
	 	NoOfBytes--;						//Decrement NoOfBytes after Reading each Byte

	 }
 }

*/





/*---------------------------------------------------------------------------------------
 void EEPROM_WriteString(unsigned char eeprom_address, unsigned char * source_address)
 ----------------------------------------------------------------------------------------
 * I/P Arguments: char,-->eeprom_address where the String is to be written.
                  char*-->Pointer to String which has to be written.

 * Return value	: none

 * description:This function is used to Write a String at specified EEPROM_address.
               EEPROM_WriteByte() function is called to write a byte at a time.
               Source(RAM) and destination(EEPOM) address are incremented each time.
               Above Operation is carried out till Null char is identified.

   NOTE: Null char is also written into the eeprom.
---------------------------------------------------------------------------------------*/
void EEPROM_WriteString(unsigned char eeprom_address, unsigned char * source_address,unsigned char Page_Number)
  {

   do
 	{
 	  EEPROM_WriteByte(eeprom_address,*source_address,Page_Number); //Write a byte from RAM to EEPROM
 	    source_address++;								//Incerement the RAM Address
 		eeprom_address++;								//Increment the Eeprom Address
 	  }while(*(source_address-1) !=0);
  }





/*---------------------------------------------------------------------------------------
void EEPROM_ReadString(unsigned char eeprom_address, unsigned char * destination_address)
 ----------------------------------------------------------------------------------------
 * I/P Arguments: char,-->eeprom_address from where the String is to be read.
                  char*-->Pointer into which the String is to be read.

 * Return value	: none

 * description:This function is used to Read a String from specified EEPROM_address.
               EEPROM_ReadByte() function is called to read a byte at a time.
               Source(EEPROM) and destination(RAM) address are incremented each time.
               Above Operation is carried out till Null char is identified.
---------------------------------------------------------------------------------------*/
void EEPROM_ReadString(unsigned char eeprom_address, unsigned char * destination_address,unsigned char Page_Number)
  {
   char eeprom_data;

     do
 	 {
	  eeprom_data = EEPROM_ReadByte(eeprom_address,Page_Number); //Read a byte from EEPROM to RAM
 	    *destination_address = eeprom_data;			 //Copy the data into String Buffer
 	     destination_address++;						 //Incerement the RAM Address
 	 	 eeprom_address++;							 //Increment the Eeprom Address
 		}while(eeprom_data!=0);
  }





/*-----------------------------------------------------------------------------------------
                                   void EEPROM_Erase()
 ------------------------------------------------------------------------------------------
 * I/P Arguments: none

 * Return value	: none

 * description:This function is used to erase the entire Eeprom memory.
               Eeprom is filled with 0xFF to accomplish the Eeprom Erase.
               EEPROM_WriteByte() function is called to write a byte at a time.
               Whole memory(0-255) is traversed and filled with 0xFF
-----------------------------------------------------------------------------------------*/
  void EEPROM_Erase()
   {
	 unsigned char eeprom_address;
	 unsigned char page;

	 for(eeprom_address=0;eeprom_address<255;eeprom_address++)
        for(page=0;page<3;page++)
	    {
		   EEPROM_WriteByte(eeprom_address,0xff,page); // Write Each memory location with OxFF
        }
   }












