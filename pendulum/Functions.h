/*
 * functions.h
 *
 *  Created on: Sep 11, 2013
 *      Author: Daniel
 */

#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

//Include
#include "DSP28x_Project.h"       // Device Headerfile and Examples Include File
#include "Example_posspeed.h"
#include <string.h>
#include <stdbool.h>
#include <math.h>

//Prototype Functions
void Setup(void);
void EPwmConfig(void);
void sensorData(void);
void PeripheralConfig(void);
interrupt void Inner_Loop( void );
interrupt void Outer_Loop(void);
interrupt void Alarm_ISR(void);
interrupt void XINT2(void);

//Pinouts
#define LED1 			GpioG1DataRegs.GPADAT.bit.GPIO25
#define LED2 			GpioG1DataRegs.GPADAT.bit.GPIO26
#define LED3			GpioG1DataRegs.GPADAT.bit.GPIO27

#define Direction	 	GpioG1DataRegs.GPADAT.bit.GPIO24
#define Direction_DIR 	GpioG1CtrlRegs.GPADIR.bit.GPIO24

#define LED_0_DIR 		GpioG1CtrlRegs.GPCDIR.bit.GPIO70
#define LED_0_DAT 		GpioG1DataRegs.GPCDAT.bit.GPIO70
#define LED_1_DIR 		GpioG1CtrlRegs.GPCDIR.bit.GPIO71
#define LED_1_DAT 		GpioG1DataRegs.GPCDAT.bit.GPIO71

short int sign(double);

//Constants
#define  Inner_Loop_Period         30000 //150MHz/5kHz
#define  PWM_Period			       3000	 //150MHz/25kHz*2
#define  Outer_Loop_Period		   15625 //150MHz/(100*12*8)
#define  PWM_upperLimit			   0.75
#define  PI						   3.14159265359
#define  threshold 				   0xF0FFFFFF
#define  readings 				   10

//Outer Loop Constants
#define M 					6
#define m 					0.391
#define L 					0.442
#define g 					9.81
#define c0 					1
#define a0 					0.24
#define b0 					0.883
#define z 					1
#define wn 					4.711 //sqrt(g/L)
#define g1 					0.1222
#define g2 					0.349
#define divider 			30
#define A 					595.2819
#define B 					360.707
#define C 					1182.128
#define D 					253.134
#define pinion_radius 		11e-3
#define Saturation 			4
#define Vsupply				28

// Inner Loop Constants
#define U1 6848
#define U2 -174
#define U3 3326

#define Reference_Factor 1344
#define sat_per			 0.75
#define gain 			 1.2

#define Y0 -3451
#define Y1 2107
#define Y2 0
#define Y3 0


#define filter_gain 9.383327128
#define Kt 0.116

#define Pos_Dir	1
#define Neg_Dir	0


#endif /* FUNCTIONS_H_ */
