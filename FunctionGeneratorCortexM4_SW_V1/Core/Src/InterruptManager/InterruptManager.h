/*
 * InterruptManager.h
 *
 *  Created on: May 16, 2020
 *      Author: chris
 */

#ifndef SRC_INTERRUPTMANAGER_H_
#define SRC_INTERRUPTMANAGER_H_


uint16_t btn1_last_interrupt_time;
uint16_t btn2_last_interrupt_time;
uint16_t btn3_last_interrupt_time;
uint16_t btn4_last_interrupt_time;
uint16_t encbtn_last_interrupt_time;

#define DEBOUNCE_TIMER 		TIM16
#define MAX_DEBOUNCE_DELAY 	1000

void IM_Init();

void IM_BTN1_EXTI14_Handler();
void IM_BTN2_EXTI15_Handler();
void IM_BTN3_EXTI0_Handler();
void IM_BTN4_EXTI1_Handler();
void IM_ENC_EXTI2_Handler();
void IM_ENC_DIRF_Handler();

void IM_SWEEP_UPDATE_TIM_IRQHandler();

#endif /* SRC_INTERRUPTMANAGER_H_ */
