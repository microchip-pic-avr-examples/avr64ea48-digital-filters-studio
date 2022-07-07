/*
 * main.c
 *
 * Created: 7/6/2022 1:38:48 PM
 *  Author: M53740
 */ 

#include <xc.h>
#include "kalman/matrix_unittests.h"
#include "kalman/kalman_example_gravity.h"
#include "peripherals/clock/clkctrl.h"
#include "peripherals/usart/usart1.h"
#include "peripherals/data_streamer/data_streamer.h"
#define  SEND_OVER_USART true
int main(void)
{
	clkctrl_init();
	USART1_Initialize();

	PORTD.DIRSET = PIN6_bm;
	
	matrix_unittests();
	while(1){
		
		if(SEND_OVER_USART)
		{
			// Code that sends the data over USART.
			kalman_gravity_demo_usart();
			}else{
			// Regular code, without USART for easier cycle
			// measurement on PIN.
			kalman_gravity_demo();
		}
		
		kalman_gravity_demo_lambda();
	}
}