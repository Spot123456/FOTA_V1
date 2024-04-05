################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/Bootloader_prog.c \
../Src/CRC.c \
../Src/DMA.c \
../Src/Delay.c \
../Src/EXTI.c \
../Src/FMI_prg.c \
../Src/GPIO.c \
../Src/HEX_Parser.c \
../Src/NVIC_program.c \
../Src/RCC.c \
../Src/STK_program.c \
../Src/USART.c \
../Src/main.c \
../Src/syscalls.c \
../Src/sysmem.c 

OBJS += \
./Src/Bootloader_prog.o \
./Src/CRC.o \
./Src/DMA.o \
./Src/Delay.o \
./Src/EXTI.o \
./Src/FMI_prg.o \
./Src/GPIO.o \
./Src/HEX_Parser.o \
./Src/NVIC_program.o \
./Src/RCC.o \
./Src/STK_program.o \
./Src/USART.o \
./Src/main.o \
./Src/syscalls.o \
./Src/sysmem.o 

C_DEPS += \
./Src/Bootloader_prog.d \
./Src/CRC.d \
./Src/DMA.d \
./Src/Delay.d \
./Src/EXTI.d \
./Src/FMI_prg.d \
./Src/GPIO.d \
./Src/HEX_Parser.d \
./Src/NVIC_program.d \
./Src/RCC.d \
./Src/STK_program.d \
./Src/USART.d \
./Src/main.d \
./Src/syscalls.d \
./Src/sysmem.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o Src/%.su Src/%.cyclo: ../Src/%.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F407G_DISC1 -DSTM32F4 -DSTM32F407VGTx -c -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src

clean-Src:
	-$(RM) ./Src/Bootloader_prog.cyclo ./Src/Bootloader_prog.d ./Src/Bootloader_prog.o ./Src/Bootloader_prog.su ./Src/CRC.cyclo ./Src/CRC.d ./Src/CRC.o ./Src/CRC.su ./Src/DMA.cyclo ./Src/DMA.d ./Src/DMA.o ./Src/DMA.su ./Src/Delay.cyclo ./Src/Delay.d ./Src/Delay.o ./Src/Delay.su ./Src/EXTI.cyclo ./Src/EXTI.d ./Src/EXTI.o ./Src/EXTI.su ./Src/FMI_prg.cyclo ./Src/FMI_prg.d ./Src/FMI_prg.o ./Src/FMI_prg.su ./Src/GPIO.cyclo ./Src/GPIO.d ./Src/GPIO.o ./Src/GPIO.su ./Src/HEX_Parser.cyclo ./Src/HEX_Parser.d ./Src/HEX_Parser.o ./Src/HEX_Parser.su ./Src/NVIC_program.cyclo ./Src/NVIC_program.d ./Src/NVIC_program.o ./Src/NVIC_program.su ./Src/RCC.cyclo ./Src/RCC.d ./Src/RCC.o ./Src/RCC.su ./Src/STK_program.cyclo ./Src/STK_program.d ./Src/STK_program.o ./Src/STK_program.su ./Src/USART.cyclo ./Src/USART.d ./Src/USART.o ./Src/USART.su ./Src/main.cyclo ./Src/main.d ./Src/main.o ./Src/main.su ./Src/syscalls.cyclo ./Src/syscalls.d ./Src/syscalls.o ./Src/syscalls.su ./Src/sysmem.cyclo ./Src/sysmem.d ./Src/sysmem.o ./Src/sysmem.su

.PHONY: clean-Src

