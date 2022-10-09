/*
 * DIO_Cfg.c
 *
 *  Created on: Mar 23, 2022
 *      Author: moham
 */

#include "../include/STD_TYPES.h"
#include "../include/DIO_Cfg.h"

const DIO_ChannelConfigType DIO_ConfigParam[DIO_NUM_OF_CHANNELS] =
{

	{0,0,2,1,0},   /* channel 0 - red */
	{0,9,6,1,0},   /* channel 1 - TX */
	{0,10,0,1,0},    /* channel 2 - RX */
	{0,1,2,1,0},   /* channel 3 - green */
	{0,2,2,1,0}   /* channel 4 - blue */
};


const DIO_ChannelGroupConfigType DIO_ChannelGroupList[DIO_NUM_OF_CHANNELGROUPS] = {

};
