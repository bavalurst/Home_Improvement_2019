################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Actuator.cpp \
../Bed.cpp \
../Control.cpp \
../Database.cpp \
../Device.cpp \
../Fridge.cpp \
../Schemerlamp.cpp \
../Sensor.cpp \
../Stoel.cpp \
../Zuil.cpp \
../main.cpp 

OBJS += \
./Actuator.o \
./Bed.o \
./Control.o \
./Database.o \
./Device.o \
./Fridge.o \
./Schemerlamp.o \
./Sensor.o \
./Stoel.o \
./Zuil.o \
./main.o 

CPP_DEPS += \
./Actuator.d \
./Bed.d \
./Control.d \
./Database.d \
./Device.d \
./Fridge.d \
./Schemerlamp.d \
./Sensor.d \
./Stoel.d \
./Zuil.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	arm-linux-gnueabihf-g++ -I/usr/arm-linux-gnueabihf/include/ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


