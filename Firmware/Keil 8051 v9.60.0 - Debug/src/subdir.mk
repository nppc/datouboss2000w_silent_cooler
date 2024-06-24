################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/InitDevice.c \
../src/Interrupts.c \
../src/main.c 

OBJS += \
./src/InitDevice.OBJ \
./src/Interrupts.OBJ \
./src/main.OBJ 


# Each subdirectory must supply rules for building sources it contributes
src/%.OBJ: ../src/%.c src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Keil 8051 Compiler'
	C51 "@$(patsubst %.OBJ,%.__i,$@)" || $(RC)
	@echo 'Finished building: $<'
	@echo ' '

src/InitDevice.OBJ: C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/8051/v4.2.3/Device/EFM8BB2/inc/SI_EFM8BB2_Register_Enums.h C:/src/Tennp/Git/datouboss2000w_silent_cooler/Firmware/inc/InitDevice.h C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/8051/v4.2.3/Device/EFM8BB2/inc/SI_EFM8BB2_Defs.h C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/8051/v4.2.3/Device/shared/si8051Base/si_toolchain.h C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/8051/v4.2.3/Device/shared/si8051Base/stdint.h C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/8051/v4.2.3/Device/shared/si8051Base/stdbool.h

src/Interrupts.OBJ: C:/src/Tennp/Git/datouboss2000w_silent_cooler/Firmware/src/main.h C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/8051/v4.2.3/Device/EFM8BB2/inc/SI_EFM8BB2_Register_Enums.h C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/8051/v4.2.3/Device/EFM8BB2/inc/SI_EFM8BB2_Defs.h C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/8051/v4.2.3/Device/shared/si8051Base/stdint.h C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/8051/v4.2.3/Device/shared/si8051Base/si_toolchain.h C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/8051/v4.2.3/Device/shared/si8051Base/stdbool.h

src/main.OBJ: C:/src/Tennp/Git/datouboss2000w_silent_cooler/Firmware/src/main.h C:/src/Tennp/Git/datouboss2000w_silent_cooler/Firmware/inc/InitDevice.h C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/8051/v4.2.3/Device/EFM8BB2/inc/SI_EFM8BB2_Register_Enums.h C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/8051/v4.2.3/Device/EFM8BB2/inc/SI_EFM8BB2_Defs.h C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/8051/v4.2.3/Device/shared/si8051Base/stdint.h C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/8051/v4.2.3/Device/shared/si8051Base/si_toolchain.h C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/8051/v4.2.3/Device/shared/si8051Base/stdbool.h


