//To read values of on board accelorometer


#include "Header.h"
#include "FUNCTION.H"

void write(uint8_t address,uint8_t value)
{
	uint8_t tx[2];
	address 	&= ~(1<<7);//clearing RW
	//address 	&= ~(1<<6); //Clearing multibyte enable
	tx[0]		= address;
	tx[1]		= value;
	cs_enable();
	SPI1_SEND(tx,2);
	cs_disable();
}

void read(uint8_t address, uint8_t *rxdata, uint32_t len)
{
	uint8_t cmd = 	address | 0x80;
	//if(len > 1)
	//{
		//cmd = address| 0xC0;
	//}
	cs_enable();
	SPI1_SEND(&cmd,1);
	SPI1_RECEIVE(rxdata,len);
	cs_disable();
}
void Lis_init()
{
	 SPI_init();
	 spi_lsi_init();
	 write(Ctrl_Reg4,0x00);
	 write(Ctrl_Reg4,0x67);
	 write(Ctrl_Reg5,0x00);
	 write(Ctrl_Reg6,0x00);
	 write(Ctrl_Reg6,0x10);
	 //write(Ctrl_Reg2,0x00);
	 //write(Ctrl_Reg2,0x80);
}

void get_value(accelorometer *value)
{
	uint8_t data[6];
	read(OUT_X_L,data,6);

	value->x 	= ((data[1]<<8) | data[0]);
	value->y	= ((data[3]<<8) | data[2]);
	value->z	= ((data[5]<<8) | data[4]);
    //read(Out_X,(uint8_t *)x, 1);
    //read(Out_Y,(uint8_t *)y, 1);
    //read(Out_Z,(uint8_t *)z, 1);
}

int get_devid()
{
	uint8_t id;
	read(WHO_AM_I,&id,1);
	return id;
}
