################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/strategies/BalanceStrategy.cpp \
../src/strategies/BalanceStrategyFactory.cpp \
../src/strategies/ComposedBalanceStrategy.cpp \
../src/strategies/DeleteBalanceStrategy.cpp \
../src/strategies/InsertBalanceStrategy.cpp \
../src/strategies/ModifyBalanceStrategy.cpp \
../src/strategies/OverflowStrategy.cpp \
../src/strategies/UnderflorRootStrategy.cpp \
../src/strategies/UnderflowStrategy.cpp 

OBJS += \
./src/strategies/BalanceStrategy.o \
./src/strategies/BalanceStrategyFactory.o \
./src/strategies/ComposedBalanceStrategy.o \
./src/strategies/DeleteBalanceStrategy.o \
./src/strategies/InsertBalanceStrategy.o \
./src/strategies/ModifyBalanceStrategy.o \
./src/strategies/OverflowStrategy.o \
./src/strategies/UnderflorRootStrategy.o \
./src/strategies/UnderflowStrategy.o 

CPP_DEPS += \
./src/strategies/BalanceStrategy.d \
./src/strategies/BalanceStrategyFactory.d \
./src/strategies/ComposedBalanceStrategy.d \
./src/strategies/DeleteBalanceStrategy.d \
./src/strategies/InsertBalanceStrategy.d \
./src/strategies/ModifyBalanceStrategy.d \
./src/strategies/OverflowStrategy.d \
./src/strategies/UnderflorRootStrategy.d \
./src/strategies/UnderflowStrategy.d 


# Each subdirectory must supply rules for building sources it contributes
src/strategies/%.o: ../src/strategies/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


