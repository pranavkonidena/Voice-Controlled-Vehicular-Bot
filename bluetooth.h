#ifndef BLUETOOTHSERVICE_H
#define BLUETOOTHSERVICE_H

class bluetoothService{
public:
    static void uart1Init();
    void sendChar(char c);
    void sendString(char* string);
    char readChar();
    char* readString(char delimiter);
		void initService();
};

#endif
