################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Bed.cpp \
../Control.cpp \
../Controller.cpp \
../Database.cpp \
../Device.cpp \
../Socket.cpp \
../Stoel.cpp \
../main.cpp 

OBJS += \
./Bed.o \
./Control.o \
./Controller.o \
./Database.o \
./Device.o \
./Socket.o \
./Stoel.o \
./main.o 

CPP_DEPS += \
./Bed.d \
./Control.d \
./Controller.d \
./Database.d \
./Device.d \
./Socket.d \
./Stoel.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/lib/jsoncpp/include/json -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


