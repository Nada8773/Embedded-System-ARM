
/*UART0*/
#define UARTDR              (*((volatile unsigned long *)0x4000C000))   /*UART Data is the interface to the FIFOs*/
#define UARTFR              (*((volatile unsigned long *)0x4000C018))   /*flag*/
#define UARTIBRD            (*((volatile unsigned long *)0x4000C024))   /*Integer Baud-Rate Divisor*/ 
#define UARTFBRD            (*((volatile unsigned long *)0x4000C028))   /*Integer Baud-Rate Divisor*/  
#define UARTLCRH            (*((volatile unsigned long *)0x4000C02C))   /*UART Line Control*/  
#define UARTCTL             (*((volatile unsigned long *)0x4000C030))   /*UART Control*/
#define UARTFR_TXFF            0x00000020 /*bit 6 UART Transmit FIFO Full*/  
#define UARTFR_RXFE            0x00000010 /*bit 5 UART Receive FIFO Empty*/ 
#define UARTLCRH_WLEN_8        0x00000060 /*8 bits number of data bits transmitted or received*/ 
#define UARTLCRH_FEN           0x00000010 /*bit 4 UART Enable FIFOs*/ 
#define UARTCTL_UARTEN         0x00000001 /*bit 0 UART Enable*/ 

/*GPIO*/
#define PORTA_AFSEL      (*((volatile unsigned long *)0x40004420))
#define PORTA_DEN        (*((volatile unsigned long *)0x4000451C))
#define PORTA_AMSEL      (*((volatile unsigned long *)0x40004528))
#define PORTA_PCTL       (*((volatile unsigned long *)0x4000452C))
#define SYSCTL_RCGC1     (*((volatile unsigned long *)0x400FE104))
#define SYSCTL_RCGC2     (*((volatile unsigned long *)0x400FE108))
#define SYSCTL_RCGC1_UART0      0x00000001  // UART0 Clock Gating Control
#define SYSCTL_RCGC2_GPIOA      0x00000001  // port A Clock Gating Control
/*
UARTLCRH_WLEN 6:5  bits
Value Description
0x0 5 bits (default)
0x1 6 bits
0x2 7 bits
0x3 8 bit


*/

void Init_UART(void);
void UART_sendByte(unsigned char Data);
unsigned char UART_recieveByte(void);
void UART_sendString(char *str);
void UART_recieveString(char *str);





