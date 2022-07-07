#include "usart1.h"

#define RECEIVE_ERROR_MASK 0x46


static void DefaultFramingErrorCallback(void);
static void DefaultOverrunErrorCallback(void);
static void DefaultParityErrorCallback(void);
void (*USART1_framing_err_cb)(void) = &DefaultFramingErrorCallback;
void (*USART1_overrun_err_cb)(void) = &DefaultOverrunErrorCallback;
void (*USART1_parity_err_cb)(void) = &DefaultParityErrorCallback;


void USART1_Initialize(void)
{
	// TX Out
	PORTC.DIRSET = PIN0_bm;
	//set baud rate register
	USART1.BAUD = (uint16_t)USART1_BAUD_RATE(115200);
	
	// TXEN enabled;
	USART1.CTRLB = USART_TXEN_bm;
	
	//  CHSIZE Character size: 8 bit;
	USART1.CTRLC = USART_CHSIZE_8BIT_gc;

}

void USART1_FramingErrorCallbackRegister(void* callbackHandler)
{
	USART1_framing_err_cb=callbackHandler;
}

void USART1_OverrunErrorCallbackRegister(void* callbackHandler)
{
	USART1_overrun_err_cb=callbackHandler;
}

void USART1_ParityErrorCallbackRegister(void* callbackHandler)
{
	USART1_parity_err_cb=callbackHandler;
}

static void DefaultFramingErrorCallback(void)
{
	/* Add your interrupt code here or use USART1.FramingCallbackRegister function to use Custom ISR */
}

static void DefaultOverrunErrorCallback(void)
{
	/* Add your interrupt code here or use USART1.OverrunCallbackRegister function to use Custom ISR */
}

static void DefaultParityErrorCallback(void)
{
	/* Add your interrupt code here or use USART1.ParityCallbackRegister function to use Custom ISR */
}

void USART1_Enable(void)
{
	USART1.CTRLB |= USART_RXEN_bm | USART_TXEN_bm;
}

void USART1_EnableRx(void)
{
	USART1.CTRLB |= USART_RXEN_bm;
}

void USART1_EnableTx(void)
{
	USART1.CTRLB |= USART_TXEN_bm;
}

void USART1_Disable(void)
{
	USART1.CTRLB &= ~(USART_RXEN_bm | USART_TXEN_bm);
}

uint8_t USART1_GetData(void)
{
	return USART1.RXDATAL;
}

bool USART1_IsTxReady(void)
{
	return (USART1.STATUS & USART_DREIF_bm);
}

bool USART1_IsRxReady(void)
{
	return (USART1.STATUS & USART_RXCIF_bm);
}

bool USART1_IsTxBusy(void)
{
	return (!(USART1.STATUS & USART_TXCIF_bm));
}

bool USART1_IsTxDone(void)
{
	return (USART1.STATUS & USART_TXCIF_bm);
}

void USART1_ErrorCheck(void)
{
	uint8_t errorMask = USART1.RXDATAH;
	if(errorMask & RECEIVE_ERROR_MASK)
	{
		if(errorMask & USART_PERR_bm)
		{
			USART1_parity_err_cb();
		}
		if(errorMask & USART_FERR_bm)
		{
			USART1_framing_err_cb();
		}
		if(errorMask & USART_BUFOVF_bm)
		{
			USART1_overrun_err_cb();
		}
	}
	
}

uint8_t USART1_Read(void)
{
	return USART1.RXDATAL;
}

void USART1_Write(const uint8_t data)
{
	USART1.TXDATAL = data;
}