#Declaring variables

#The compilers
CC=gcc
#CC_BBB=arm-linux-gnueabihf-gcc 
#CC_FRDM=arm-none-eabi-gcc

#The flags
CFLAGS= -o
#GEN_ALL= -save-temps=cwd		##Saves all the temporary files generated

C_FILES=project_1.c main.c memory.c data.c

I_FILES=project_1.i main.i memory.i data.i

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












#======================================
#=======Additional Targets=============
#======================================

#preprocess: $(C_FILES)
#	$(CC) -E $(C_FILES) -o $(I_FILES)




#=======Preprocessing files (Output generated in the Command line)======
preprocess:
	$(CC) -E *.c
.PHONY : preprocess

%.i : %.c
	$(CC) -E $< -o $@

#=======Assembly output files=============
asm-file: *.c
	gcc -S *.c
.PHONY : asm-file

%.s : %.c
	$(CC) -S $< -o $@

#=======Individual compilation and not link (Working)=====

%.o : %.c
	$(CC) -c $< -o $@

#=======Compile all files (Working)===========

compile-all:
	$(CC) -c *.c 
.PHONY : compile-all

#=======Build all files and link============ Not working

build:
	ld *.o 
.PHONY : build

#=======Upload the files to BBB=============Not tested
upload: %.o
	scp root@10.0.0.215 /home/richard/Desktop/Making/Deep/$@ /ric
.PHONY : upload

#=======Clean the files=====================Working but gives error if all files not present
clean: 
	rm *o *.map *.out *.o *.s *.i
.PHONY : clean

#=======Generates a library into archive========Working. Dont know meaning of cvq
build-lib:
	ar cvq libproject.a memory.c data.c		
.PHONY : build-lib

