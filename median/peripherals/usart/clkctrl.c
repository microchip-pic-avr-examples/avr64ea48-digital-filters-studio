#include "../clock/clkctrl.h"

void clkctrl_init(void)
{
    ccp_write_io((void*)&CLKCTRL.MCLKCTRLB, (CLKCTRL.MCLKCTRLB & ~CLKCTRL_PDIV_gm) | CLKCTRL_PDIV_DIV10_gc); //Set Main clock to 2 MHz
}