/*
 * FunctionOutput.h
 *
 *  Created on: 9 May 2020
 *      Author: chris
 */

#ifndef SRC_SIGNALMANAGER_FUNCTIONOUTPUT_H_
#define SRC_SIGNALMANAGER_FUNCTIONOUTPUT_H_


typedef enum
{
	Sine_Out_Mode,
	Square_Out_Mode,
	Saw_Out_Mode,
	RevSaw_Out_Mode,
	Triangle_Out_Mode,
	Impulse_Out_Mode

} eOutput_mode;


void FuncO_ModifyOutput();

eOutput_mode FuncO_GetOutputMode();


#endif /* SRC_SIGNALMANAGER_FUNCTIONOUTPUT_H_ */