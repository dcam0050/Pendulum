/*
 * Setup.c
 *
 *  Created on: Sep 12, 2013
 *      Author: Daniel
 */
#include "Functions.h"

#ifdef _FLASH
// These are defined by the linker (see device linker command file)
extern Uint16 RamfuncsLoadStart;
extern Uint16 RamfuncsLoadSize;
extern Uint16 RamfuncsRunStart;
extern char debugger;
#endif

void Setup(void)
{
	unsigned long int delay = 0;	// Step 1. Initialize System Control for Control and Analog Subsystems
	// Enable Peripheral Clocks
	// This example function is found in the F28M35x_SysCtrl.c file.

	debugger = 2;
	InitSysCtrl();
	// If project is linked into flash, copy critical code sections to RAM.


    // Step 2. Initialize GPIO:
	// This example function is found in the F28M35x_Gpio.c file and
	// illustrates how to set the GPIO to it's default state.

#ifdef _FLASH
		// Copy time critical code and Flash setup code to RAM
		// This includes the following functions: InitFlash();
		// The  RamfuncsLoadStart, RamfuncsLoadEnd, and RamfuncsRunStart
		// symbols are created by the linker. Refer to the device .cmd file.
		   memcpy(&RamfuncsRunStart, &RamfuncsLoadStart, (size_t)&RamfuncsLoadSize);

		// Call Flash Initialization to setup flash waitstates
		// This function must reside in RAM
			InitFlash();
#endif

	// Step 3. Clear all interrupts and initialize PIE vector table:
	// Disable CPU interrupts
	    DINT;

	    // Initialize the PIE control registers to their default state.
	    	// The default state is all PIE interrupts disabled and flags
	    	// are cleared.
	    	// This function is found in the F28M35x_PieCtrl.c file.
	    	    InitPieCtrl();

	    	// Disable CPU interrupts and clear all CPU interrupt flags:
	    	    IER = 0x0000;
	    	    IFR = 0x0000;

	    	// Initialize the PIE vector table with pointers to the shell Interrupt
	    	// Service Routines (ISR).
	    	// This will populate the entire table, even if the interrupt
	    	// is not used in this example.  This is useful for debug purposes.
	    	// The shell ISR routines are found in F28M35x_DefaultIsr.c.
	    	// This function is found in F28M35x_PieVect.c.m
	    	    InitPieVectTable();

	    	// Interrupts that are used in this example are re-mapped to
	    	// ISR functions found within this file.
	    	   EALLOW; // This is needed to write to EALLOW protected register
	    	   PieVectTable.ADCINT1 = &Inner_Loop;
	    	   PieVectTable.XINT1 = &Alarm_ISR;
	    	   PieVectTable.XINT2 = &XINT2;
	    	   PieVectTable.EPWM2_INT = &Outer_Loop;
	    	   EDIS;   // This is needed to disable write to EALLOW protected registers

	    	// Step 4. Initialize all the Device Peripherals:
	    	// This function is found in F28M35x_InitPeripherals.c
	    	// InitPeripherals(); // Not required for this example

	    	   // InitGpio();  // Skipped for this example
				InitEQep1Gpio();
				InitEPwm3Gpio();
				InitEPwm2Gpio();
				InitEPwm1Gpio();
				InitAdc1();
				EALLOW;
				Direction_DIR = 1;
				GpioG1CtrlRegs.GPADIR.bit.GPIO5 = 1;	// Set Pin A.5 for Absolute Encoder Direction Control
				GpioG1CtrlRegs.GPADIR.bit.GPIO6 = 1;	// Set Pin A.6 for Absolute Encoder Latch Control
				GpioG1CtrlRegs.GPBDIR.bit.GPIO32  = 1;  // Set as output
				GpioG1CtrlRegs.GPBMUX1.bit.GPIO32 = 3;  // Select EPWM1SOCA as driving source
				GpioG1CtrlRegs.GPADIR.bit.GPIO25 = 1;	// Set pin as out for alarm LED
				GpioG1CtrlRegs.GPADIR.bit.GPIO26 = 1;	// For power on orange LED
				GpioG1CtrlRegs.GPADIR.bit.GPIO27 = 1;	// For startup warning green LED
				LED_0_DIR_REG = 1;
				LED_1_DIR_REG = 1;
				EDIS;


				EALLOW;

			    GpioG1CtrlRegs.GPAMUX1.bit.GPIO7 = 0;        // GPIO
			    GpioG1CtrlRegs.GPADIR.bit.GPIO7 = 0;         // input
			    GpioG1CtrlRegs.GPAQSEL1.bit.GPIO7 = 0;       // XINT1 Synch to SYSCLKOUT only


			    GpioG1CtrlRegs.GPAMUX2.bit.GPIO24 = 0;        // GPIO
			    GpioG1CtrlRegs.GPADIR.bit.GPIO24 = 0;         // input
			    GpioG1CtrlRegs.GPAQSEL2.bit.GPIO24 = 0;       // XINT2 Synch to SYSCLKOUT only


				EDIS;

				EALLOW;

				GpioG1TripRegs.GPTRIP4SEL.bit.GPTRIP4SEL = 7;		//Switch end of line interrupt
				GpioG1TripRegs.GPTRIP5SEL.bit.GPTRIP5SEL = 24;		//Absolute Encoder Alarm

				EDIS;

				Direction = Pos_Dir;
				//LED_0_DAT_REG = 1;// turn off LED

				XIntruptRegs.XINT1CR.bit.ENABLE = 1;
				XIntruptRegs.XINT1CR.bit.POLARITY = 00;

				XIntruptRegs.XINT2CR.bit.ENABLE = 1;
				XIntruptRegs.XINT2CR.bit.POLARITY = 00;


				GpioG1DataRegs.GPADAT.bit.GPIO5 = 0;	//Increasing count in clockwise direction
				GpioG1DataRegs.GPADAT.bit.GPIO6 = 1;	//Disable Latch => Continuous updating of output lines

				GpioG1DataRegs.GPADAT.bit.GPIO25 = 1;
				GpioG1DataRegs.GPADAT.bit.GPIO26 = 1;
				GpioG1DataRegs.GPADAT.bit.GPIO27 = 1;	//Disable all LED's

	    	    for(delay = 0; delay < mSec10; delay++)
				{
				}
	    	    PeripheralConfig(); // Configure ADC and EQEP sub-modules
	    	    EALLOW;
	    		SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 0;
	    		EDIS;
	    		EPwmConfig();
	    		EALLOW;
	    		SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 5;
	    		EDIS;
	            for(delay = 0; delay < mSec20; delay++)
	            {
	            }
	    	    LED_1_DAT_REG = 1;// turn off LED
	            for(delay = 0; delay < mSec20; delay++)
	            {
	            }
	    	    LED_1_DAT_REG = 0;// turn off LED
	            for(delay = 0; delay < mSec20; delay++)
	            {
	            }
	    	    LED_1_DAT_REG = 1;// turn off LED
	    	// Step 5. User specific code, enable interrupts:
	    	// Enable ADCINT1 in PIE
	    	    PieCtrlRegs.PIECTRL.bit.ENPIE = 1;
	    	    PieCtrlRegs.PIEIER1.bit.INTx1 = 1;  // Enable INT 1.1 in the PIE - ADC1 Conversion Ready
	    	    PieCtrlRegs.PIEIER1.bit.INTx4 = 1;	// Enable XINT1
	    	    PieCtrlRegs.PIEIER1.bit.INTx5 = 1;	// Enable XINT2
	    	    PieCtrlRegs.PIEIER3.bit.INTx2 = 1;	// Enable INT 3.2 in the PIE - Timer 2 Interrupt
	    	    IER |= M_INT1;                      // Enable CPU Interrupt 1
	    	    IER |= M_INT3;						// Enable CPU Interrupt 3

	    	    EALLOW;
	    	    SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 1;        // Start all the timers synced
	    	    EDIS;

	    	    return;
}


