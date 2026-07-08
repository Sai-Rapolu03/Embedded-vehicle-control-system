#include <stdio.h>
#include <stdint.h>
#include <math.h>

#include "Header.h"
#include "FUNCTION.H"

int main(void)
{
	//int8_t x,y,z;
	//printf("into main");
	accelorometer data;
	timer_init(); //Initializing timers
	adc_init(); //Initializing ADC for LDR

	uart_init(); //UART Initializing
	Lis_init(); //Accelerometer(LIS3DSH) Initialized

	i2c_init(); //I2C Initialization
	LCD_Init(); //LCD Display Initialization
	//printf("System Ready");

	uint8_t devid=get_devid();

	volatile uint32_t value;
	long int temp1,temp2,j,count;
	long int mag;
	char magnitude[50];
	/*if(UART->SR & (1<<7))
	{
		UART->DR = 'A';
		delay(20000);
		UART->DR = 'X';
		delay(20000);
		UART->DR = 'Y';
		delay(20000);
	}*/
	//GPIOB->ODR 	|= (1<<0); //IN1 ON PB0
		//	delay(500000);
	LCD_SetCursor(0,0);
	LCD_Print("System OFF");


	GPIOD->MODER	&= ~(3<<24);
	GPIOD->MODER	&= ~(3<<26);

	GPIOD->MODER	|= (1<<24);//PD12
	GPIOD->MODER	|= (1<<26);//PD13

	GPIOD->ODR 		&= ~(1<<12); //LED for Right
	GPIOD->ODR 		&= ~(1<<13);
	GPIOD->ODR 		&= ~(1<<14);

	while(1)
	{
		uart_receive();
		get_value(&data);

		printf("device=%d\n",devid);
		delay(500000);
		printf("X=%d Y=%d Z=%d\r\n",data.x,data.y,data.z);
		delay(5000);
		long int var=((data.x * data.x)+(data.y*data.y)+(data.z*data.z));
		printf("Var=%lu\r\n",var/1000);
		//mag=pow(var,0.5);
		mag=sq_root(var/1000);
		printf("Magnitude=%lu\r\n",mag);

		j=0;
		count=0;
		temp1=mag;
		while(temp1>0)
		{
			temp2=temp1%10;
			temp1=temp1/10;
			magnitude[j]=temp2+'0';
			j++;
		}
		magnitude[j]= '\0';
		j=0;
		while(magnitude[j] != '\0')
		{
			count++;
			j++;
		}
		for(j=0;j<count/2;j++)
		{
			magnitude[j] ^= magnitude[count-j-1];
			magnitude[count-j-1] ^= magnitude[j];
			magnitude[j] ^= magnitude[count-j-1];
		}
		printf("mag=%s\r\n",magnitude);

		if(start==1)
		{

		ADC->CR2 	|= (1<<30); //Start conversion

		while(!(ADC->SR & (1<<1)));
		value=ADC->DR;

		printf("LDR = %lu\r\n",value);
		delay(20000);
		if(led1==1)
		{
			GPIOD->ODR 	|= (1<<12); //Green LED ON(PD12)
		}
		else
		{
			GPIOD->ODR 	&= ~(1<<12); //Green LED OFF(PD12)
		}

		if(led2==1)
		{
			GPIOD->ODR 	|= (1<<13); //Orange LED ON(PD13)
		}
		else
		{
			GPIOD->ODR 	&= ~(1<<13); //Orange LED OFF(PD13)
		}

		if(value>1500) //LDR value checking
		{
			GPIOD->ODR 	|= (1<<14); //RED LED ON
			delay(2000);

			LCD_SetCursor(3,0);
			LCD_Print("                  ");
			LCD_SetCursor(3,0);
			LCD_Print("Head Light ON");
			delay(1000);
		}
		else
		{
			LCD_SetCursor(3,0);
			LCD_Print("Head Light OFF");
			GPIOD->ODR 	&= ~(1<<14); // RED LED OFF
			delay(20000);
		}
		//LCD_SetCursor(0,0);
		//LCD_Print("Car is Started");
		LCD_SetCursor(2,0);
		LCD_Print("MAG:");
		LCD_SetCursor(2,4);
		LCD_Print(magnitude);

		}
	}
}

void delay(int X)
{
	for(uint32_t i=0;i<X;i++)
	{

	}
}


long int sq_root(long int n)
{
    long int low = 0;
    long int high = n;
    long int ans = 0;

    while(low <= high)
    {
        long int mid = low + (high - low) / 2;

        long long sq = (long long)mid * mid;

        if(sq == n)
            return mid;

        if(sq < n)
        {
            ans = mid;
            low = mid + 1;
        }
        else
        {
            high = mid - 1;
        }
    }

    return ans;
}
