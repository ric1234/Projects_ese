/*
 * ftoa.c
 *
 *  Created on: 27-Oct-2016
 *      Author: Richard Noronha and Omkar Purandare
 */
#include"main.h"

/*Function to reverse the string*/
void reverse(char *str, int len)
{
    int i=0, j=len-1, temp;
    while (i<j)
    {
    	temp = str[i];
        str[i] = str[j];
        str[j] = temp;
        i++;
        j--;
    }
}

/* Converts a given integer x to string str[].  d is the number of digits required in output. If d is more than the number
  of digits in x, then 0s are added at the beginning.*/
int intToStr(int x, char str[], int d)
{
    int i = 0;
    while (x)
    {
        str[i++] = (x%10) + '0';
        x = x/10;
    }
    /*If number of digits required is more, then add 0s at the beginning*/
    while (i < d)
        str[i++] = '0';

    reverse(str, i);
    str[i] = '\0';
    return i;
}

/*Converts a floating point number to string.*/
void ftoa(float n, char *res, int afterpoint)
{
    int ipart = (int)n;									// Extract integer part
    float fpart = n - (float)ipart;						// Extract floating part
    int i = intToStr(ipart, res, 0);					// convert integer part to string

    /*Check for display option after point*/
    if (afterpoint != 0)
    {
        res[i] = '.';  									// add dot

        /*Get the value of fraction part upto given no.
        /of points after dot. The third parameter is needed
        to handle cases like 233.007*/
        fpart = fpart * power(10, afterpoint);
        intToStr((int)fpart, res + i + 1, afterpoint);
    }
}

/*Function to perform the exponential part*/
int power(int a, int n)
{
  int i,b=1;
  for(i=0;i<n;i++)
   b=b*a;
  return b;

 }

/*Out pointer has the msb part and the return value is the lsb part*/
unsigned char hex_to_ascii(unsigned char hex_value, unsigned char * out)
{
    unsigned char output=0x00,temp_output1,temp_output2,m,n;
    if(hex_value<=0x09)						//For single digit hex numbers
    {
        output=(hex_value+0x30);
        *out=0x30;
    }
    else									//Split the data m is the MSB of the data; n is the LSB
    {
    m=hex_value&0x0F;
    n=hex_value&0xF0;
    n=n>>4;									//Shift n to the right so that we can work with it

        if(m<=0x09)							//Make the lsb part into hex if below 10
        {
        	output=(m+0x30);
        }
		else if(m>=0x09)
		{
			temp_output1=m-0x09;
			output=(temp_output1+0x40);
		}


        if(n<=0x09)								//Make the msb into hex
        {
        *out=(n+0x30);
        }
        else
        {
			temp_output2=n-0x09;
			*out=(temp_output2+0x40);
		}
    }
    return output;
}

/*******function to convert int to ascii******/
uint16_t my_itoa(char * str, int data)
{
 uint16_t num_digits=0;
   while(data!=0) //Using traditional divding way to get integers seperately
   {
     *str= data%10; //dividing by 10 multiple times and storing reminders to get each integer
     *str=(*str)+0x30;					//Conversion to ascii
     data= data/10;
     str++;
     num_digits++;
   }
   str=str-num_digits;
   reverse(str,num_digits);
   return num_digits;
}








