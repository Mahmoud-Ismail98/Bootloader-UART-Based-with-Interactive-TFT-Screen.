################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/MCAL/GPIO/GPIO_program.c 

OBJS += \
./Src/MCAL/GPIO/GPIO_program.o 

C_DEPS += \
./Src/MCAL/GPIO/GPIO_program.d 


# Each subdirectory must supply rules for building sources it contributes
Src/MCAL/GPIO/%.o Src/MCAL/GPIO/%.su Src/MCAL/GPIO/%.cyclo: ../Src/MCAL/GPIO/%.c Src/MCAL/GPIO/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -c -I../Inc -I"H:/test/ARM_prgect/Bootloader-UART-Based-with-Interactive-TFT-Screen/Bootloader_APP_updater/SERVICES" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Src-2f-MCAL-2f-GPIO

clean-Src-2f-MCAL-2f-GPIO:
	-$(RM) ./Src/MCAL/GPIO/GPIO_program.cyclo ./Src/MCAL/GPIO/GPIO_program.d ./Src/MCAL/GPIO/GPIO_program.o ./Src/MCAL/GPIO/GPIO_program.su

.PHONY: clean-Src-2f-MCAL-2f-GPIO

