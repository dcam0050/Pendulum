/*
 * Inner_Loop.c
 *
 *  Created on: Sep 12, 2013
 *      Author: Daniel
 */
#include "Functions.h"

double PWM_value = 0;
double counter = 0;
bool toggle = 0;

interrupt void Inner_Loop( void )
{
	Uint16 test = 0;

	if(PWM_value < PWM_Period)
	{	PWM_value += 60; }

	else if(PWM_value >= PWM_Period)
	{
		PWM_value = 0;
		toggle = ~toggle;
		LED_0_DAT_REG = toggle;
		Direction = toggle;
	}
	EPwm3Regs.CMPA.half.CMPA = PWM_value;

    Adc1Regs.ADCINTFLGCLR.bit.ADCINT1 = 1;  //Clear ADCINT1 flag reinitialize for next SOC
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1; // Acknowledge interrupt to PIE
}




