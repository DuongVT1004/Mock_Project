################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../data_uart/data_uart.c 

OBJS += \
./data_uart/data_uart.o 

C_DEPS += \
./data_uart/data_uart.d 


# Each subdirectory must supply rules for building sources it contributes
data_uart/%.o: ../data_uart/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@data_uart/data_uart.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


