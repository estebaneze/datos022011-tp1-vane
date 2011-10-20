################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/utils/BitFile.cpp \
../src/utils/ConfigFile.cpp \
../src/utils/ConfigurationMananger.cpp \
../src/utils/Fecha.cpp \
../src/utils/utiles.cpp 

OBJS += \
./src/utils/BitFile.o \
./src/utils/ConfigFile.o \
./src/utils/ConfigurationMananger.o \
./src/utils/Fecha.o \
./src/utils/utiles.o 

CPP_DEPS += \
./src/utils/BitFile.d \
./src/utils/ConfigFile.d \
./src/utils/ConfigurationMananger.d \
./src/utils/Fecha.d \
./src/utils/utiles.d 


# Each subdirectory must supply rules for building sources it contributes
src/utils/%.o: ../src/utils/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


