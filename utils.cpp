#include "utils.h"
#include "TM4C123.h"
#include "gpio.h"
void systick1Us(){
	 SYSCTL->RCGCGPIO |= 0x20;  // Turn on bus clock for GPIOF
  while ((SYSCTL->PRGPIO & 0x20) == 0) {};  // Wait for GPIOF to be ready
  
  GPIOF->DIR |= 0x08;       // Set PF3 as output (GREEN LED)
  GPIOF->DEN |= 0x08;       // Enable PF3 as a digital pin
	
  // SysTick configuration
  SysTick->LOAD = 50- 1;  			// One second delay for 50 MHz clock
  SysTick->VAL  = 0;            // Clear the current value register
  SysTick->CTRL = 0x05;         // Enable SysTick, system clock, no interrupt
		
	while (!(SysTick->CTRL & 0x10000));
}
void systick1Ms(){
for(int i =0 ;i<1000;i++) systick1Us();
}

void systickDelaySeconds(int delay) {
	for(int i = 0; i< delay*1000; i ++) {
		systick1Ms();
	}
}

void blinkRed(int ct) {
	while(ct -- ) {
		systickDelaySeconds(1);
		GPIOF->DATA = 0x02;
		systickDelaySeconds(1);
		GPIOF->DATA = 0x0;
	}
}

void moveForward(void)
{
    SYSCTL->RCGC2 |= 0x01;   // Enable clock to PORTA
    GPIOA->DIR |= (1<<3)|(1<<2); // Set PA2 and PA3 as output pins
    GPIOA->DEN |= (1<<3)|(1<<2); // Enable digital functionality for PA2 and PA3
    GPIOA->DATA |=(1<<2);        // Set PA2 HIGH
    GPIOA->DATA &=~(1<<3);       //Set PA3LOW
}

void moveBackwards(void)
{
    SYSCTL->RCGC2 |= 0x01;   // Enable clock to PORTA
    GPIOA->DIR |= (1<<3)|(1<<2); // Set PA2 and PA3 as output pins
    GPIOA->DEN |= (1<<3)|(1<<2); // Enable digital functionality for PA2 and PA3
    GPIOA->DATA &=~(1<<2);        // Set PA2 HIGH
    GPIOA->DATA |=(1<<3);       //?Set?PA3?LOW
}
void pwmGenerator(int duty){
				GPIOF->DATA |= 0x02;  // Set PF1 high (turn ON PF1)
        for(int i = 0;i<duty;i++) systick1Ms();        // Delay for ON time (duty cycle)
        // Turn off the LED
        GPIOF->DATA &= ~0x02; // Set PF1 low (turn OFF PF1)
				for(int i = 0; i < 50-duty; i ++) systick1Ms();
}