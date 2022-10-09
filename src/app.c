/*
 * app.c
 *
 *  Created on: Aug 23, 2022
 *      Author: Farouk
 */

#include "STD_TYPES.h"
#include "DIO.h"
#include "app.h"


void App_TurnOnLed(u8 Led_Id)
{
	DIO_ChannelWrite(Led_Id, 1);
}

void App_TurnOffAll(void)
{
	DIO_ChannelWrite(RED_LED, 0);
	DIO_ChannelWrite(GREEN_LED, 0);
	DIO_ChannelWrite(BLUE_LED, 0);
}
