################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Indexes/Index.cpp \
../src/Indexes/ListaIndex.cpp 

OBJS += \
./src/Indexes/Index.o \
./src/Indexes/ListaIndex.o 

CPP_DEPS += \
./src/Indexes/Index.d \
./src/Indexes/ListaIndex.d 


# Each subdirectory must supply rules for building sources it contributes
src/Indexes/%.o: ../src/Indexes/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

