
#include "Header.h"
#include "FUNCTION.H"

volatile uint8_t led1=0;
volatile uint8_t led2=0;
void timer_init()
{
	RCC-> APB1ENR	|= (1<<0); //ENABLE TIMER 2 CLOCK
	RCC-> AHB1ENR	|= (1<<0); // Enable GPIOA clock
	RCC-> AHB1ENR 	|= (1<<1); //ENABLE GPIOB CLOCK

	GPIOA->MODER	|= (2<<0); //PA0
	GPIOA->MODER 	|= (2<<2); //PA1

	GPIOB->MODER 	|= (1<<0); //PB0
	GPIOB->MODER 	|= (1<<2); //PB1
	GPIOB->MODER 	|= (1<<20); //PB10
	GPIOB->MODER 	|= (1<<22); //PB11

	GPIOA->AFRL		&= ~(0x0F<<0);
	GPIOA->AFRL 	&= ~(0x0F<<4);
	GPIOA->AFRL		|= (1<<0); //ALTERNATE FUNCTION TO PA0
	GPIOA->AFRL		|= (1<<4); //ALTERNATE FUNCTION TO PA1

	TIM-> PSC		= 15; //PRE-SCALAR VALUE
	TIM-> ARR		=999; //AUTO RELOAD
	TIM->CCMR1		|= (1<<3); //ENABLE COMPARE 1 PRELOAD
	TIM->CCMR1		|= (1<<11); //ENABLE COMPARE 2 PRELOAD
	TIM->CCMR1		&= ~(7<<4);
	TIM->CCMR1		&= ~(7<<12);
	TIM->CCMR1		|= (6<<4); //PWM MODE FOR CHANNEL 1
	TIM->CCMR1		|= (6<<12); //PWM MODE FOR CHANNEL 2
	TIM->CCR1		=250; //25% DUTY CYCLE CH-1
	TIM->CCR2 		=250; //25% DUTY CYCLE CH-2
	TIM->CCER		|= (1<<0); //Enable channel-1
	TIM->CCER		|= (1<<4); //Enable channel-2
	TIM->CR1		|= (1<<7); //ARP ENABLE
	TIM->CR1 		|= (1<<0); //COUNTER ENABLE

}


void motor_direction(int a,int b,char value)
{
	if(UART->SR & (1<<7))
			{
				UART->DR = value;
				delay(2000);
			}
	if((a==1) & (b==1)) //FORWARD DIRECTION
	{
		if(UART->SR & (1<<7))
		{
			UART->DR = 'l';
			delay(2000);
		}
		TIM->CCR1		=250; //25% DUTY CYCLE CH-1
		TIM->CCR2 		=250; //25% DUTY CYCLE CH-2
		GPIOB->ODR 	|= (1<<0); //IN1 ON PB0
		//delay(500000);
		GPIOB->ODR	&= ~(1<<1); //IN2 OFF PB1
		//delay(200000);
		GPIOB->ODR  |= (1<<10); //IN3 ON
		GPIOB->ODR 	&= ~(1<<11); //IN4 OFF
		led1=0;
		led2=0;
		//delay(500000);
	}
	else if((a==0) & (b==1)) //RIGHT
	{
		TIM->CCR1		=250; //25% DUTY CYCLE CH-1
		TIM->CCR2 		=250; //25% DUTY CYCLE CH-2
		GPIOB->ODR 	&= ~(1<<0); //IN1 OFF
		GPIOB->ODR	|= (1<<1); //IN2 ON
		GPIOB->ODR  |= (1<<10); //IN3 ON
		GPIOB->ODR 	&= ~(1<<11); //IN4 OFF

		led1=1;
		led2=0;

		//GPIOD->ODR 	|= (1<<12); //Green LED ON(PD12)
	}
	else if((a==1) & (b==0)) //LEFT
	{
		TIM->CCR1		=250; //25% DUTY CYCLE CH-1
		TIM->CCR2 		=250; //25% DUTY CYCLE CH-2
		GPIOB->ODR 	|= (1<<0); //IN1 ON
		GPIOB->ODR	&= ~(1<<1); //IN2 OFF
		GPIOB->ODR  &= ~(1<<10); //IN3 OFF
		GPIOB->ODR 	|= (1<<11); //IN4 ON

		led2=1;
		led1=0;
		//GPIOD->ODR 	|= (1<<13); //Orange LED ON(PD13)
	}
	else if((a==0) & (b==0)) //Back
	{
		TIM->CCR1		=250; //25% DUTY CYCLE CH-1
		TIM->CCR2 		=250; //25% DUTY CYCLE CH-2
		GPIOB->ODR 	&= ~(1<<0); //IN1 OFF
		GPIOB->ODR	|= (1<<1); //IN2 ON
		GPIOB->ODR  &= ~(1<<10); //IN3 OFF
		GPIOB->ODR 	|= (1<<11); //IN4 ON

		led1=0;
		led2=0;
	}
}
void motor_stop()
{
	led1=0;
	led2=0;
	GPIOB->ODR 	&= ~(1<<0); //IN1 OFF
	GPIOB->ODR	&= ~(1<<1); //IN2 OFF
	GPIOB->ODR  &= ~(1<<10); //IN3 OFF
	GPIOB->ODR 	&= ~(1<<11); //IN4 OFF
}
