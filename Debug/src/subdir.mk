################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables
C_SRCS += \
../src/lcd.c \
../src/r_cg_cgc.c \
../src/r_cg_cgc_user.c \
../src/r_cg_port.c \
../src/r_cg_port_user.c \
../src/r_main.c \
../src/r_systeminit.c 

COMPILER_OBJS += \
src/lcd.obj \
src/r_cg_cgc.obj \
src/r_cg_cgc_user.obj \
src/r_cg_port.obj \
src/r_cg_port_user.obj \
src/r_main.obj \
src/r_systeminit.obj 

C_DEPS += \
src/lcd.d \
src/r_cg_cgc.d \
src/r_cg_cgc_user.d \
src/r_cg_port.d \
src/r_cg_port_user.d \
src/r_main.d \
src/r_systeminit.d 

# Each subdirectory must supply rules for building sources it contributes
src/%.obj: ../src/%.c 
	@echo 'Scanning and building file: $<'
	@echo 'Invoking: Scanner and Compiler'
	@echo src\cDepSubCommand.tmp=
	@sed -e "s/^/ /" "src\cDepSubCommand.tmp"
	ccrl -subcommand="src\cDepSubCommand.tmp" -o "$(@:%.obj=%.d)"  -MT="$(@:%.obj=%.obj)"  -MT="$(@:%.obj=%.d)" -msg_lang=english "$<"
	@echo src\cSubCommand.tmp=
	@sed -e "s/^/ /" "src\cSubCommand.tmp"
	ccrl -subcommand="src\cSubCommand.tmp" -msg_lang=english -o "$(@:%.d=%.obj)" "$<"
	@echo 'Finished Scanning and building: $<'
	@echo.
