################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/assimilate_handler.cpp 

OBJS += \
./src/assimilate_handler.o 

CPP_DEPS += \
./src/assimilate_handler.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/local/mysql/include/ -I/Users/nrakover/Desktop/BOINC/BOINC_Source -I/Users/nrakover/Desktop/BOINC/BOINC_Source/api -I/Users/nrakover/Desktop/BOINC/BOINC_Source/lib -I/Users/nrakover/Desktop/BOINC/BOINC_Source/db -I/Users/nrakover/Desktop/BOINC/BOINC_Source/sched -I/Users/nrakover/Desktop/BOINC/BOINC_Source/tools -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


