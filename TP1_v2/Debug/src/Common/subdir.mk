################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Common/Helper.cpp \
../src/Common/Identities.cpp \
../src/Common/IntegerList.cpp 

OBJS += \
./src/Common/Helper.o \
./src/Common/Identities.o \
./src/Common/IntegerList.o 

CPP_DEPS += \
./src/Common/Helper.d \
./src/Common/Identities.d \
./src/Common/IntegerList.d 


# Each subdirectory must supply rules for building sources it contributes
src/Common/%.o: ../src/Common/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


