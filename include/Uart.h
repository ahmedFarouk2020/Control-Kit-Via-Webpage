/*********************************************************/
/* author  : Farouk                                      */
/* Version : v01                                         */
/* Date    : Sept 19 2020                                */
/*********************************************************/

#ifndef UART_INTERFACE_H
#define UART_INTERFACE_H


#define INVALID_UART_ID_ERROR 250


void Uart_Init(void);

void UART_SendSync(u8 DeviceId, u8 data);

void UART_SendStr(u8 DeviceId, u8* str);

u8 UART_RecvSync(u8 DeviceId);

u8 UART_RecvWithTimeout(u8 DeviceId);








#endif
