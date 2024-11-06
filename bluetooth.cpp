#include "TM4C123.h"
#include "bluetooth.h"
#include "gpio.h"
#include <string.h>
#include <stdlib.h>

void bluetoothService::uart1Init() {
    SYSCTL->RCGCUART |= (1 << 1);  // Enable UART1
    SYSCTL->RCGCGPIO |= (1 << 1);  // Enable clock for GPIOB
    GPIOB->AFSEL = (1 << 0) | (1 << 1);  // Enable alt function for PB0, PB1
    GPIOB->PCTL = (1 << 0) | (1 << 4);  // Assign UART signals to PB0, PB1
    GPIOB->DEN = (1 << 0) | (1 << 1);   // Enable digital functionality
    
    UART1->CTL &= ~(1 << 0);  // Disable UART1
    UART1->IBRD = 325;  // Set integer part of baud rate
    UART1->FBRD = 34;   // Set fractional part of baud rate
    UART1->LCRH = (0x3 << 5) | (1 << 4);  // 8-bit, no parity, 1-stop bit
    UART1->CC = 0x0;  // Use system clock for UART
    UART1->CTL = (1 << 0) | (1 << 8) | (1 << 9);  // Enable UART1
}

void bluetoothService::sendChar(char c) {
    while (UART1->FR & (1 << 5)) {};  // Wait until TX buffer is empty
    UART1->DR = c;  // Send the character
}

void bluetoothService::sendString(char* string) {
    while (*string) {
        sendChar(*(string++));  // Send each character
    }
}

char bluetoothService::readChar() {
		unsigned long long reloadVal = 50000-1;
    while (UART1->FR & (1 << 4) && reloadVal --) {};  // Wait until RX buffer is not empty
			if(reloadVal == 0) return 'f';
    char cmd =  UART1->DR;  // Read the character
			if(cmd == 'f' || cmd == 'b' || (cmd - '0' >= 0 && cmd - ' 0' <= 9) || cmd == '+' || cmd == '-' || cmd == 'l' || cmd == 'r'){
				return cmd;
			}
			else{
				return 'x';
			}
}

char* bluetoothService::readString(char delimiter) {
    int stringSize = 0;
    char* string = (char*)calloc(10, sizeof(char));
    char c = readChar();

    while (c != delimiter) {
        *(string + stringSize) = c;
        stringSize++;
        if ((stringSize % 10) == 0) {
            string = (char*)realloc(string, (stringSize + 10) * sizeof(char));
        }
        c = readChar();
    }
    return string;
}

void bluetoothService::initService() {
    gpioService gpS = gpioService();
    bluetoothService b1;
    b1.uart1Init();
    gpS.gpioFInit();
}
bool bluetoothService::bluetoothConnected(){
		gpioService gpS = gpioService();
	  gpS.gpioEInit();
		return (GPIOE ->DATA & 0x10) != 0; 
}
