
#include "Header.h"
#include "FUNCTION.H"
/*
void USART2_IRQHandler()
{
    if (UART->SR & (1<<5)) // RXNE flag
    {
        char value;
        value= UART->DR;
        uart_command_handler(value);

    }
}*/

volatile uint8_t start=0;


void uart_receive()
{
	/*if(UART->SR & (1<<7)) //TXE Flag
	{
		UART->DR = 'X';
		delay(20000);
		UART->DR = 'Y';
		delay(20000);
		UART->DR ='Z';
		delay(20000);
	}*/
	if (UART->SR & (1<<5)) // RXNE flag
	{
		char value;
	    value= UART->DR;
	    uart_command_handler(value);
	 }
}

void uart_init()
{
	RCC->APB1ENR	|= (1<<17); //CLK FOR UART
	RCC->AHB1ENR	|= (1<<0); //CLK FOR GPIOA

	GPIOA->MODER 	&= ~(2<<4);
	GPIOA->MODER 	&= ~(2<<6);
	GPIOA->MODER 	|= (2<<4); //AFRL FOR PA2
	GPIOA->MODER 	|= (2<<6); //AFRL FOR PA3

	GPIOA->AFRL		&= ~(0x0F<<8);
	GPIOA->AFRL 	&= ~(0x0F<<12);
	GPIOA->AFRL 	|= (7<<8); //ALTERNATE FUNCTION OF PA2
	GPIOA->AFRL 	|= (7<<12); //ALTERNATE FUNCTION OF PA3

	UART->BRR		= 0x683; //BAUD RATE 9600
	UART->CR1		|= (1<<3); //TRANSMITTER ENABLE
	UART->CR1		|= (1<<2); //RECEIVER ENABLE
	//UART->CR1 		|= (1<<7); //TX INTERRUPT ENABLE
	UART->CR1		|= (1<<5); //RX INTERRUPT ENABLE
	UART->CR1 		|= (1<<13); //UART ENABLE

	//LCD_SetCursor(0,0);
	//LCD_Print("System OFF");


	//uart_receive();

	//NVIC_ISER1		|= (1<<6); //NVIC FOR UART2
}

void uart_command_handler(char value)
{
	switch(value)
	{
	case'S' : //Start
	{
		start=1;
		LCD_Command(0x01); //Clear LCD
		LCD_SetCursor(0,0);
		LCD_Print("System ON");
		LCD_SetCursor(1,0);
		LCD_Print("Standby Mode");
		led1=0;
		led2=0;
		break;
	}
	case 'F' : //Forward
	{
		if(start)
		{
			LCD_SetCursor(1,0);
			LCD_Print("Active Mode");
			motor_direction(1,1,value); //value is added extra
		}
		break;
	}
	case 'R' : //Right
	{
		if(start)
		{
			LCD_SetCursor(1,0);
			LCD_Print("Active Mode");
			motor_direction(0,1,value);
		}
		break;
	}
	case 'B' : //Backward
	{
		if(start)
		{
			LCD_SetCursor(1,0);
			LCD_Print("Active Mode");
			motor_direction(0,0,value);
		}
		break;
	}
	case 'L' : //Left
	{
		if(start)
		{
			LCD_SetCursor(1,0);
			LCD_Print("Active Mode");
			motor_direction(1,0,value);
		}
		break;
	}
	case 'P' : //Pause
	{
		if(start)
		{
			LCD_SetCursor(1,0);
			LCD_Print("                 ");
			LCD_SetCursor(1,0);
			LCD_Print("Standby Mode");
			led1=0;
			led2=0;
			motor_stop();
			//motor_direction(1,0,value);
		}
		break;
	}
	case 'E' : //Stop
	{
		start=0;
		led1=0;
		led2=0;
		LCD_Command(0x01); //Clear LCD
		LCD_SetCursor(0,0);
		LCD_Print("System OFF");
		motor_stop();

		break;
	}

	}
}
