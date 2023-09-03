################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../main.c \
../oadc.c \
../odcm.c \
../ogpio.c \
../olcd.c \
../olm35.c \
../opwm.c 

OBJS += \
./main.o \
./oadc.o \
./odcm.o \
./ogpio.o \
./olcd.o \
./olm35.o \
./opwm.o 

C_DEPS += \
./main.d \
./oadc.d \
./odcm.d \
./ogpio.d \
./olcd.d \
./olm35.d \
./opwm.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=1000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


