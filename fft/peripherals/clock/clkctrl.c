#include "../clock/clkctrl.h"

void clkctrl_init(void)
{
	ccp_write_io((void*)&CLKCTRL.MCLKCTRLB, 0x00); //Set Main clock to 20 MHz
}