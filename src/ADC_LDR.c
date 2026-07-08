
#include "Header.h"
#include "FUNCTION.H"

void adc_init()
{

	RCC-> APB2ENR 	|= (1<<8); //RCC FOR ADC1
	RCC-> AHB1ENR 	|= (1<<0);//RCC GPIOA
	RCC-> AHB1ENR 	|= (1<<3); //RCC for GPIOD

	GPIOA-> MODER 	&= ~(3<<8);
	GPIOA-> MODER 	&= ~(3<<10);
	GPIOA-> MODER 	|= (3<<8); //ANALOG MODE FOR PA4
	GPIOD-> MODER	|= (1<<28); //Output for LED

	ADC->CR1		&= ~(3<<24); //12-bit resolution
	ADC->SQR3		=4 ; //Channel 4
	ADC->CR2		|= (1<<0); //ADC ON

}
