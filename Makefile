#Declaring variables

#The compilers
CC=gcc
#CC_BBB=arm-linux-gnueabihf-gcc 
#CC_FRDM=arm-none-eabi-gcc

#The flags

CFLAGS= -o
#GEN_ALL= -save-temps=cwd		##Saves all the temporary files generated

#OPTIONS= -Wall -g -O0 #-Arch_specific
#UPLOAD=scp 


#==============================For eabi=====================
#assemler=arm-linux-gnueabi-as


#linker
#LD_1=arm-linux-gnueabi-ld



#====================Main code starts here:
all: hello
.PHONY : all

host:
.PHONY : host

hello.exe: Omkar.o
	$(CC) Omkar.o -o Yo

Omkar.o: Omkar.c
	$(CC) -c Omkar.c

#=============Board specific===========================
bbb:

frdm:













#=======Added functionality===========#
preprocess:

asm-file:
	gcc -S *.c

%.o:
#How to do this? You have to pick out the name of the file from the command line

complile-all:
	gcc -c *.c 

build:
	ld *.o 
upload:
	scp root@10.0.0.215 /home/richard/Desktop/Making /ric

clean: 
	rm *o *.map *.out *.o *.S *.i
.PHONY : all

build-lib:
	ar -cvq libproject.a memory.c data.c		#http://www.yolinux.com/TUTORIALS/LibraryArchives-StaticAndDynamic.html
.PHONY : build-lib

