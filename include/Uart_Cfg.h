/*********************************************************/
/* author  : Farouk                                      */
/* Version : v01                                         */
/* Date    : Sept 19 2020                                */
/*********************************************************/

#ifndef UART_CONFIG_H
#define UART_CONFIG_H


#define CLK 8000000U // CPU CLK

#define NUM_OF_SERIAL_PORTS ((u8)3)

#define NUM_OF_CHANNELS    ((u8)1)
#define MAX_NUM_OF_DEVICES ((u8)1)

typedef struct{
    u8 TXE; // 1-> needed  0-> not needed
    u8 TC;  // 1-> needed  0-> not needed
    u8 RXNE;// 1-> needed  0-> not needed
}Uart_InterruptType;

typedef struct{
	u8 serialID; /* UART1=0, UART2=1, UART3=2 */
	u8 dataSize; /* _8BITS=0, _9BITS=1 */
	//u8 parityType; /* None, ODD, EVEN */
	//u8 stopBits;  /* 1STOP, 2STOP */
	u8 uartMode; /* RX_ONLY=1, TX_ONLY=2, TX_RX=3 */
	Uart_InterruptType interrupts; 
	u32 buadrate; /* 9600, 4800, 115200 ,.. do it by the equation */
}Uart_Config;


extern Uart_Config ConfigList[NUM_OF_CHANNELS];



#endif
