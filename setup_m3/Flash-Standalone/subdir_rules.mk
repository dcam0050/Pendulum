################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
set_pinout_f28m35x.obj: C:/ti/controlSUITE/device_support/f28m35x/v201/MWare/board_drivers/set_pinout_f28m35x.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv5/tools/compiler/arm_5.0.4/bin/armcl" -mv7M3 --code_state=16 --abi=eabi -me -g --include_path="C:/ti/ccsv5/tools/compiler/arm_5.0.4/include" --include_path="C:/ti/controlSUITE/device_support/f28m35x/v201/MWare" --gcc --define="_FLASH" --define="_STANDALONE" --diag_warning=225 --gen_func_subsections=on --ual --preproc_with_compile --preproc_dependency="set_pinout_f28m35x.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

setup_m3.obj: C:/ti/controlSUITE/device_support/f28m35x/v201/F28M35x_examples_Control/setup_m3/m3/setup_m3.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv5/tools/compiler/arm_5.0.4/bin/armcl" -mv7M3 --code_state=16 --abi=eabi -me -g --include_path="C:/ti/ccsv5/tools/compiler/arm_5.0.4/include" --include_path="C:/ti/controlSUITE/device_support/f28m35x/v201/MWare" --gcc --define="_FLASH" --define="_STANDALONE" --diag_warning=225 --gen_func_subsections=on --ual --preproc_with_compile --preproc_dependency="setup_m3.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

startup_ccs.obj: C:/ti/controlSUITE/device_support/f28m35x/v201/F28M35x_examples_Control/setup_m3/m3/startup_ccs.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv5/tools/compiler/arm_5.0.4/bin/armcl" -mv7M3 --code_state=16 --abi=eabi -me -g --include_path="C:/ti/ccsv5/tools/compiler/arm_5.0.4/include" --include_path="C:/ti/controlSUITE/device_support/f28m35x/v201/MWare" --gcc --define="_FLASH" --define="_STANDALONE" --diag_warning=225 --gen_func_subsections=on --ual --preproc_with_compile --preproc_dependency="startup_ccs.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


