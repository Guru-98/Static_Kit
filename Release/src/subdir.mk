################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/display.c \
../src/lcd.c \
../src/r_cg_adc.c \
../src/r_cg_adc_user.c \
../src/r_cg_cgc.c \
../src/r_cg_cgc_user.c \
../src/r_cg_intc.c \
../src/r_cg_intc_user.c \
../src/r_cg_port.c \
../src/r_cg_port_user.c \
../src/r_cg_timer.c \
../src/r_cg_timer_user.c \
../src/r_main.c \
../src/r_systeminit.c \
../src/test.c 

C_DEPS += \
./src/display.d \
./src/lcd.d \
./src/r_cg_adc.d \
./src/r_cg_adc_user.d \
./src/r_cg_cgc.d \
./src/r_cg_cgc_user.d \
./src/r_cg_intc.d \
./src/r_cg_intc_user.d \
./src/r_cg_port.d \
./src/r_cg_port_user.d \
./src/r_cg_timer.d \
./src/r_cg_timer_user.d \
./src/r_main.d \
./src/r_systeminit.d \
./src/test.d 

OBJS += \
./src/display.o \
./src/lcd.o \
./src/r_cg_adc.o \
./src/r_cg_adc_user.o \
./src/r_cg_cgc.o \
./src/r_cg_cgc_user.o \
./src/r_cg_intc.o \
./src/r_cg_intc_user.o \
./src/r_cg_port.o \
./src/r_cg_port_user.o \
./src/r_cg_timer.o \
./src/r_cg_timer_user.o \
./src/r_main.o \
./src/r_systeminit.o \
./src/test.o 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking Compiler'
	$(file > $@.in,-O0 -fdata-sections -g2 -IC:\\Program Files (x86)\\Renesas\\RL78\\1_8_0\\/inc -IC:/Users/500022/Documents/Intern/RL78/workspace/Static_Kit/generate -I"C:/Users/500022/Documents/Intern/RL78/workspace/Static_Kit/generate" -Wa,-adlhn="$(basename $(notdir $<)).lst" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" "$<" -c -o "$@")
	rl78-elf-gcc @"$@.in"
	@echo 'Finished building: $<'
	@echo ' '


