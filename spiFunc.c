#include <stdio.h>
#include <spiFunc.h>
#include <wiringPi.h>
#include <wiringPiSPI.h>

#define READ 0x80;
#define WRITE 0x00;

unsigned char data[4] = {0, 0, 0, 0};

/*************************************************************************************
int setUpSPI(int channel, int baudrate)
	Sets up the SPI module to run at a scpecific baudrate between 500kHz to 32MHz
	for either channel 0 or channel 1.
**************************************************************************************/
int setUpSPI(int channel, int baudrate)
{
	return wiringPiSPISetup(channel, baudrate);
}

/************************************************************************************
unsigned char XGAttached(int ss)
	Checks if the accelerometer and gyroscope are attached and returns 1 for yes
	and 0 for no. ss is 0 for channel 0 and 1 for channel 1.
*************************************************************************************/
unsigned char XGAttached(int ss)
{
	const int WHO_AM_I = 0x0F;

	data[0] = WHO_AM_I | READ;

	wiringPiSPIDataRW(ss, data, 2);

	if(data[1] == 0x68) return 1;
	else return 0;
}

/************************************************************************************
unsigned char MAttached(int ss)
	Checks if the magentometers is attached and return a 1 for yes and a 0 for no.
	ss is 0 for chnnel 0 and 1  for channel 1.
*************************************************************************************/
unsigned char MAttached(int ss)
{
	const int WHO_AM_I = 0x0F;

	data[0] = WHO_AM_I | READ;

	wiringPiSPIDataRW(ss, data, 2);

	if(data[1] == 0x3D) return 1;
	else return 0;
}

void initialzeXGM(int ssAG, int ssM)
{
	// ACCELEROMETER and GYROSCOPE

	// CTRL_REG1_G (10h) - 1100 0011 - 0xC3
	data[0] = 0x10;
	data[1] = 0xC3;
	wiringPiSPIDataRW(ssAG, data, 2);

	// CTRL_REG2_G (11h) - 0000 0000 - 0x00
	data[0] = 0x11;
	data[1] = 0x00;
	wiringPiSPIDataRW(ssAG, data, 2);

	// CTRL_REG3_G (12h)

	// ORIENT_CFG_G (13h)

	// CTRL_REG6_XL (20h) - 1101 1000 - 0xD8
	data[0] = 0x20;
	data[1] = 0xD8;
	wiringPiSPIDataRW(ssAG, data, 2);

	// CTRL_REG7_XL (21h) - 00000000

	// CTRL_REG8 (22h) - 0000 0000
	data[0] = 0x22;
	data[1] = 0x00;
	wiringPiSPIDataRW(ssAG, data, 2);

	// CTRL_REG9 (23h) - 0000 0100
	data[0] = 0x23;
	data[1] = 0x04;
	wiringPiSPIDataRW(ssAG, data, 2);

	// MAGNETOMETER

	// CTRL_REG1_M (20h) - 0111 1100
	data[0] = 0x20;
	data[1] = 0x7C;
	wiringPiSPIDataRW(ssM, data, 2);

	//




int readAccZ(int ss)
{

}








































