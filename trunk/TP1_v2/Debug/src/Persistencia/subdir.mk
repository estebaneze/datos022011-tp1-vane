################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Persistencia/AdmEspacioDisponible.cpp \
../src/Persistencia/Archivo.cpp \
../src/Persistencia/Block.cpp \
../src/Persistencia/Persistor.cpp \
../src/Persistencia/PersistorBTree.cpp \
../src/Persistencia/PersistorBase.cpp 

OBJS += \
./src/Persistencia/AdmEspacioDisponible.o \
./src/Persistencia/Archivo.o \
./src/Persistencia/Block.o \
./src/Persistencia/Persistor.o \
./src/Persistencia/PersistorBTree.o \
./src/Persistencia/PersistorBase.o 

CPP_DEPS += \
./src/Persistencia/AdmEspacioDisponible.d \
./src/Persistencia/Archivo.d \
./src/Persistencia/Block.d \
./src/Persistencia/Persistor.d \
./src/Persistencia/PersistorBTree.d \
./src/Persistencia/PersistorBase.d 


# Each subdirectory must supply rules for building sources it contributes
src/Persistencia/%.o: ../src/Persistencia/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


