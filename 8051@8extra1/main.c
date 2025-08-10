#include <reg51.h>

// LED on P1.0
sbit LED = P1^0;

// Initialize UART @9600 baud using Timer1 Mode2
void UART_Init() {
    TMOD = 0x20;   // Timer1, Mode 2 (8-bit auto-reload)
    TH1 = 0xFD;     // Reload value for 9600 baud @11.0592 MHz
    SCON = 0x50;    // Serial mode 1, REN=1
    TR1 = 1;        // Start Timer1
}

// Transmit one character, wait for TI
void UART_Tx(char c) {
    SBUF = c;
    while (!TI);
    TI = 0;
}

// Receive one character, wait for RI
char UART_Rx() {
    while (!RI);
    RI = 0;
    return SBUF;
}

// Send a null-terminated string
//void UART_TxString(char *s) {
  //  while (*s) {
    //    UART_Tx(*s++);
    //}
//}
void UART_TxString(char s[]) {
    int i = 0;
    while (s[i] != '\0') {
        UART_Tx(s[i]);
        i++;
    }
}

void main() {
    char cmd;
    
    LED = 0;              // Ensure LED off at start
    UART_Init();          // Set up serial

    UART_TxString("\r\nUART-LED Toggle Ready!\r\n");
    UART_TxString("Send '1' to turn ON, '0' to turn OFF\r\n> ");

    while (1) {
        cmd = UART_Rx();        // Wait for user key
        
        if (cmd == '1') {
            LED = 1;            // Turn LED on
            UART_TxString("\r\nLED ON\r\n> ");
        }
        else if (cmd == '0') {
            LED = 0;            // Turn LED off
            UART_TxString("\r\nLED OFF\r\n> ");
        }
        else {
            UART_TxString("\r\nInvalid. Send '1' or '0'\r\n> ");
        }
    }
}


/*
#include<reg51.h>
sbit LED = P1^0;

void UART_Init(){
  TMOD = 0x20;
  TH1 = 0xFD;
	SCON = 0x50;
	TR1 =1;
}

void UART_Tx(char c){
 SBUF = c;
	while(TI == 0);
	TI = 0;
}
char UART_Rx(){
 
	while(RI == 0);
	RI = 0;
	return SBUF;
}

void UART_TxString(char s[]) {
    int i = 0;
    while (s[i] != '\0') {
        UART_Tx(s[i]);
        i++;
    }
}
void main(){
  char cmd;
  UART_Init();
	UART_TxString("\r\nyou can give input either 0 or 1\r\n> ");
	
	while(1){
	 if(cmd == 1){
	   LED = 1;
		 UART_TxString("LED was turned on\n");
	 }
	 else if (cmd ==0){
	  LED =0;
		 UART_TxString("\r\nLED Off\r\n> ");
	 }
	 else {
	 UART_TxString("\r\invalid\r\n> ");
	 
	 }
		 
	   
	 }

}
*/