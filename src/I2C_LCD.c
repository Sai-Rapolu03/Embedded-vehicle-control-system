
#include "Header.h"
#include "FUNCTION.H"

void i2c_init()
{
	RCC->AHB1ENR	|= (1<<1); //Clock for GPIOB
	RCC->APB1ENR	|= (1<<21); //Clock for I2C

	GPIOB->MODER	&= ~(3<<12);
	GPIOB->MODER 	&= ~(3<<14);

	GPIOB->MODER	|= (2<<12);//PB6
	GPIOB->MODER	|= (2<<14);//PB7

	GPIOB->AFRL		&= ~(0xF<<24);
	GPIOB->AFRL 	&= ~(0xF<<28);

	GPIOB->AFRL 	|= (4<<24); //PB6
	GPIOB->AFRL 	|= (4<<28); //PB7
	GPIOB->OTYPER	|= (3<<6); //Setting open drain
	GPIOB->PUPDR	&= ~(3<<12);
	GPIOB->PUPDR	&= ~(3<<14);

	GPIOB->PUPDR	|= (1<<12); //Enabling pull up resistors
	GPIOB->PUPDR	|= (1<<14); //Enabling pull up resistors

	//I2C configuration

	I2C->CR1 		|= (1<<15); //Reset
	I2C->CR1		&= ~(1<<15); //Clearing reset
	I2C->CR2		= 16; //Setting frequency to 16MHZ
	I2C->CCR		= 80; //CCR=100khz
	I2C->TRISE  	= 17; //Risetime
	I2C->CR1 		|= (1 << 0); //Enable I2C

}

void I2C1_Start(void)
{
	I2C->CR1|= (1<<8); //Start generation
	while(!(I2C-> SR1 & (1<<0))); //ACK for start condition
}

void I2C1_WriteAddr(uint8_t address,uint8_t rw)
{
	volatile uint32_t temp;

	I2C->DR = (address << 1) | rw;      // 7-bit addr + R/W
	while(!(I2C->SR1 & (1<<1)));        // wait ADDR

	temp = I2C->SR1;                    // clear ADDR
	temp = I2C->SR2;


}

void I2C1_WriteData(uint8_t data)
{
	while(!(I2C->SR1 & (1<<7))); //TXE
	I2C->DR	= data;
	while(!(I2C->SR1 & (1<<2))); //BYTE TRANSFER FINISHED
}

void I2C1_Stop(void)
{
	I2C->CR1 	|= (1<<9); //STOP GENERATION
}

void LCD_Pulse(uint8_t data)
{
	data |= (1<<2); //ENABLE BIT SET
	I2C1_WriteData(data);
	delay(20000);
	data &= ~(1<<2); //ENABLE BIT CLEAR
	I2C1_WriteData(data);
	delay(20000);
}

void LCD_SendNibble(uint8_t nibble, uint8_t mode)
{
	uint8_t data=0;
	data 	= (nibble & 0xF0);
	data 	|= LCD_BACKLIGHT;
	if(mode)
		data |= LCD_RS;                 // RS=1 for data
	else
	    data &= ~LCD_RS;                // RS=0 for command

	LCD_Pulse(data);
}

void LCD_SendByte(uint8_t value, uint8_t mode)
{
	LCD_SendNibble(value & 0xF0, mode); //Sending higher nibble
	LCD_SendNibble((value << 4) & 0xF0, mode); //Sending lower nibble
}

void LCD_Command(uint8_t cmd)
{
	I2C1_Start();
	I2C1_WriteAddr(LCD_ADDR , 0);
	LCD_SendByte(cmd,0);
	I2C1_Stop();
}

void LCD_Data(uint8_t data)
{
	I2C1_Start();
	I2C1_WriteAddr(LCD_ADDR, 0);
	LCD_SendByte(data,1);
	I2C1_Stop();
}

void LCD_Init(void)
{
	delay(20000);
	I2C1_Start();
	I2C1_WriteAddr(LCD_ADDR, 0);
	LCD_SendNibble(0x30,0);
	delay(20000);
	LCD_SendNibble(0x30,0);
	delay(20000);
	LCD_SendNibble(0x30,0);
	delay(20000);
	LCD_SendNibble(0x20,0);//4-bit mode
	delay(20000);
	I2C1_Stop();

	LCD_Command(0x28);// 4-bit,2line
	delay(20000);
	LCD_Command(0x0C);//Display on
	delay(20000);
	LCD_Command(0x06);// Entry mode
	delay(20000);
	LCD_Command(0x01);//Clear
	delay(20000);
}

void LCD_SetCursor(uint8_t row, uint8_t col)
{
	uint8_t value;
	if(row==0)
	{
		value= 0x80+col; // OR with 0x80 indicates that as DDRAM address
	}
	else if(row==1)
	{
		value=0xC0+col;
	}
	else if(row == 2)
	{
		value=0x94+col;
	}
	else
	{
		value =0xD4+col;
	}
	LCD_Command(value);
}

void LCD_Print(char *str)
{
	volatile uint32_t i=0;
	while(str[i] != '\0')
	{
		LCD_Data(str[i]);
		i++;
	}
}
