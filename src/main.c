/***** Project Description
 * Control Kit using webpage remotely
 * @Bugs
 * - UART send unkown characters (bit rate issue) => UART is working now (Solved)
 * - UART receive wrong data :)
 */
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "RCC_interface.h"
#include "DIO.h"
#include "Uart.h"
#include "ESP_interface.h"
#include "app.h"


extern u8 Data;

int main(void)
{
	/* RCC init */
	RCC_voidInitSysClock();/* initiate clock as HSE */
	RCC_voidEnableClock(RCC_APB2 , 2);/* enable GPIOA */

	DIO_Init();
	Uart_Init();
	ESP_voidInit();
//	delay(); delay(); delay();
//	delay();delay();

	ESP_voidConnectToRouter();
//	delay();delay();
   	while(1)
   	{

		ESP_voidConnectServer();
		
		ESP_voidSendServerReq();

		ESP_voidGetData();

		switch (Data)
		{
			case '0': App_TurnOffAll(); break;
			case '1': App_TurnOnLed(RED_LED); break;
			case '2': App_TurnOnLed(GREEN_LED); break;
			case '3': App_TurnOnLed(BLUE_LED); break;
		}

   	}
}
