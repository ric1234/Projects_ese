#==================Include the make files============================================
include sources.mk

IS:=$(SRCS:.c=.i)
ASM_FILES:=$(IS:.i=.s)
OBJ_FILES:=$(ASM_FILES:.s=.o)


#==================Default compiler==================================================
CC=gcc

#==================The default flags=================================================
CFLAGS=-ansi -std=c99

WALL=-Wall				##How to implement
DEBUG= -g 

LD_FLAGS= -O0 -Map 			#-Arch_specific
SIZE=size


#==================Test condition======================================================
ifeq ($(arch),host)
CC=gcc
SIZE=size
else ifeq ($(arch), bbb)
CC=arm-linux-gnueabihf-gcc
SIZE=arm-linux-gnueabihf-size
else ifeq ($(arch), frdm)
CC=arm-none-eabi-gcc		#include pragma function
SIZE=arm-none-eabi-size
endif

#====================Main code starts here:
all: build size_of_file


#======================================
#=======Additional Targets=============
#======================================
#==============Dependencies============================

dependencies:$(SRCS)
	$(CC) -M $< -o $@

#=======Preprocessing files (Output generated in the Command line)======
#$@: Prereq  $<:Target
#======================================================================
preprocess: $(IS)
	$(CC) -E $< -o $@
.PHONY : preprocess

%.i : %.c
	$(CC) -E $< -o $@

#=======Assembly output files=============
asm-file: $(ASM_FILES)
	$(CC) -S $(ASM_FILES)
.PHONY : asm-file

%.s : %.i 
	$(CC) -S $< -o $@

#=======Individual compilation and not link (Working)=====
%.o : %.s
	$(CC) -c $< -o $@		

#=======Compile all files (Working)===========

compile-all: $(OBJ_FILES)
	$(CC) -c $(OBJ_FILES) 
.PHONY : compile-all

#=======Build all files and link===========


build: $(INCLUDES) $(OBJ_FILES)
	$(CC) $(OBJ_FILES) -o project
.PHONY : build
#=======Size==================================
size_of_file: project
	$(SIZE) project

#=======Upload the files to BBB=============
#NOTE:
#The IP of the board will have to be modified depending on the router 
#===========================================
upload: 
	scp project root@10.0.0.215:/home/project_1	
.PHONY : upload

#=======Clean the files=====================
clean: 
	rm $(IS) $(ASM_FILES) $(OBJ_FILES) project
.PHONY : clean

#=======Generates a library into archive========================================================
build-lib:
	ar -c libproject.a -r memory.c data.c		
.PHONY : build-lib

