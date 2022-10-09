/*********************************************************/
/* author  : Farouk                                      */
/* Version : v01                                         */
/* Date    : Sept 19 2020                                */
/*********************************************************/

#ifndef UART_PRIVATE_H
#define UART_PRIVATE_H

#define UART1_BASE_ADDRESS   (0x40013800)  // APB2
#define UART2_BASE_ADDRESS   (0x40004400)  // APB1
#define UART3_BASE_ADDRESS   (0x40004800)  // APB1


typedef struct{
	
	volatile u32 SR;
	volatile u32 DR;
	volatile u32 BRR;
	volatile u32 CR1;
	volatile u32 CR2;
	volatile u32 CR3;
	volatile u32 GRPR;

}UART_TypeDef;


#define UART1      ( (volatile UART_TypeDef *)0x40013800 )



#endif
