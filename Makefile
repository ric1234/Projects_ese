#Declaring variables
include sources.mk

IS:=$(SRCS:.c=.i)
ASM_FILES:=$(IS:.i=.s)

OBJ_FILES:=$(SRCS:.s=.o)
OBJECT_FILES:=$(SRCS:.c=.o)

#==================Default compiler
CC=gcc

#==================The flags
CFLAGS= -o 

#GEN_ALL= -save-temps=cwd		##Saves all the temporary files generated

#OPTIONS= -Wall -g 
LD_FLAGS= -O0 #-Arch_specific
#UPLOAD=scp 

#=======================================================
C99= -ansi -std=c99
#==============================For eabi=====================
#assemler=arm-linux-gnueabi-as


#linker
#LD_1=arm-linux-gnueabi-ld

#=======================Test condition===============
ifeq ($(arch),host)
CC=gcc
else ifeq ($(arch), bbb)
CC=arm-linux-gnueabihf-gcc
else ifeq ($(arch), frdm)
CC=arm-none-eabi-gcc
endif


#====================Main code starts here:
default: build


#====================TESTING AREA================================


check: $(INCLUDES) $(OBJS)
	gcc $< -o execu




#======================================
#=======Additional Targets=============
#======================================
#==============Dependencies============================

dependencies:$(SRCS)
	$(CC) -M $< -o $@

#=======Preprocessing files (Output generated in the Command line)======
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
obj-file: $(OBJ_FILES)
	$(CC) -c $(OBJ_FILES)
.PHONY : obj-file
%.o : %.s
	$(CC) -c $< -o $@		##$@: Prereq  $<:Target

#=======Compile all files (Working)===========

compile-all: $(OBJECT_FILES)
	$(CC) -c $(OBJECT_FILES) 
.PHONY : compile-all

#=======Build all files and link============Working

build: $(INCLUDES) $(OBJECT_FILES)
	$(CC) $(OBJECT_FILES) -o project -M 
.PHONY : build

#=======Upload the files to BBB=============
upload: 
	scp project root@10.0.0.215:/home/project_1
.PHONY : upload

#=======Clean the files=====================Working but gives error if all files not present
clean: 
	rm *.map *.out *.o *.s *.i *.exe 
.PHONY : clean

#=======Generates a library into archive========Working. Dont know meaning of cvq
build-lib:
	ar cvq libproject.a memory.c data.c		
.PHONY : build-lib

