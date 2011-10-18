################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/exceptions/ElementAlreadyExists.cpp \
../src/exceptions/ElementNotFoundException.cpp \
../src/exceptions/KeyNotFoundException.cpp \
../src/exceptions/OperationNotFoundException.cpp \
../src/exceptions/OverflowException.cpp \
../src/exceptions/ProgramException.cpp 

OBJS += \
./src/exceptions/ElementAlreadyExists.o \
./src/exceptions/ElementNotFoundException.o \
./src/exceptions/KeyNotFoundException.o \
./src/exceptions/OperationNotFoundException.o \
./src/exceptions/OverflowException.o \
./src/exceptions/ProgramException.o 

CPP_DEPS += \
./src/exceptions/ElementAlreadyExists.d \
./src/exceptions/ElementNotFoundException.d \
./src/exceptions/KeyNotFoundException.d \
./src/exceptions/OperationNotFoundException.d \
./src/exceptions/OverflowException.d \
./src/exceptions/ProgramException.d 


# Each subdirectory must supply rules for building sources it contributes
src/exceptions/%.o: ../src/exceptions/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


