#include "TM4C123.h"
#include "bluetooth.h"
#include "gpio.h"
#include <string.h>
#include <stdlib.h>

#define GPIO_PORTF_DATA_R     	(*((volatile unsigned long *) 0X400253FC))
#define GPIO_PORTF_DIR_R         	(*((volatile unsigned long *) 0X40025400))
#define GPIO_PORTF_AFSEL_R     	(*((volatile unsigned long *) 0X40025420))
#define GPIO_PORTF_PUR_R         	(*((volatile unsigned long *) 0X40025510))
#define GPIO_PORTF_DEN_R         	(*((volatile unsigned long *) 0X4002551C))
#define GPIO_PORTF_LOCK_R     	(*((volatile unsigned long *) 0X40025520))
#define GPIO_PORTF_CR_R         	(*((volatile unsigned long *) 0X40025524))
#define GPIO_PORTF_AMSEL_R     	(*((volatile unsigned long *) 0X40025528))
#define GPIO_PORTF_PCTL_R     	(*((volatile unsigned long *) 0X4002552C))
#define SYSCTL_RCGC2_R             	(*((volatile unsigned long *) 0X400FE108))

void gpioService::gpioFInit() {
	
	volatile unsigned long delay;
	SYSCTL_RCGC2_R|=0x00000020;
	delay = SYSCTL_RCGC2_R;
	GPIO_PORTF_LOCK_R= 0x4C4F434B;
	GPIO_PORTF_CR_R= 0x1F;
	GPIO_PORTF_AMSEL_R=0x00;
	GPIO_PORTF_PCTL_R=0x00000000;
	GPIO_PORTF_DIR_R=0x0E;
	GPIO_PORTF_AFSEL_R=0x00;
	GPIO_PORTF_PUR_R=0x11;
	GPIO_PORTF_DEN_R=0x1F;

}

void gpioService::gpioDInit() {
		SYSCTL_RCGC2_R |= (1 << 3);
		GPIOD ->AMSEL = 0x00;
		GPIOD ->PCTL = 0x0;
		GPIOD ->DIR = 0xFF;
		GPIOD ->AFSEL = 0x00;
		GPIOD ->DEN = 0xFF;
}

