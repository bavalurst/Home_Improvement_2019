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
../Sensor.cpp \
../Stoel.cpp \
../main.cpp 

OBJS += \
./Actuator.o \
./Bed.o \
./Control.o \
./Database.o \
./Device.o \
./Sensor.o \
./Stoel.o \
./main.o 

CPP_DEPS += \
./Actuator.d \
./Bed.d \
./Control.d \
./Database.d \
./Device.d \
./Sensor.d \
./Stoel.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/lib/jsoncpp/include/json -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


