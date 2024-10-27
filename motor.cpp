#include "motor.h"
#include "utils.h"
#include "TM4C123.h"
#include "bluetooth.h"
#include "servomotor.h"
using namespace std;

void motorService::pwmSignal () {
	int duty = 25;
	bluetoothService bl = bluetoothService();
	bl.initService();
  while (true) {
				char command = bl.readChar();
					if(command == 'f') {
						duty = 0;
						pwmGenerator(duty);
						moveForward();
						duty = 25;
					}
					else if(command == 'b') {
						duty = 0;
					pwmGenerator(duty);
						moveBackwards();
						duty = 25;
					}
					else if(command - '0' < 10 && command -'0' >= 0){
						duty = 5*(command - '0');
					}
					else if(command == '+'){
						duty += 5;
					}
					else if(command == '-') {
						duty -= 5;
					}
			  	pwmGenerator(duty);
					
					if(command == 'l') {
							turnLeft();
					}
					else if(command == 'r'){
							turnRight();
					}
		
   }
}


void motorService::moveForward(void)
{
    SYSCTL->RCGC2 |= 0x01;   // Enable clock to PORTA
    GPIOA->DIR |= (1<<3)|(1<<2); // Set PA2 and PA3 as output pins
    GPIOA->DEN |= (1<<3)|(1<<2); // Enable digital functionality for PA2 and PA3
    GPIOA->DATA |=(1<<2);        // Set PA2 HIGH
    GPIOA->DATA &=~(1<<3);       //?Set?PA3?LOW
}

void motorService::moveBackwards(void)
{
    SYSCTL->RCGC2 |= 0x01;   // Enable clock to PORTA
    GPIOA->DIR |= (1<<3)|(1<<2); // Set PA2 and PA3 as output pins
    GPIOA->DEN |= (1<<3)|(1<<2); // Enable digital functionality for PA2 and PA3
    GPIOA->DATA &=~(1<<2);        // Set PA2 HIGH
    GPIOA->DATA |=(1<<3);       //?Set?PA3?LOW
}

void motorService::initService(){
		SYSCTL->RCGC2 |= 0x20;       // Enable clock to GPIOF
    GPIOF->DIR |= 0x02;             // Set PF1 as output
    GPIOF->DEN |= 0x02;             // Enable digital function for PF1
}