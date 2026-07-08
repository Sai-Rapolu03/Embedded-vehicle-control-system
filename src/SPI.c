/*
 * SPI.c
 *
 *  Created on: Jun 30, 2026
 *      Author: HP
 */


#include "Header.h"
#include "FUNCTION.H"

void SPI_init()
{
	RCC-> AHB1ENR 	|= (1<<0);//RCC GPIOA
	RCC-> AHB1ENR	|= (1<<4);//RCC GPIOE


	GPIOA->MODER 	&= ~(3<<10);
	GPIOA->MODER 	|= (2<<10); //PA5
	GPIOA->MODER	&= ~(3<<12);
	GPIOA->MODER 	|= (2<<12); //PA6
	GPIOA->MODER	&= ~(3<<14);
	GPIOA->MODER	|= (2<<14); //PA7
	GPIOE->MODER	&= ~(3<<6);
	GPIOE->MODER 	|= (1<<6); //PE3 OUTPUT

	GPIOA->AFRL		|= (5<<20); //AF FOR PA5
	GPIOA->AFRL		|= (5<<24); //AF FOR PA6
	GPIOA->AFRL		|= (5<<28); //AF FOR PA7


	GPIOA->OTYPER	=0; //Output push pull
	GPIOA->OSPEEDR	|= (0x3F<<10); //SET HIGH SPEED FOR PA5,PA6,PA7

}

void spi_lsi_init()
{
	RCC-> APB2ENR	|= (1<<12); //RCC SPI
	cs_disable();

	SPI->CR1		|= (1<<2);//ENABLE MASTER MODE
	SPI->CR1		&= ~(7<<3);
	SPI->CR1		|= (2<<3); //CLK DIVIDER
	SPI->CR1 		|= (1<<0); //CPHA
	SPI->CR1 		|= (1<<1); //CPOL
	SPI->CR1 		&= ~(1<<7); //MSB FIRST
	SPI->CR1		|= (1<<9); //SSM
	SPI->CR1		|= (1<<8); //SSI
	SPI->CR1		|= (1<<6); //Enable SPI

}

void SPI1_SEND(uint8_t *txbuffer,uint8_t size)
{
	volatile uint8_t dummy;
	char temp;

	for(uint32_t i=0;i<size;i++)
	{
		while(!(SPI->SR & (1<<1))); //WAIT FOR TXE
		temp= txbuffer[i];
		SPI->DR= temp;

		while(!(SPI->SR & (1<<0))); //WAIT FOR RXNE
		dummy=SPI->DR;
	}
	 while(SPI->SR & (1<<7)); //CHECK BUSY FLAG
}

void SPI1_RECEIVE(uint8_t *rxbuffer,uint8_t size)
{
	for(uint32_t i=0;i<size;i++)
	{
		while(!(SPI->SR & (1<<1))); //WAIT FOR TXE
		SPI->DR 	= 0xFF;

		while(!(SPI->SR & (1<<0))); //WAIT FOR RXNE
		rxbuffer[i]	= SPI->DR;
	}
}

void cs_enable()
{
	GPIOE->BSRR	|= (1<<19); //PE3 RESET
}

void cs_disable()
{
	GPIOE->BSRR	|= (1<<3); //PE3 SET
}
