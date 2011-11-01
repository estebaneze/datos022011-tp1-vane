################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Entidades/Administrador.cpp \
../src/Entidades/Candidato.cpp \
../src/Entidades/Cargo.cpp \
../src/Entidades/Conteo.cpp \
../src/Entidades/Distrito.cpp \
../src/Entidades/Eleccion.cpp \
../src/Entidades/Lista.cpp \
../src/Entidades/Votante.cpp 

OBJS += \
./src/Entidades/Administrador.o \
./src/Entidades/Candidato.o \
./src/Entidades/Cargo.o \
./src/Entidades/Conteo.o \
./src/Entidades/Distrito.o \
./src/Entidades/Eleccion.o \
./src/Entidades/Lista.o \
./src/Entidades/Votante.o 

CPP_DEPS += \
./src/Entidades/Administrador.d \
./src/Entidades/Candidato.d \
./src/Entidades/Cargo.d \
./src/Entidades/Conteo.d \
./src/Entidades/Distrito.d \
./src/Entidades/Eleccion.d \
./src/Entidades/Lista.d \
./src/Entidades/Votante.d 


# Each subdirectory must supply rules for building sources it contributes
src/Entidades/%.o: ../src/Entidades/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


