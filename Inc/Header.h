/*
 * Header.h
 *
 *  Created on: Jun 29, 2026
 *      Author: HP
 */

#ifndef HEADER_H_
#define HEADER_H_
#include <stdio.h>
#include <stdint.h>


#define	RCC_Base	0x40023800
#define Tim2_Base	0x40000000
#define UART2_Base 	0x40004400
#define SPI1_Base	0x40013000
#define I2C1_Base	0x40005400
#define	ADC_Base	0x40012000
#define	GPIOA_Base	0x40020000
#define	GPIOB_Base	0x40020400
#define GPIOD_Base	0x40020C00
#define GPIOE_Base	0x40021000
#define NVIC_BASE	0xE000E100

typedef struct
{
	volatile uint32_t CR ;
	volatile uint32_t PLLCFGR ;
	volatile uint32_t CFGR ;
	volatile uint32_t CIR ;
	volatile uint32_t AHB1RSTR ;
	volatile uint32_t AHB2RSTR ;
	volatile uint32_t Reserved[2] ;
	volatile uint32_t APB1RSTR;
	volatile uint32_t APB2RSTR ;
	volatile uint32_t Reserved0[2] ;
	volatile uint32_t AHB1ENR ;
	volatile uint32_t AHB2ENR ;
	volatile uint32_t Reserved1[2] ;
	volatile uint32_t APB1ENR ;
	volatile uint32_t APB2ENR ;
	volatile uint32_t Reserved2[2] ;
	volatile uint32_t AHB1LPENR ;
	volatile uint32_t AHB2LPENR ;
	volatile uint32_t Reserved3[2] ;
	volatile uint32_t APB1LPENR ;
	volatile uint32_t APB2LPENR ;
	volatile uint32_t Reserved4[2] ;
	volatile uint32_t BDCR ;
	volatile uint32_t CSR ;
	volatile uint32_t Reserved5[2] ;
	volatile uint32_t SSCGR	;
	volatile uint32_t PLLI2SCFGR ;
	volatile uint32_t Reserved6 ;
	volatile uint32_t DCKCFGR ;

}RCC_typedef;


typedef struct
{
	volatile uint32_t 	CR1;
	volatile uint32_t 	CR2;
	volatile uint32_t	SMCR;
	volatile uint32_t	DIER;
	volatile uint32_t	SR;
	volatile uint32_t	EGR;
	volatile uint32_t	CCMR1;
	volatile uint32_t	CCMR2;
	volatile uint32_t	CCER;
	volatile uint32_t	CNT;
	volatile uint32_t	PSC;
	volatile uint32_t	ARR;
	volatile uint32_t	Reserved0;
	volatile uint32_t	CCR1;
	volatile uint32_t	CCR2;
	volatile uint32_t	CCR3;
	volatile uint32_t	CCR4;
	volatile uint32_t	Reserved1;
	volatile uint32_t	 DCR;
	volatile uint32_t	 DMAR;
	volatile uint32_t	OR;
}TIM_typedef;


typedef struct
{
	volatile uint32_t SR;
	volatile uint32_t DR;
	volatile uint32_t BRR;
	volatile uint32_t CR1;
	volatile uint32_t CR2;
	volatile uint32_t CR3;
	volatile uint32_t GTPR;
}UART_typedef;

typedef struct
{
	volatile uint32_t CR1;
	volatile uint32_t CR2;
	volatile uint32_t SR;
	volatile uint32_t DR;
	volatile uint32_t CRCPR;
	volatile uint32_t RXCRCR;
	volatile uint32_t TXCRCR;
	volatile uint32_t I2SCFGR;
	volatile uint32_t I2SPR;

}SPI_typedef;


typedef struct
{
	volatile uint32_t	CR1;
	volatile uint32_t	CR2;
	volatile uint32_t	OAR1;
	volatile uint32_t	OAR2;
	volatile uint32_t	DR;
	volatile uint32_t	SR1;
	volatile uint32_t	SR2;
	volatile uint32_t	CCR;
	volatile uint32_t	TRISE;
	volatile uint32_t	FLTR;
}I2C1_typedef;


typedef struct
{

	volatile uint32_t SR ;
	volatile uint32_t CR1 ;
	volatile uint32_t CR2 ;
	volatile uint32_t SMPR1 ;
	volatile uint32_t SMPR2 ;
	volatile uint32_t JOFR1 ;
	volatile uint32_t JOFR2 ;
	volatile uint32_t JOFR3 ;
	volatile uint32_t JOFR4 ;
	volatile uint32_t HTR ;
	volatile uint32_t LTR ;
	volatile uint32_t SQR1 ;
	volatile uint32_t SQR2 ;
	volatile uint32_t SQR3 ;
	volatile uint32_t JSQR ;
	volatile uint32_t JDR1 ;
	volatile uint32_t JDR2 ;
	volatile uint32_t JDR3 ;
	volatile uint32_t JDR4 ;
	volatile uint32_t DR ;
	volatile uint32_t CCR ;

}ADC_typedef;


typedef struct
{
	volatile uint32_t 	MODER;
	volatile uint32_t	OTYPER;
	volatile uint32_t	OSPEEDR;
	volatile uint32_t	PUPDR;
	volatile uint32_t	IDR;
	volatile uint32_t	ODR;
	volatile uint32_t	BSRR;
	volatile uint32_t	LCKR;
	volatile uint32_t	AFRL;
	volatile uint32_t	AFRH;

}GPIO_typedef;


#define RCC 	((RCC_typedef *)(RCC_Base))
#define TIM		((TIM_typedef*)(Tim2_Base))
#define UART	((UART_typedef *)(UART2_Base))
#define SPI		((SPI_typedef *)(SPI1_Base))
#define I2C		((I2C1_typedef *)(I2C1_Base))
#define ADC		((ADC_typedef *)(ADC_Base))
#define GPIOA	((GPIO_typedef *)(GPIOA_Base))
#define GPIOB	((GPIO_typedef *)(GPIOB_Base))
#define GPIOD	((GPIO_typedef *)(GPIOD_Base))
#define GPIOE	((GPIO_typedef *)(GPIOE_Base))
#define  NVIC_ISER1		(*(volatile uint32_t *)(NVIC_BASE+0x04))


#define LCD_BACKLIGHT  0x08   // bit 3
#define LCD_ENABLE     0x04   // bit 2
#define LCD_RW         0x02   // bit 1 read
#define LCD_RS         0x01   // bit 0
#define LCD_ADDR  	   0x27

#define Ctrl_Reg1	0x21
#define Ctrl_Reg2	0x22
#define Ctrl_Reg3	0x23
#define Ctrl_Reg4	0x20
#define Ctrl_Reg5	0x24
#define Ctrl_Reg6	0x25
#define OUT_X_L		0x28
#define OUT_X_H		0x29
#define OUT_Y_L		0x2A
#define OUT_Y_H		0x2B
#define OUT_Z_L		0x2C
#define OUT_Z_H		0x2D
#define WHO_AM_I 	0x0F //Device id reg

typedef struct
{
	int16_t x;
	int16_t y;
	int16_t z;
}accelorometer;

#endif /* HEADER_H_ */
