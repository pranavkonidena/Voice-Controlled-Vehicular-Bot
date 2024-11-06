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

void gpioService::gpioAInit() {
		SYSCTL_RCGC2_R |= (1 << 0);
		GPIOA ->AMSEL = 0x00;
		GPIOA ->PCTL = 0x0;
		GPIOA ->DIR = 0xFF;
		GPIOA ->AFSEL = 0x00;
		GPIOA ->DEN = 0xFF;
}

void gpioService::gpioBInit() {
		SYSCTL_RCGC2_R |= (1 << 1);
		GPIOB ->AMSEL = 0x00;
		GPIOB ->PCTL = 0x0;
		GPIOB ->DIR = 0xFF;
		GPIOB ->AFSEL = 0x00;
		GPIOB ->DEN = 0xFF;
}

void gpioService::gpioCInit() {
		SYSCTL_RCGC2_R |= (1 << 2);
		GPIOC ->AMSEL = 0x00;
		GPIOC ->PCTL = 0x00;
		GPIOC ->DIR = (1<<7);
		GPIOC ->AFSEL = 0x00;
		GPIOC ->DEN = (1<<7);
}

void gpioService::gpioDInit() {
		SYSCTL_RCGC2_R |= (1 << 3);
		GPIOD ->AMSEL = 0x00;
		GPIOD ->PCTL = 0x0;
		GPIOD ->DIR = (1<<6);
		GPIOD ->DIR |= (1<<7);
		GPIOD ->AFSEL = 0x00;
		GPIOD ->DEN = (1<<6);
		GPIOD ->DEN |= (1<<7);
}

void gpioService::gpioFInit() {
	
	volatile unsigned long delay;
	SYSCTL_RCGC2_R |= (1 << 5);
	delay = SYSCTL_RCGC2_R;
	GPIO_PORTF_AMSEL_R=0x00;
	GPIO_PORTF_PCTL_R=0x00000000;
	GPIO_PORTF_DIR_R=0x1E;
	GPIO_PORTF_AFSEL_R=0x00;
	GPIO_PORTF_PUR_R=0x11;
	GPIO_PORTF_DEN_R=0x1F;

}
void gpioService::gpioEInit() {
	// setting PE4 as input 
	// to find the connection state of bluetooth 
		SYSCTL ->RCGC2  |= (1 << 4);
		GPIOE ->AMSEL = 0x00;
		GPIOE ->PCTL = 0x0;
		GPIOE ->DIR = ~(1<<4);
		GPIOE ->PUR = 0x11;
		GPIOE ->CR =
		GPIOE ->AFSEL = 0x00;
		GPIOE ->DEN = (1<<4);
}