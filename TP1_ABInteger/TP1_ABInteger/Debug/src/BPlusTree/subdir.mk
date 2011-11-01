################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/BPlusTree/BNode.cpp \
../src/BPlusTree/BPlusTree.cpp \
../src/BPlusTree/Element.cpp \
../src/BPlusTree/EqualElementComparator.cpp \
../src/BPlusTree/KeyElement.cpp \
../src/BPlusTree/LeafNode.cpp \
../src/BPlusTree/MainTree.cpp \
../src/BPlusTree/Node.cpp \
../src/BPlusTree/NodeFactory.cpp 

OBJS += \
./src/BPlusTree/BNode.o \
./src/BPlusTree/BPlusTree.o \
./src/BPlusTree/Element.o \
./src/BPlusTree/EqualElementComparator.o \
./src/BPlusTree/KeyElement.o \
./src/BPlusTree/LeafNode.o \
./src/BPlusTree/MainTree.o \
./src/BPlusTree/Node.o \
./src/BPlusTree/NodeFactory.o 

CPP_DEPS += \
./src/BPlusTree/BNode.d \
./src/BPlusTree/BPlusTree.d \
./src/BPlusTree/Element.d \
./src/BPlusTree/EqualElementComparator.d \
./src/BPlusTree/KeyElement.d \
./src/BPlusTree/LeafNode.d \
./src/BPlusTree/MainTree.d \
./src/BPlusTree/Node.d \
./src/BPlusTree/NodeFactory.d 


# Each subdirectory must supply rules for building sources it contributes
src/BPlusTree/%.o: ../src/BPlusTree/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


