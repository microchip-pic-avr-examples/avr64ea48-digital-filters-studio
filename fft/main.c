/*
 * main.c
 *
 * Created: 7/5/2022 9:48:26 AM
 *  Author: M53740
 */ 

#include <xc.h>
#include "filter/kiss_fftr.h"
#include "filter/sine.h"
#include "peripherals/clock/clkctrl.h"
#include "peripherals/usart/usart1.h"
#include "peripherals/data_streamer/data_streamer.h"
#include <avr/cpufunc.h>
#include <math.h>


int main(void)
{
	clkctrl_init();
	USART1_Initialize();
	volatile int nfft = 512;
	volatile int out = (nfft/2)+1;
	
	kiss_fftr_cfg cfg = kiss_fftr_alloc(nfft, 0, NULL, NULL);  //kiss_fft_alloc( nfft ,is_inverse_fft ,0,0 );
	kiss_fft_scalar cpx_in[nfft];
	kiss_fft_cpx cpx_out[out];
	
	
	for(int m =0;m<nfft;m++){               // fill cpx_in with nfft data points from sinewave[]
		cpx_in[m] = sinewave[m];
	};
	
	volatile int16_t watch_real=4;
	volatile int16_t watch_imag = 35;
	volatile uint32_t pwr;
	volatile uint16_t cnt=0;
	
	PORTD.OUTSET = PIN6_bm; // Make PD6 output logic high
	kiss_fftr(cfg, cpx_in , cpx_out);      // The actual FFT operation
	PORTD.OUTCLR = PIN6_bm; // Make PD6 output logic low
	while(1)
	{

		for(int n=0;n<out;n++)
		{
			//putting cpx_out.r  into watchable variables
			cnt = n;
			watch_real = cpx_out[n].r;
			watch_imag = cpx_out[n].i;

			//Calculating the power spectrum
			pwr = sqrt(cpx_out[n].r * cpx_out[n].r + cpx_out[n].i * cpx_out[n].i);


			//Writing four variables to USART, so they can be read by MPLAB DV:
			// 0. Start token
			// 1. watch_real (int16_t)
			// 2. watch_imag (int16_t)
			// 3. cnt (uint16_t))
			// 4. pwr (uint_32_t))
			// .. and the end token
			variableWrite_SendFrame(watch_real, watch_imag, cnt, pwr);
		}
	}
	kiss_fft_cleanup();                         // Tidy up after you.
	
}