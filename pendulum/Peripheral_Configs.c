/*
 * Peripheral_Configs.c
 *
 *  Created on: Sep 12, 2013
 *      Author: Daniel
 */
#include "Functions.h"


void Config_Current_ADC(void);
void Config_PS_ADC(void);
void EQEP_Init(void);
extern char debugger;


void PeripheralConfig(void)
{
	debugger = 3;
	Config_Current_ADC();
	EQEP_Init();
	//Config_PS_ADC();
	return;
}

void EQEP_Init(void)
{

    EQep1Regs.QDECCTL.bit.QSRC=00;      // QEP quadrature count mode
    EQep1Regs.QDECCTL.bit.SOEN=0;		// Disable position compare sync

    EQep1Regs.QEPCTL.bit.FREE_SOFT=0;
    EQep1Regs.QEPCTL.bit.PCRM=01;       // PCRM=01 mode - QPOSCNT reset on maximum position
    EQep1Regs.QPOSINIT = 0x0;
    EQep1Regs.QPOSMAX=0xFFFFFFFF;
    EQep1Regs.QEPCTL.bit.QCLM=0;        // Latch reading when cpu reads QPOSCNT
    EQep1Regs.QEPCTL.bit.QPEN=1;        // QEP enable
    return;
}

void EPwmConfig(void)
{
	EALLOW;
	SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 0;       // Stop all the TB clocks
	EDIS;

	// Time-base registers
    EPwm3Regs.TBPRD = PWM_Period;                       // Set timer period
    EPwm3Regs.TBPHS.half.TBPHS = 0x0000;          		// Phase is 0
    EPwm3Regs.TBCTR = 0x0000;                     		// Clear counter

    // Setup TBCLK
    EPwm3Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN; 		// Count up
    EPwm3Regs.TBCTL.bit.PHSEN = TB_DISABLE;       		// Disable phase loading
    EPwm3Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;      		// Clock ratio to SYSCLKOUT
    EPwm3Regs.TBCTL.bit.CLKDIV = TB_DIV1;
    // Setup compare
    EPwm3Regs.CMPA.half.CMPA = 0;

    // Set actions
    EPwm3Regs.AQCTLA.bit.CAU = AQ_CLEAR;             		// Set PWM3A on Zero
    EPwm3Regs.AQCTLA.bit.CAD = AQ_SET;
//----------------------------------------------------------------------------------------------//
    // Time-base registers
    EPwm2Regs.TBPRD = Outer_Loop_Period;                // Set timer period
    EPwm2Regs.TBPHS.all = 0;          					// Phase is 0
    EPwm2Regs.TBCTR = 0x0000;                      		// Clear counter

    // Setup TBCLK
    EPwm2Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN; 		// Count up
    EPwm2Regs.TBCTL.bit.PHSEN = TB_DISABLE;       		// Disable phase loading
    EPwm2Regs.TBCTL.bit.HSPCLKDIV = 6;      			// Clock ratio to SYSCLKOUT
    EPwm2Regs.TBCTL.bit.CLKDIV = 3;
    // Setup compare
    EPwm2Regs.ETSEL.bit.INTSEL = ET_CTR_PRDZERO;       	// Select INT on Zero and PRD event
    EPwm2Regs.ETSEL.bit.INTEN = 1;    					// Enable INT
    EPwm2Regs.ETPS.bit.INTPRD = ET_1ST;            	 	// Generate INT on 1st event
    // Set actions
    EPwm2Regs.AQCTLA.bit.ZRO = AQ_SET;             		// Set PWM3A on Zero
    EPwm2Regs.AQCTLA.bit.PRD = AQ_CLEAR;
//-----------------------------------------------------------------------------------------//
    // Time-base registers
    EPwm1Regs.TBPRD = Inner_Loop_Period;                // Set timer period
    EPwm1Regs.TBPHS.all = 0;          					// Phase is 0
    EPwm1Regs.TBCTR = 0;                      			// Clear counter
    EPwm1Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN; 		// Count up
    EPwm1Regs.TBCTL.bit.PHSEN = TB_DISABLE;       		// Disable phase loading
    EPwm1Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;      		// Clock ratio to SYSCLKOUT
    EPwm1Regs.TBCTL.bit.CLKDIV = TB_DIV1;

    // Set actions
    EPwm1Regs.AQCTLA.bit.ZRO = AQ_SET;           	  	// Set PWM3A on Zero
    EPwm1Regs.AQCTLA.bit.PRD = AQ_CLEAR;

    EPwm1Regs.ETSEL.bit.SOCAEN         = 1;      		// Enable SOC on A group
    EPwm1Regs.ETSEL.bit.SOCASEL        = 0x3;    		// Select SOC from CMPA/CMPC on up count
    EPwm1Regs.ETPS.bit.SOCAPRD         = 1;
}

void Config_Current_ADC( void )
{
    // Configure ADC
    EALLOW;

    Adc1Regs.ADCCTL2.bit.ADCNONOVERLAP = 1;     // Set ADC to non-overlap mode

    Adc1Regs.ADCCTL1.bit.INTPULSEPOS   = 0;     // EOC trips after conversion result is latched
    Adc1Regs.INTSEL1N2.bit.INT1E       = 1;     // Enabled ADCINT1
    Adc1Regs.INTSEL1N2.bit.INT1CONT    = 0;     // Disable ADCINT1 Continuous mode
    Adc1Regs.INTSEL1N2.bit.INT1SEL     = 1;     // setup EOC1 to trigger ADCINT1

    // Select ADC input channels
    Adc1Regs.ADCSOC1CTL.bit.CHSEL      = 0;     // set SOC1 channel select to ADC1A2

    // Selecting triggers for SOCs
    AnalogSysctrlRegs.TRIG5SEL.all     = 5;     // Assigning EPWM1SOCA to TRIGGER 6 of analog subsystem

    Adc1Regs.ADCSOC1CTL.bit.TRIGSEL    = 9;    	// Assign EPWM1SOCA to SOC1 TRIGSEL
    Adc1Regs.ADCSOCFRC1.bit.SOC1 =1;

    // Set S/H window of 7 ADC clock cycles
    Adc1Regs.ADCSOC1CTL.bit.ACQPS      = 6;

    EDIS;
    return;
}

/*void Config_PS_ADC( void )
{
    // Configure ADC
    EALLOW;

    Adc2Regs.ADCCTL2.bit.ADCNONOVERLAP = 1;     // Set ADC to non-overlap mode

    Adc2Regs.ADCSOC1CTL.bit.CHSEL      = 0;     // set SOC1 channel select to ADC2A2
    Adc2Regs.ADCCTL1.bit.INTPULSEPOS   = 1;     // ADCINT1 trips after AdcResults latch
    Adc2Regs.INTSEL1N2.bit.INT1E       = 1;     // Enabled ADCINT1
    Adc2Regs.INTSEL1N2.bit.INT1CONT    = 0;     // Disable ADCINT1 Continuous mode
    Adc2Regs.INTSEL1N2.bit.INT1SEL     = 0;     // setup EOC0 to trigger ADCINT1 to fire
    Adc2Regs.ADCSOC1CTL.bit.CHSEL      = 0;     // set SOC1 channel select to ADC1A2
    Adc2Regs.ADCSOC1CTL.bit.ACQPS      = 6;     // Set S/H window of 7 ADC clock cycles

    EDIS;
    return;
}*/





