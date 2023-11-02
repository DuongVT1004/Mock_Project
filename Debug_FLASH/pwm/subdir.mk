################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../pwm/pwm.c 

OBJS += \
./pwm/pwm.o 

C_DEPS += \
./pwm/pwm.d 


# Each subdirectory must supply rules for building sources it contributes
pwm/%.o: ../pwm/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@pwm/pwm.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


