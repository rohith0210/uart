/*#include <reg51.h>

void UART_Init() {
    SCON = 0x50;  // 8-bit UART mode, REN enabled
    TMOD = 0x20;  // Timer1 Mode2
    TH1 = 0xFD;   // 9600 baud rate
    TR1 = 1;      // Start Timer1
}

void UART_Tx(char ch) {
    SBUF = ch;          // Load data to transmit
    while (TI == 0);    // Wait for transmission to complete
    TI = 0;             // Clear TI flag
}

void main() {
    int i;              // ? Declare here
    UART_Init();
    
    while (1) {
        UART_Tx('H');
        UART_Tx('i');
        UART_Tx('\n');
        UART_Tx('\r');
        
        for (i = 0; i < 30000; i++);  // crude delay loop
    }
}

*/
#include <reg51.h>

void UART_Init()
{
    TMOD = 0x20;       // Timer1 Mode2 (8-bit auto-reload)
    TH1 = 0xFD;        // Baud rate 9600 for 11.0592MHz crystal
    SCON = 0x50;       // Serial mode 1, 8-bit data, 1 stop bit, REN enabled
    TR1 = 1;           // Start Timer 1
}

void UART_TxChar(char ch)
{
    SBUF = ch;         // Load character into buffer
    while (TI == 0);   // Wait until transmission complete
    TI = 0;            // Clear TI flag
}

char UART_RxChar()
{
    while (RI == 0);   // Wait for reception to complete
    RI = 0;            // Clear RI flag
    return SBUF;       // Read received char from buffer
}

void main()
{
	 
    char received;
    UART_Init();       // Initialize UART

    UART_TxChar('H');  // Send H
    UART_TxChar('i');  // Send i
    while (1)
    {
        received = UART_RxChar();   // Wait and read a char
        UART_TxChar(received);      // Echo it back
			
    }
	
}

//USING TIMER2 
#include <reg52.h>

void UART_Init_T2() {
    SCON = 0x50;      // UART mode 1, REN enabled (8-bit UART)
    
    // Load reload value for 9600 baud rate
    RCAP2H = 0xFF;
    RCAP2L = 0xDC;
    TH2 = 0xFF;
    TL2 = 0xDC;

    T2CON = 0x34;     // Set RCLK=1, TCLK=1, TR2=1 (start timer 2)
}

void UART_Tx(char ch) {
    SBUF = ch;
    while (TI == 0);
    TI = 0;
}

void main() {
    UART_Init_T2();

    while (1) {
        UART_Tx('H');
        UART_Tx('e');
        UART_Tx('l');
        UART_Tx('l');
        UART_Tx('o');
        UART_Tx('\n');
        UART_Tx('\r');
        while (1);  // Just once
    }
}
