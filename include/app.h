/*
 * app.h
 *
 *  Created on: Aug 23, 2022
 *      Author: Farouk
 */

#ifndef APP_H_
#define APP_H_


#define RED_LED    0
#define GREEN_LED  3
#define BLUE_LED   4

void App_TurnOnLed(u8 Led_Id);
void App_TurnOffAll(void);

#endif /* APP_H_ */
