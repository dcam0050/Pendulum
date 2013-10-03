
#include "Functions.h"

// Prototype statements for functions found within this file.

// Global variables
double Feedback_Store[readings] = {0};
double Output_Store[readings] = {0};
//double Input_Store[readings] = {0};
char debugger = 0;
unsigned long int len = 0;

void main(void)
{
    unsigned short analoginit;
	//unsigned long int i,j = 0;
	//bool toggle = 0;
	unsigned int j = 0;

	for(j=0;j<readings;j++)
	{
		Feedback_Store[j]=0;
		Output_Store[j] = 0;
		//Input_Store[j] = 0;
	}
	Setup();

	//	Adc2Regs.ADCSOCFRC1.bit.SOC1 =1;//Read ADC2
	//	while(Adc2Regs.ADCCTL1.bit.ADCBSY == 1)
	//	{
	//		asm("NOP");
	//	}
	//	while(Adc2Result.ADCRESULT1 <= threshold)
	//	{
	//		LED1 = 0;
	//	}
	//	GpioG1DataRegs.GPADAT.bit.GPIO26 = 0; //Check voltage, if ok turn on Orange LED
	//	for(j=0;j<30;j++)												//Loop for 5s blinking Green LED until enable of interrupts
	//	{
	//		for(i = 0;i<200000;i++)
	//		{
	//			GpioG1DataRegs.GPADAT.bit.GPIO27 = toggle;
	//			toggle = ~toggle;
	//		}
	//		i = 0;
	//	}
	//	GpioG1DataRegs.GPADAT.bit.GPIO27 = 0;

	    EINT;                               // Enable Global interrupt INTM
	    ERTM;                               // Enable Global real-time interrupt DBGM
		for(;;)
		{
			debugger = 1;
			len++;
		}
}


