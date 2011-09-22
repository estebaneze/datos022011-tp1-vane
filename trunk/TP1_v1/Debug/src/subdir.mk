################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Bucket.cpp \
../src/Buckets.cpp \
../src/Comparable.cpp \
../src/ComuDatos.cpp \
../src/Directory.cpp \
../src/Field.cpp \
../src/HashExtensible.cpp \
../src/Index.cpp \
../src/TP1_v1.cpp \
../src/TableIndex.cpp \
../src/base64.cpp \
../src/bp_node.cpp \
../src/bp_subnode.cpp \
../src/bp_tree.cpp \
../src/capaindice.cpp \
../src/key_node.cpp \
../src/main.cpp \
../src/main2.cpp \
../src/main_commands.cpp \
../src/main_commandsARGS.cpp \
../src/ref.cpp \
../src/refs.cpp 

OBJS += \
./src/Bucket.o \
./src/Buckets.o \
./src/Comparable.o \
./src/ComuDatos.o \
./src/Directory.o \
./src/Field.o \
./src/HashExtensible.o \
./src/Index.o \
./src/TP1_v1.o \
./src/TableIndex.o \
./src/base64.o \
./src/bp_node.o \
./src/bp_subnode.o \
./src/bp_tree.o \
./src/capaindice.o \
./src/key_node.o \
./src/main.o \
./src/main2.o \
./src/main_commands.o \
./src/main_commandsARGS.o \
./src/ref.o \
./src/refs.o 

CPP_DEPS += \
./src/Bucket.d \
./src/Buckets.d \
./src/Comparable.d \
./src/ComuDatos.d \
./src/Directory.d \
./src/Field.d \
./src/HashExtensible.d \
./src/Index.d \
./src/TP1_v1.d \
./src/TableIndex.d \
./src/base64.d \
./src/bp_node.d \
./src/bp_subnode.d \
./src/bp_tree.d \
./src/capaindice.d \
./src/key_node.d \
./src/main.d \
./src/main2.d \
./src/main_commands.d \
./src/main_commandsARGS.d \
./src/ref.d \
./src/refs.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


