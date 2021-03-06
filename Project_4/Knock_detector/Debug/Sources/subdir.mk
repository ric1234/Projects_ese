################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Sources/accelerometer.c \
../Sources/adc.c \
../Sources/delay.c \
../Sources/dma.c \
../Sources/eeprom.c \
../Sources/ftoa.c \
../Sources/i2c.c \
../Sources/io.c \
../Sources/logging.c \
../Sources/main.c \
../Sources/message.c \
../Sources/profile.c \
../Sources/rtc.c \
../Sources/uart.c 

OBJS += \
./Sources/accelerometer.o \
./Sources/adc.o \
./Sources/delay.o \
./Sources/dma.o \
./Sources/eeprom.o \
./Sources/ftoa.o \
./Sources/i2c.o \
./Sources/io.o \
./Sources/logging.o \
./Sources/main.o \
./Sources/message.o \
./Sources/profile.o \
./Sources/rtc.o \
./Sources/uart.o 

C_DEPS += \
./Sources/accelerometer.d \
./Sources/adc.d \
./Sources/delay.d \
./Sources/dma.d \
./Sources/eeprom.d \
./Sources/ftoa.d \
./Sources/i2c.d \
./Sources/io.d \
./Sources/logging.d \
./Sources/main.d \
./Sources/message.d \
./Sources/profile.d \
./Sources/rtc.d \
./Sources/uart.d 


# Each subdirectory must supply rules for building sources it contributes
Sources/%.o: ../Sources/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I"../Sources" -I"../Includes" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


