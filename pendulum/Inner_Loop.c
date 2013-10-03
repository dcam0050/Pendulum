/*
 * Inner_Loop.c
 *
 *  Created on: Sep 12, 2013
 *      Author: Daniel
 */
#include "Functions.h"

//Data Recording
extern double Feedback_Store[readings];
extern double Output_Store[readings];
extern double Input_Store[readings];
//-----------------------------------

long double Output[3] = {0};		//U(k-1) to U(k-3)
long double Feedback[4] = {0};		//Y(k) to Y(k-3)
long double Output_Current = 0;		//U(k)

long int store_Count = 0;


float PWM = 0;
unsigned int PWM_value = 0;
double filter_offset, current = 0;


extern bool start_outer;
bool start_inner = 1;
bool toggle = 0;

double Torque_Reference = 0.1;
extern char debugger;
extern unsigned long int len;

interrupt void Inner_Loop( void )
{
	int i = 0;
	unsigned long int debug = 0;
	double voltage = 0;
	double Current_Reference = Torque_Reference/Kt ;


	//toggle = ~toggle;
	//LED_0_DAT_REG = toggle;
	debugger = 4;

	if(start_inner == true)// || start_outer == true) //check if inner loop has been executed beforehand, if not clear arrays
	{
		for(i=0;i<3;i++)
		{
			Output[i] = 0;
			Feedback[i] = 0;
		}
		Feedback[3] = 0;
		debug = Adc1Result.ADCRESULT1;
		filter_offset = (debug*3.33/(1<<12));
		start_inner = false;
	}
	else if(start_inner == false)// && start_outer == false)
	{
//----------------------------------Calculate Output Matrix--------------------------//
		Output_Current = 0;
		Output_Current += Reference_Factor*Current_Reference*gain;
		Output_Current += (Output[0]*U1 + Output[1]*U2 + Output[2]*U3);
		Output[2] = Output[1];
		Output[1] = Output[0];
		Output[0] = 0;

//---------------------------------Calculate Feedback Matrix------------------------//

		Feedback[3] = Feedback[2];
		Feedback[2] = Feedback[1];
		Feedback[1] = Feedback[0];
		debug = Adc1Result.ADCRESULT1;
		voltage = (debug*3.33/(1<<12)) ;
		Feedback[0] = voltage - filter_offset;
		if(Feedback[0] < 0.01 && Feedback[0] > -0.01)
		{
			Feedback[0] = 0;
			LED_0_DAT_REG = 1;
		}
		else
		{
			LED_0_DAT_REG = 0;
		}

		Feedback[0] *= filter_gain;
		//Feedback[0] *= Kt;

		Output_Current += (Feedback[0]*Y0 + Feedback[1]*Y1 + Feedback[2]*Y2 + Feedback[3]*Y3 );
		Output_Current /= 10000;
//---------------------------------Update Output Matrix----------------------------------//
		if(Output_Current > Vsupply*sat_per)
		{
			Output_Current = Vsupply*sat_per;
		}
		else if( Output_Current < -Vsupply*sat_per)
		{
			Output_Current = -Vsupply*sat_per;
		}
		Output[0] = Output_Current;

//-----------------------------------PWM Saturation Control-------------------------------//
	PWM = Output_Current/Vsupply;

//--------------------------------------PWM calculation-----------------------------------//
	PWM = (float)(PWM*PWM_Period);
	PWM_value = (Uint16)fabs(PWM);

	if(PWM >= 0)
	{
		Direction = Pos_Dir; //Set Positive Direction
	}
	else if(PWM < 0)
	{
		Direction = Neg_Dir; //Set Negative Direction
	}
	EPwm3Regs.CMPA.half.CMPA = PWM_value;
	LED1 = 0;
	}
	//Input_Store[store_Count] = Torque_Reference;
	//Feedback_Store[store_Count] = Feedback[0];
	//Output_Store[store_Count] = Output_Current;
	store_Count++;
	//if(store_Count >= readings)
		if(store_Count >= PWM_Period)
	{
		//Alarm_ISR();
		store_Count = 0;
		Torque_Reference *= -1;
	}
	len = 0;
    Adc1Regs.ADCINTFLGCLR.bit.ADCINT1 = 1;  //Clear ADCINT1 flag reinitialize for next SOC
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1; // Acknowledge interrupt to PIE
}





