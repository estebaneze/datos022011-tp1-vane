################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Pruebas/Pruebas_Listas.cpp 

OBJS += \
./src/Pruebas/Pruebas_Listas.o 

CPP_DEPS += \
./src/Pruebas/Pruebas_Listas.d 


# Each subdirectory must supply rules for building sources it contributes
src/Pruebas/%.o: ../src/Pruebas/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


