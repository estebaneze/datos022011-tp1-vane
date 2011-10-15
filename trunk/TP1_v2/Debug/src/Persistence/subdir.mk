################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Persistence/Archivo.cpp \
../src/Persistence/Block.cpp \
../src/Persistence/FreeSpaceManager.cpp \
../src/Persistence/Persistor.cpp \
../src/Persistence/PersistorBTree.cpp \
../src/Persistence/PersistorBase.cpp 

OBJS += \
./src/Persistence/Archivo.o \
./src/Persistence/Block.o \
./src/Persistence/FreeSpaceManager.o \
./src/Persistence/Persistor.o \
./src/Persistence/PersistorBTree.o \
./src/Persistence/PersistorBase.o 

CPP_DEPS += \
./src/Persistence/Archivo.d \
./src/Persistence/Block.d \
./src/Persistence/FreeSpaceManager.d \
./src/Persistence/Persistor.d \
./src/Persistence/PersistorBTree.d \
./src/Persistence/PersistorBase.d 


# Each subdirectory must supply rules for building sources it contributes
src/Persistence/%.o: ../src/Persistence/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


