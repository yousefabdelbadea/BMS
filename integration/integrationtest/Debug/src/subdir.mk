################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/ADC_program.c \
../src/AFIO_program.c \
../src/BLE.c \
../src/BMS_PBcfg.c \
../src/CellBalancing.c \
../src/Charge_Control.c \
../src/DIO_program.c \
../src/Data_Acqusition.c \
../src/Display.c \
../src/LCD.c \
../src/MULTIPLEXER_program.c \
../src/RCC_program.c \
../src/STP.c \
../src/SYSTICK_program.c \
../src/USART_Program.c \
../src/_write.c \
../src/delay.c \
../src/main.c 

OBJS += \
./src/ADC_program.o \
./src/AFIO_program.o \
./src/BLE.o \
./src/BMS_PBcfg.o \
./src/CellBalancing.o \
./src/Charge_Control.o \
./src/DIO_program.o \
./src/Data_Acqusition.o \
./src/Display.o \
./src/LCD.o \
./src/MULTIPLEXER_program.o \
./src/RCC_program.o \
./src/STP.o \
./src/SYSTICK_program.o \
./src/USART_Program.o \
./src/_write.o \
./src/delay.o \
./src/main.o 

C_DEPS += \
./src/ADC_program.d \
./src/AFIO_program.d \
./src/BLE.d \
./src/BMS_PBcfg.d \
./src/CellBalancing.d \
./src/Charge_Control.d \
./src/DIO_program.d \
./src/Data_Acqusition.d \
./src/Display.d \
./src/LCD.d \
./src/MULTIPLEXER_program.d \
./src/RCC_program.d \
./src/STP.d \
./src/SYSTICK_program.d \
./src/USART_Program.d \
./src/_write.d \
./src/delay.d \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM GNU C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -fno-move-loop-invariants -Wall -Wextra  -g3 -DDEBUG -DUSE_FULL_ASSERT -DTRACE -DOS_USE_TRACE_SEMIHOSTING_DEBUG -DSTM32F10X_MD -DUSE_STDPERIPH_DRIVER -DHSE_VALUE=8000000 -I"../include" -I"../system/include" -I"../system/include/cmsis" -I"../system/include/stm32f1-stdperiph" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


