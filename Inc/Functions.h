//File for Function declaratons

#ifndef FUNCTION_H_
#define FUNCTION_H_


extern volatile uint8_t start;
extern volatile uint8_t led1;
extern volatile uint8_t led2;
//Functions in timer.c
void timer_init();
void motor_direction(int a,int b,char value);
void motor_stop();

//Functions in uart.c
void uart_init();
void uart_receive();
void USART2_IRQHandler();
void uart_command_handler(char value);

//Function in i2c_lcd.c
void i2c_init();
void I2C1_Start(void);
void I2C1_WriteAddr(uint8_t address,uint8_t rw);
void I2C1_WriteData(uint8_t data);
void I2C1_Stop(void);
void LCD_Pulse(uint8_t data);
void LCD_SendNibble(uint8_t nibble, uint8_t mode);
void LCD_SendByte(uint8_t value, uint8_t mode);
void LCD_Command(uint8_t cmd);
void LCD_Data(uint8_t data);
void LCD_Init(void);
void LCD_SetCursor(uint8_t row, uint8_t col);
void LCD_Print(char *str);
void send_msg(char *data);

//Functions in SPI.c
void SPI_init();
void spi_lsi_init();
void SPI1_SEND(uint8_t *txbuffer,uint8_t size);
void SPI1_RECEIVE(uint8_t *rxbuffer,uint8_t size);
void cs_enable();
void cs_disable();

//Functions in ADC_LDR.c
void adc_init();

void delay(int X);

//Functions of LIS302DL
void write(uint8_t address,uint8_t value);
void read(uint8_t address, uint8_t *rxdata, uint32_t len);
void Lis_init();
void get_value(accelorometer *value);
int get_devid();

long int sq_root(long int var);


#endif /* FUNCTION_H_ */
