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
#include "peripherals/clock/clkctrl.h"
#include "peripherals/usart/usart1.h"
#include "peripherals/data_streamer/data_streamer.h"
#include "filter/MedianFilter.h"
#include "filter/sine.h"
#include <util/delay.h>

#define NUM_ELEMENTS    31

static sMedianFilter_t medianFilter;
static sMedianNode_t medianBuffer[NUM_ELEMENTS];

int main(void)
{
    clkctrl_init();
    USART1_Initialize();
	PORTD.DIRSET = PIN6_bm;
    
    volatile uint16_t original = 0;
    volatile uint16_t filtered = 0;
    uint8_t i = 0;
    medianFilter.numNodes = NUM_ELEMENTS;
    medianFilter.medianBuffer = medianBuffer;
    MEDIANFILTER_Init(&medianFilter);

    while (1)
    {

        original = sinewave[i++];
        _delay_ms(100);
        // Using pin PD6 to measure duration of median filter
		PORTD.OUTSET = PIN6_bm; // Make PD6 output logic high
        filtered = MEDIANFILTER_Insert(&medianFilter, original);
		PORTD.OUTCLR = PIN6_bm; // Make PD6 output logic low

        // sending data over usart
        variableWrite_SendFrame(original, filtered);
    }
}