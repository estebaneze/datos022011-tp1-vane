################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Logging/BPlusTreeLog.cpp \
../src/Logging/HashLog.cpp \
../src/Logging/Log.cpp 

OBJS += \
./src/Logging/BPlusTreeLog.o \
./src/Logging/HashLog.o \
./src/Logging/Log.o 

CPP_DEPS += \
./src/Logging/BPlusTreeLog.d \
./src/Logging/HashLog.d \
./src/Logging/Log.d 


# Each subdirectory must supply rules for building sources it contributes
src/Logging/%.o: ../src/Logging/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


