################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Sources/accelerometer.c \
../Sources/adc.c \
../Sources/color.c \
../Sources/delay.c \
../Sources/dma.c \
../Sources/ftoa.c \
../Sources/i2c.c \
../Sources/io.c \
../Sources/main.c \
../Sources/message.c \
../Sources/profile.c \
../Sources/pwm_inti.c \
../Sources/spi.c \
../Sources/uart.c 

OBJS += \
./Sources/accelerometer.o \
./Sources/adc.o \
./Sources/color.o \
./Sources/delay.o \
./Sources/dma.o \
./Sources/ftoa.o \
./Sources/i2c.o \
./Sources/io.o \
./Sources/main.o \
./Sources/message.o \
./Sources/profile.o \
./Sources/pwm_inti.o \
./Sources/spi.o \
./Sources/uart.o 

C_DEPS += \
./Sources/accelerometer.d \
./Sources/adc.d \
./Sources/color.d \
./Sources/delay.d \
./Sources/dma.d \
./Sources/ftoa.d \
./Sources/i2c.d \
./Sources/io.d \
./Sources/main.d \
./Sources/message.d \
./Sources/profile.d \
./Sources/pwm_inti.d \
./Sources/spi.d \
./Sources/uart.d 


# Each subdirectory must supply rules for building sources it contributes
Sources/%.o: ../Sources/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I"../Sources" -I"../Includes" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


