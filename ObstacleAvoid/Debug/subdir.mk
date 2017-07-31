################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../HamsterManager.cpp \
../LocalizationManager.cpp \
../Map.cpp \
../PathPlanner.cpp \
../RandomWalk.cpp \
../Robot.cpp \
../RobotMovement.cpp \
../WayPointsManager.cpp \
../main.cpp 

OBJS += \
./HamsterManager.o \
./LocalizationManager.o \
./Map.o \
./PathPlanner.o \
./RandomWalk.o \
./Robot.o \
./RobotMovement.o \
./WayPointsManager.o \
./main.o 

CPP_DEPS += \
./HamsterManager.d \
./LocalizationManager.d \
./Map.d \
./PathPlanner.d \
./RandomWalk.d \
./Robot.d \
./RobotMovement.d \
./WayPointsManager.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


