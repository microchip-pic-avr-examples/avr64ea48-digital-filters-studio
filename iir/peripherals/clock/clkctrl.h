#ifndef CLKCTRL_H_
#define CLKCTRL_H_

#include <xc.h>
#include <avr/cpufunc.h>

void clkctrl_init(void);
#ifndef F_CPU
#define F_CPU 20000000UL
#endif



#endif /* CLKCTRL_H_ */