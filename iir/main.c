/*
 * main.c
 *
 * Created: 7/5/2022 2:06:01 PM
 *  Author: Microchip Technology
 */ 

 /*
 * MAIN Generated Driver File
 * 
 * @file main.c
 * 
 * @defgroup main MAIN
 * 
 * @brief This is the generated driver implementation file for the MAIN driver.
 *
 * @version MAIN Driver Version 1.0.0
*/

/*
� [2022] Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms, you may use Microchip 
    software and any derivatives exclusively with Microchip products. 
    You are responsible for complying with 3rd party license terms  
    applicable to your use of 3rd party software (including open source  
    software) that may accompany Microchip software. SOFTWARE IS ?AS IS.? 
    NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS 
    SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT,  
    MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT 
    WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY 
    KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF 
    MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE 
    FORESEEABLE. TO THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP?S 
    TOTAL LIABILITY ON ALL CLAIMS RELATED TO THE SOFTWARE WILL NOT 
    EXCEED AMOUNT OF FEES, IF ANY, YOU PAID DIRECTLY TO MICROCHIP FOR 
    THIS SOFTWARE.
*/
#include <xc.h>
#include <math.h>
#include <stdbool.h>
#include "peripherals/clock/clkctrl.h"

#include "filter/biquad.h"
#include "filter/sine.h"
#include "peripherals/data_streamer/data_streamer.h"
#include "peripherals/usart/usart1.h"

#define ONLY_SEND_USART true
#define FILTER_TYPE LPF

int main(void)
{    
	clkctrl_init();
	USART1_Initialize();
    PORTD.DIRSET = PIN6_bm;
    
    smp_type dbGain = 1.0;
    smp_type freq;
    smp_type srate;
    smp_type bandwidth;
    if(FILTER_TYPE == BPF){
        freq = 3.0;                    // Frequency in Hertz
        srate = 255.0;                 // Samples per second
        bandwidth = 1;               // Bandwidth in Octaves
    }else{
        freq = 8.0;                    // Frequency in Hertz
        srate = 255.0;                 // Samples per second
        bandwidth = 5.0;               // Bandwidth in Octaves
    }
    
    // NOTE: Gain only used when LSH or HSH filter
    // Visit this website for Bandpass filter:
    // http://www.sengpielaudio.com/calculator-bandwidth.htm
   
    biquad *bq = BiQuad_new(FILTER_TYPE, dbGain,    /* gain of filter */
                      freq,                 /* center frequency */
                      srate,                /* sampling rate */
                      bandwidth);           /* Bandwidth in Octaves */
    uint8_t i = 0;
    uint8_t sinevalue;
    float filtered;
    while(1)
    {
        
        if(ONLY_SEND_USART)
        {
            

            sinevalue = sinewave[i++];
			// PD6 used for measuring cycles used in filter
			PORTD.OUTSET = PIN6_bm; // Make PD6 output logic high

            
            filtered = BiQuad(sinevalue, bq);
			PORTD.OUTCLR = PIN6_bm; // Make PD6 output logic low
            // sending original and filtered value
            variableWrite_SendFrame(sinevalue, filtered);
        }else
		{
            sinevalue = sinewave[i++];
			
			// PD6 used for measuring cycles used in filter
			PORTD.OUTSET = PIN6_bm; // Make PD6 output logic high
            filtered = BiQuad(sinevalue, bq);
			PORTD.OUTCLR = PIN6_bm; // Make PD6 output logic low
        
        }
		
    }    
}