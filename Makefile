#Declaring variables
include sources.mk



IS:=$(SRCS:.c=.i)
ASM_FILES:=$(IS:.i=.s)

OBJ_FILES:=$(SRCS:.s=.o)
OBJECT_FILES:=$(SRCS:.c=.o)


#The compilers

#CC_BBB=arm-linux-gnueabihf-gcc 
#CC_FRDM=arm-none-eabi-gcc

#The flags
#CFLAGS= -o
#GEN_ALL= -save-temps=cwd		##Saves all the temporary files generated

#C_FILES=project_1.c main.c memory.c data.c

I_FILES=project_1.i main.i memory.i data.i

#OPTIONS= -Wall -g -O0 #-Arch_specific
#UPLOAD=scp 


#==============================For eabi=====================
#assemler=arm-linux-gnueabi-as


#linker
#LD_1=arm-linux-gnueabi-ld



#====================Main code starts here:
default: build

all: host_name
.PHONY : all

host_name: %$<




Omkar.o: Omkar.c
	$(CC) -c Omkar.c

#=============Board specific===========================
host:
ifeq (%$@, host)
	CCC=gcc
endif
	
.PHONY : host

bbb:
	CCC=arm-linux-gnueabihf-gcc
	

frdm:
	CCC=arm-none-eabi-gcc
#====================================================


check: $(INCLUDES) $(OBJS)
	gcc $< -o execu




#======================================
#=======Additional Targets=============
#======================================

#preprocess: $(C_FILES)
#	$(CC) -E $(C_FILES) -o $(I_FILES)




#=======Preprocessing files (Output generated in the Command line)======
preprocess: $(IS)
	$(CCC) -E $< -o $@
.PHONY : preprocess

%.i : %.c
	$(CCC) -E $< -o $@

#=======Assembly output files=============
asm-file: $(ASM_FILES)
	$(CCC) -S $(ASM_FILES)
.PHONY : asm-file

%.s : %.i
	$(CCC) -S $< -o $@

#=======Individual compilation and not link (Working)=====
obj-file: $(OBJ_FILES)
	$(CCC) -c $(OBJ_FILES)
.PHONY : obj-file
%.o : %.s
	$(CCC) -c $< -o $@		##$@: Prereq  $<:Target

#=======Compile all files (Working)===========

compile-all: $(OBJECT_FILES)
	$(CCC) -c $(OBJECT_FILES) 
.PHONY : compile-all

#=======Build all files and link============Working

build: $(INCLUDES) $(OBJECT_FILES)
	$(CCC) $(OBJECT_FILES) -o project -M 
.PHONY : build

#=======Upload the files to BBB=============Not tested
upload: 
	scp root@10.0.0.215 /home/richard/Desktop/Making/Deep/$@ /ric
.PHONY : upload

#=======Clean the files=====================Working but gives error if all files not present
clean: 
	rm *o *.map *.out *.o *.s *.i *.exe
.PHONY : clean

#=======Generates a library into archive========Working. Dont know meaning of cvq
build-lib:
	ar cvq libproject.a memory.c data.c		
.PHONY : build-lib

