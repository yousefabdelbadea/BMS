################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/ADC_program.c \
../src/AFIO_program.c \
../src/BLE.c \
../src/Battery_Backup.c \
../src/CellBalancing.c \
../src/Charge_Control.c \
../src/DIO_program.c \
../src/Data_Acqusition.c \
../src/Display.c \
../src/LCD.c \
../src/MULTIPLEXER_program.c \
../src/NVIC.c \
../src/RCC_program.c \
../src/RCFilter.c \
../src/STP.c \
../src/SYSTICK_program.c \
../src/TIMER_program.c \
../src/ThermalManagment.c \
../src/USART_Program.c \
../src/delay.c \
../src/main.c 

OBJS += \
./src/ADC_program.o \
./src/AFIO_program.o \
./src/BLE.o \
./src/Battery_Backup.o \
./src/CellBalancing.o \
./src/Charge_Control.o \
./src/DIO_program.o \
./src/Data_Acqusition.o \
./src/Display.o \
./src/LCD.o \
./src/MULTIPLEXER_program.o \
./src/NVIC.o \
./src/RCC_program.o \
./src/RCFilter.o \
./src/STP.o \
./src/SYSTICK_program.o \
./src/TIMER_program.o \
./src/ThermalManagment.o \
./src/USART_Program.o \
./src/delay.o \
./src/main.o 

C_DEPS += \
./src/ADC_program.d \
./src/AFIO_program.d \
./src/BLE.d \
./src/Battery_Backup.d \
./src/CellBalancing.d \
./src/Charge_Control.d \
./src/DIO_program.d \
./src/Data_Acqusition.d \
./src/Display.d \
./src/LCD.d \
./src/MULTIPLEXER_program.d \
./src/NVIC.d \
./src/RCC_program.d \
./src/RCFilter.d \
./src/STP.d \
./src/SYSTICK_program.d \
./src/TIMER_program.d \
./src/ThermalManagment.d \
./src/USART_Program.d \
./src/delay.d \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM GNU C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -fno-move-loop-invariants -Wall -Wextra  -g3 -DDEBUG -DUSE_FULL_ASSERT -DTRACE -DOS_USE_TRACE_SEMIHOSTING_DEBUG -DSTM32F10X_MD -DUSE_STDPERIPH_DRIVER -DHSE_VALUE=8000000 -I"../include" -I"../system/include" -I"../system/include/cmsis" -I"../system/include/stm32f1-stdperiph" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


