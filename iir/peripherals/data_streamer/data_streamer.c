/**
 * DATASTREAMER Generated File
 *
 * @file data_streamer.c
 * 
 * @brief This file contains the code for the Data Streamer component.
 *
 * @version Data Streamer Version 1.1.0
 * @note Select and configure a UART over which to send data to the MPLAB Data Visualizer. 
*/

/*
© [2022] Microchip Technology Inc. and its subsidiaries.

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

/* Generate variable frames for sending data to the MPLAB Data Visualizer, 
   e.g. to be display on a graph.
*/
#include <stdint.h>
#include "../usart/usart1.h"
#include "../data_streamer/data_streamer.h"

#define DATA_STREAMER_START_BYTE 3  //trivial Data Streamer Protocol start of frame token
#define DATA_STREAMER_END_BYTE (255 - DATA_STREAMER_START_BYTE)  
/* Data Streamer Protocol end byte is the One's compliment (~) of startByte, 
   e.g. startByte: 0b0000 0011, endByte: 0b1111 1100  */



/**
@ingroup datastreamer
@brief For multi-byte variable types, the bytes are sent from from least significant to most significant.
@param uint8_t* byte_ptr: pointer to multi-byte variable
@param uint8_t num_bytes: number of bytes
*/
static void variableWrite_SendValue(uint8_t* byte_ptr, uint8_t num_bytes)
 {
      for(uint8_t i = 0; i < num_bytes; i++)
      {
         while(!(USART1_IsTxReady()));
         USART1_Write(byte_ptr[i]);
      }
}

void variableWrite_SendFrame(uint8_t original, float filtered)
{
   while(!(USART1_IsTxReady()));
   USART1_Write(DATA_STREAMER_START_BYTE);
     
   while(!(USART1_IsTxReady()));
   USART1_Write(original);                                 // uint8_t

   variableWrite_SendValue((uint8_t *) &filtered, 4);         // float


   while(!(USART1_IsTxReady()));
   USART1_Write(DATA_STREAMER_END_BYTE);  

   while(!USART1_IsTxDone());
}
