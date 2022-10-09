/*********************************************************/
/* author  : Farouk                                      */
/* Version : v02                                         */
/* Date    : August 14 2022                              */
/*********************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "RCC_Interface.h"
#include "NVIC_interface.h"

#include "Uart_REG.h"
#include "Uart.h"
#include "Uart_Cfg.h"


UART_TypeDef* SerialPorts[NUM_OF_SERIAL_PORTS] = {
	(UART_TypeDef*) UART1_BASE_ADDRESS,
	(UART_TypeDef*) UART2_BASE_ADDRESS,
	(UART_TypeDef*) UART3_BASE_ADDRESS
};

void Uart_Init(void)
{
	u8 i;
	for(i=0; i<NUM_OF_CHANNELS; i++)
	{
		UART_TypeDef* Uart = SerialPorts[ConfigList[i].serialID];
		/* Enable Clk */
		switch( ConfigList[i].serialID )
		{
			case 0:
				RCC_voidEnableClock(RCC_APB2,14);
				MNVIC_voidEnableInterrupt(37);
			break;
			case 1:
				RCC_voidEnableClock(RCC_APB1,17);
				MNVIC_voidEnableInterrupt(38);
			break;
			case 2:
				RCC_voidEnableClock(RCC_APB1,18);
				MNVIC_voidEnableInterrupt(39);
			break;
			default: break;
		}
		
		/* Calculate buad rate */
        float ClkDivider = CLK/(16.0*ConfigList[i].buadrate);
        unsigned short mantissa = (unsigned short int)ClkDivider;
        unsigned int fraction = (unsigned int)((ClkDivider-(float)mantissa) * 16 + 0.5) ;

        Uart->BRR = (mantissa<<4 & 0x0ff0U) |(fraction & (0x0fU));

		
		/* Word length 8-bytes */
        Uart->CR1 &= ~(1<< 12); /* clear the bit M */
        Uart->CR1 |= (ConfigList[i].dataSize<< 12); /* put the value into the bit M */
		
		
		/* Enable selected interrupts */
        Uart->CR1 &= ~(7 << 5); // clear interrupts fields
        Uart->CR1 |= ConfigList[i].interrupts.RXNE<< 5;
        Uart->CR1 |= ConfigList[i].interrupts.TC<< 6;
        Uart->CR1 |= ConfigList[i].interrupts.TXE<< 7;
		
		// choose mode
		Uart->CR1 &= ~(3 << 2U); // clear bit field
		Uart->CR1 |= ConfigList[i].uartMode << 2U ; // set value
		
		
		// uart enable
		Uart->CR1 |= 1 << 13U;
	
		/* reset all flags */
		Uart->SR = 0;
	}
	
}



void UART_SendSync(u8 DeviceId, u8 data)
{
    if(DeviceId < MAX_NUM_OF_DEVICES)
    {
        UART_TypeDef* Uart = SerialPorts[ConfigList[DeviceId].serialID];
        Uart->DR = data;
        /* Wait until tranfer complete flag is set */
        while( !GET_BIT(Uart->SR,6) );
        CLR_BIT(UART1->SR,6);
    }
}


void UART_SendStr(u8 DeviceId, u8* str)
{
	while(*str != '\0')
	{
		UART_SendSync(DeviceId, *str);
		str++;
	}

}
u8 UART_RecvSync(u8 DeviceId)
{
    if(DeviceId < MAX_NUM_OF_DEVICES)
    {

        UART_TypeDef* Uart = SerialPorts[ConfigList[DeviceId].serialID];
        /* Wait until receive buffer is not empty */
        while( !GET_BIT(Uart->SR,5) );

        return Uart->DR;
    }
    return 0xff; /* Error */
}

u8 UART_RecvWithTimeout(u8 DeviceId)
{
	u8 data=0;
	u16 timeout=0;
	if(DeviceId < MAX_NUM_OF_DEVICES)
	{

		UART_TypeDef* Uart = SerialPorts[ConfigList[DeviceId].serialID];
		// wait until data receive completes
		while( GET_BIT(Uart->SR,5) == 0 )// stops here
		{
			timeout++;
			if(timeout == 40000)
			{
				data = 255;
				break;
			}
		}

		if(data == 0)
		{
			data = Uart->DR;
		}

		return data;
	}

	return INVALID_UART_ID_ERROR;
}

