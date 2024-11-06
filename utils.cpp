#include "utils.h"
#include "TM4C123.h"
#include "bluetooth.h"
#include "gpio.h"
void systick1Us(){
	SYSCTL->RCGCGPIO |= 0x20;  // Turn on bus clock for GPIOF
  while ((SYSCTL->PRGPIO & 0x20) == 0) {};  // Wait for GPIOF to be ready
  
  GPIOF->DIR |= (1<<3);       // Set PF3 as output (GREEN LED)
  GPIOF->DEN |= (1<<3);       // Enable PF3 as a digital pin
	
  // SysTick configuration
  SysTick->LOAD = 50- 1;  			// One second delay for 50 MHz clock
  SysTick->VAL  = 0;            // Clear the current value register
  SysTick->CTRL = 0x05;         // Enable SysTick, system clock, no interrupt
		
	while (!(SysTick->CTRL & 0x10000));
}
void systick1Ms(int time){
	
for(int i =0 ;i<1000*time;i++) systick1Us();
}

void systickUs(int delay) {
	for(int i = 0; i < delay; i ++) systick1Us();
}

void systickDelaySeconds(int delay) {
	for(int i = 0; i< delay*1000000; i ++) systick1Us();
}

void blinkRed(int ct) {
	while(ct -- ) {
		systick1Ms(300);
		GPIOF->DATA = 0x02;
		systick1Ms(300);
		GPIOF->DATA = 0x0;
	}
}
void blinkGreen(int ct) {
	while(ct -- ) {
		systick1Ms(200);
		GPIOF->DATA = (1<<3);
		systick1Ms(200);
		GPIOF->DATA = 0x0;
	}
}
void blinkBlue(int ct) {
	while(ct -- ) {
		systick1Ms(300);
		GPIOF->DATA = (1<<2);
		systick1Ms(300);
		GPIOF->DATA = 0x0;
	}
}
void glowGreen(){
		GPIOF->DATA = (1<<3);
}
void glowRed(){
	GPIOF->DATA = (1<<1);
}
void moveForward(void)
{
    SYSCTL->RCGC2 |= 0x01;   // Enable clock to PORTA
    GPIOA->DIR |= (1<<3)|(1<<2)|(1 << 4) | (1 << 5); // Set PA2 and PA3 as output pins
    GPIOA->DEN |= (1<<3)|(1<<2)|(1 << 4) | (1 << 5); // Enable digital functionality for PA2 and PA3
    GPIOA->DATA |=((1<<2) | (1 << 4));        // Set PA2 HIGH
    GPIOA->DATA &=~(1<<3);       //Set PA3LOW
		GPIOA ->DATA &=~(1 << 5);
}

void moveBackwards(void)
{
    SYSCTL->RCGC2 |= 0x01;   // Enable clock to PORTA
    GPIOA->DIR |= (1<<3)|(1<<2)|(1<<4)|(1<<5); // Set PA2 and PA3 as output pins
    GPIOA->DEN |= (1<<3)|(1<<2)|(1<<4)|(1<<5); // Enable digital functionality for PA2 and PA3
    GPIOA->DATA &=~(1<<2);        // Set PA2 HIGH
		GPIOA->DATA &=~(1<<4);
    GPIOA->DATA |=((1<<3) | (1 << 5));       //?Set?PA3?LOW
}

void pwmGeneratorLeft(int duty){
				gpioService gp = gpioService();
				//gp.gpioCInit();
				//gp.gpioFInit();
				GPIOF->DATA |= (1<<4);  // Set PF4 high 
         systick1Ms(duty);        // Delay for ON time (duty cycle)
         //Turn off the LED
        GPIOF->DATA &= ~(1<<4); // Set PF4 low 
				systick1Ms((10-duty));
}
void pwmGeneratorRight(int duty){
				gpioService gp = gpioService();
				//gp.gpioDInit();
				GPIOD->DATA |= (1<<6);  // Set PD6 high
        systick1Ms(duty);        // Delay for ON time (duty cycle)
        // Turn off the LED
        GPIOD->DATA &= ~(1<<6); // Set PD6 low 
				systick1Ms(10-duty);
}


