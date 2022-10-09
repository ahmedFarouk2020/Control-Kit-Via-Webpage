/***********************************************/
/* Author : FAROUK                             */
/* Version: V01                                */
/* Date   : Sept 30 2020                       */
/***********************************************/

#ifndef ESP_INTERFACE_H
#define ESP_INTERFACE_H


/* Close echo & Set CWMODE as STATION */
void ESP_voidInit(void);

/* Check if Command was received correctly returns the index of OK */
u8 ESP_u8ReceiveCmd(void);

/* connect to router */
void ESP_voidConnectToRouter(void);

/* connect to server */
void ESP_voidConnectServer(void);

/* get data from server to make an action */
void ESP_voidSendServerReq(void);

void ESP_voidGetData(void);

void delay(void);

u8 ESP_u8ValidateCmd(void);

void ESP_voidReceiveCmd(void);

#endif
