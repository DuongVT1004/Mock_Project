################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../delay_ms/delay.c 

OBJS += \
./delay_ms/delay.o 

C_DEPS += \
./delay_ms/delay.d 


# Each subdirectory must supply rules for building sources it contributes
delay_ms/%.o: ../delay_ms/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@delay_ms/delay.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


