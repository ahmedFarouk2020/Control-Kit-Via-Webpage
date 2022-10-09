/***********************************************/
/* Author : FAROUK                             */
/* Version: V01                                */
/* Date   : Sept 30 2020                       */
/***********************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "ESP_interface.h"
#include "ESP_private.h"
#include "ESP_config.h"

#include "DIO.h"
#include "Uart.h"

u8 receivedData[100]={0};
u8 CommandState =0;
u8 Data;

void delay(void)
{
	for(u16 i=0 ; i<=1000 ; i++)
	{
		for(u16 j=0 ; j<=1000 ; j++)
		{
			asm("NOP");
		}
	}
}

u8 ESP_u8ValidateCmd(void)
{
	u8 State =0;

	for(u8 i=0;i<100;i++)
	{
		if( (receivedData[i]=='n' && receivedData[i+1]=='o' ) || (receivedData[i]=='O' && receivedData[i+1]=='K' ) || (receivedData[i]=='A' && receivedData[i+1]=='L' && receivedData[i+2]=='R') )
		{ /* busy b..  |  no change  | OK  | ALREADY CONNECT */
			State = 1;// received correctly
			break;
		}
		else if((receivedData[i]=='b' && receivedData[i+1]=='u' && receivedData[i+2]=='s'))
		{
			delay(); delay(); delay();
			delay(); delay(); delay(); break;
		} else if ( ( receivedData[i]=='i' && receivedData[i+1]=='s' ) || (( receivedData[i]=='o' && receivedData[i+1]=='t' )) ) {
			ESP_voidConnectServer(); /* link is not */
			UART_SendStr(0, (u8 *)"AT+CIPSEND=36\r\n");
			break;
		}
	}
	return State;

}


void ESP_voidReceiveCmd(void)
{
	u8 arrIndx = 0;
	u8 Dummy = 0;

	while(Dummy != 255)
	{
		Dummy = UART_RecvWithTimeout(0);
		receivedData[arrIndx] = Dummy;
		arrIndx++;
	}

}


void ESP_voidInit(void)
{
	UART_SendStr(0, (u8 *)"ATE0\r\n");
	delay(); delay(); delay();

	UART_SendStr(0, (u8 *)"AT+CWMODE=1\r\n");
	delay(); delay(); delay();
}


void ESP_voidConnectToRouter(void)
{
	
	UART_SendStr(0, (u8 *)"AT+CWJAP=\"abc\",\"#*600800*#\"\r\n");
	delay(); delay(); delay();

}

void ESP_voidConnectServer(void)
{	
	u8 status = 0;
	while(status == 0) {
		// delay(); delay(); delay();
		UART_SendStr(0 ,(u8 *)"AT+CIPSTART=\"TCP\",\"192.168.1.5\",80\r\n");
		ESP_voidReceiveCmd();
		status = ESP_u8ValidateCmd();
	}
}

void ESP_voidSendServerReq(void)
{
	u8 status = 0;
	while(status == 0) {
		UART_SendStr(0, (u8 *)"AT+CIPSEND=36\r\n");
		ESP_voidReceiveCmd();
		ESP_u8ValidateCmd();

		UART_SendStr(0, (u8 *)"GET http://localhost:80/get-status\n\n");
		ESP_voidReceiveCmd();
		status = ESP_u8ValidateCmd();
	}
//	delay(); delay(); delay(); delay();

}




void ESP_voidGetData(void)
{
	u8 i=0;
	while(i < 100)
	{
		if( receivedData[i]=='+' && receivedData[i+1]=='I')
		{
			Data = receivedData[i+7];
			break;
		} else if (receivedData[i]=='I' && receivedData[i+1]=='P') {
			Data = receivedData[i+6];
			break;
		} else if (receivedData[i]=='P' && receivedData[i+1]=='D') {
			Data = receivedData[i+5];
			break;
		}
		i++;
	}

}



