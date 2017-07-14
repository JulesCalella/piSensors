#include <stdio.h>
#include <spiFunc.h>
#include <wiringPi.h>
#include <wiringPiSPI.h>

#define READ 0x80
#define WRITE 0x7F

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

/************************************************************************************
void initializeXGM(int ssAG, int ssM)
	Inititalizes all the registers with proper defaults. Necessary to use
	magnetometer with SPI.
************************************************************************************/
void initializeXGM(int ssAG, int ssM)
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

	// CTRL_REG2_M (21h) - 0000 0000
	data[0] = 0x21;
	data[1] = 0x00;

	// CTRL_REG3_M (22h) - 1000 0100
	data[0] = 0x22;
	data[1] = 0x84;

	// CTRL_REG4_M (23h) - 0000 1000
	data[0] = 0x23;
	data[1] = 0x08;

	// CTRL_REG5_M (24h) - 0000 0000
	data[0] = 0x24;
	data[1] = 0x00;
}


/************************************************************************************
int readAccZ(int ss)
	Reads the data on the Z axis of the Accelerometer.
************************************************************************************/
int readAccZ(int ss)
{
	signed int AccelerometerZ;

	// Read first Byte
	data[0] = (READ | 0x2C);
	data[1] = 0;

	wiringPiSPIDataRW(ss, data, 2);

	// Store value
	AccelerometerZ = data[1];

	// Read second Byte
	data[0] = (READ | 0x2D);
	data[1] = 0;

	wiringPiSPIDataRW(ss, data, 2);

	// Shift new data left 8 bits, OR with previous data
	AccelerometerZ = AccelerometerZ | (data[1] << 8);

	return AccelerometerZ;
}

/************************************************************************************
int readAccY(int ss)
	Reads the data on the Y axis of the accelerometer.	
/************************************************************************************
int readAccY(int ss)
{
	signed int AccelerometerY;

	// Read first Byte
	data[0] = (READ | 0x2A);
	data[1] = 0;

	wiringPiSPIDataRW(ss, data, 2);

	// Store value
	AccelerometerY = data[1];

	// Read second Byte
	data[0] = (READ | 0x2B);
	data[1] = 0;

	wiringPiSPIDataRW(ss, data, 2);

	// Shift new data left 8 bits, OR with previous data
	AccelerometerY = AccelerometerY | (data[1] << 8);

	return AccelerometerY;
}

/************************************************************************************
int readAccX(int ss)
	Reads the data on the X axis of the accelerometer.
************************************************************************************/
int readAccX(int ss)
{
	signed int AccelerometerX;

	// Read first Byte
	data[0] = (READ | 0x28);
	data[1] = 0;

	wiringPiSPIDataRW(ss, data, 2);

	// Store value
	AccelerometerX = data[1];

	// Read second Byte
	data[0] = (READ | 0x29);
	data[1] = 0;

	wiringPiSPIDataRW(ss, data, 2);

	// Shift new data left 8 bits, OR with previous data
	AccelerometerX = AccelerometerX | (data[1] << 8);

	return AccelerometerX;
}

/************************************************************************************
int readGyroZ(int ss)
	Reads the data on the Z axis of the gyroscope.
************************************************************************************/
int readGyroZ(int ss)
{
	signed int GyroscopeZ;

	// Read first Byte
	data[0] = (READ | 0x1C);
	data[1] = 0;

	wiringPiSPIDataRW(ss, data, 2);

	// Store value
	GyroscopeZ = data[1];

	// Read second Byte
	data[0] = (READ | 0x1D);
	data[1] = 0;

	wiringPiSPIDataRW(ss, data, 2);

	// Shift new data left 8 bits, OR with previous data
	GyroscopeZ = GyroscopeZ | (data[1] << 8);

	return GyroscopeZ;
}

/************************************************************************************
int readGyroY(int ss)
	Reads the data on the Y axis of the gyroscope.
************************************************************************************/
int readGyroY(int ss)
{
	signed int GyroscopeY;

	// Read first Byte
	data[0] = (READ | 0x1A);
	data[1] = 0;

	wiringPiSPIDataRW(ss, data, 2);

	// Store value
	GyroscopeY = data[1];

	// Read second Byte
	data[0] = (READ | 0x1B);
	data[1] = 0;

	wiringPiSPIDataRW(ss, data, 2);

	// Shift new data left 8 bits, OR with previous data
	GyroscopeY = GyroscopeY | (data[1] << 8);

	return GyroscopeY;
}

/************************************************************************************
int readGyroX(int ss)
	Reads the data on the X axis of the gyroscope.
************************************************************************************/
int readGyroX(int ss)
{
	signed int GyroscopeX;

	// Read first Byte
	data[0] = (READ | 0x18);
	data[1] = 0;

	wiringPiSPIDataRW(ss, data, 2);

	// Store value
	GyroscopeX = data[1];

	// Read second Byte
	data[0] = (READ | 0x19);
	data[1] = 0;

	wiringPiSPIDataRW(ss, data, 2);

	// Shift new data left 8 bits, OR with previous data
	GyroscopeX = GyroscopeX | (data[1] << 8);

	return GyroscopeX;
}

/************************************************************************************
int readMagZ(int ss)
	Reads the data on the Z axis the magnetometer.
************************************************************************************/
int readMagZ(int ss)
{
	signed int MagnetometerZ;

	// Read first Byte
	data[0] = (READ | 0x2C);
	data[1] = 0;

	wiringPiSPIDataRW(ss, data, 2);

	// Store value
	MagnetometerZ = data[1];

	// Read second Byte
	data[0] = (READ | 0x2D);
	data[1] = 0;

	wiringPiSPIDataRW(ss, data, 2);

	// Shift new data left 8 bits, OR with previous data
	MagnetometerZ = MagnetometerZ | (data[1] << 8);

	return MagnetometerZ;
}

/************************************************************************************
int readMagY(int ss)
	Reads the data on the Y axis the magnetometer.
************************************************************************************/
int readMagY(int ss)
{
	signed int MagnetometerY;

	// Read first Byte
	data[0] = (READ | 0x2A);
	data[1] = 0;

	wiringPiSPIDataRW(ss, data, 2);

	// Store value
	MagnetometerY = data[1];

	// Read second Byte
	data[0] = (READ | 0x2B);
	data[1] = 0;

	wiringPiSPIDataRW(ss, data, 2);

	// Shift new data left 8 bits, OR with previous data
	MagnetometerY = MagnetometerY | (data[1] << 8);

	return MagnetometerY;
}

/************************************************************************************
int readMagX(int ss)
	Reads the data on the Z axis the magnetometer.
************************************************************************************/
int readMagX(int ss)
{
	signed int MagnetometerX;

	// Read first Byte
	data[0] = (READ | 0x28);
	data[1] = 0;

	wiringPiSPIDataRW(ss, data, 2);

	// Store value
	MagnetometerX = data[1];

	// Read second Byte
	data[0] = (READ | 0x29);
	data[1] = 0;

	wiringPiSPIDataRW(ss, data, 2);

	// Shift new data left 8 bits, OR with previous data
	MagnetometerX = MagnetometerX | (data[1] << 8);

	return MagnetometerX;
}

/************************************************************************************
void unitValues(int ssAG, int ssM)
	Prints the units for the three sensors.
************************************************************************************/
void unitValues(int ssAG, int ssM)
{
	int selection;

	// Read accelerometer units
	data[0] = (READ | 0x20);
	data[1] = 0x00;
	selection = wiringPiSPIDataRW(ssAG, data, 2);

	switch(selection & 0x18)
	{
		case 0x00:
			printf("Accelerometer: +-2g\n");
			break;

		case 0x08:
			printf("Accelerometer: +-16g\n");
			break;

		case 0x10:
			printf("Accelerometer: +-4g\n");
			break;

		case 0x18:
			printf("Accelerometer: +-8g\n");
			break;

		default:
			printf("Error gathering accelerometer data...\n");
			break;
	}

	// Read gyroscope units
	data[0] = (READ | 0x10);
	data[1] = 0x00;
	selection = wiringPiSPIDataRW(ssAG, data, 2);

	switch(selection & 0x18)
	{
		case 0x00:
			printf("Gyroscope: 245dps\n");
			break;

		case 0x08:
			printf("Gyroscope: 500dps\n");
			break;

		case 0x18:
			printf("Gyroscope: 2000dps\n");
			break;

		default:
			printf("Error gathering gyroscope data...\n");
			break;
	}

	// Read magnetometer units
	data[0] = (READ | 0x21);
	data[1] = 0x00;
	selection = wiringPiSPIDataRW(ssM, data, 2);

	switch(selection & 0x60)
	{
		case 0x00:
			printf("Magnetometer: +-4 gauss\n");
			break;

		case 0x20:
			printf("Magnetometer: +-8 gauss\n");
			break;

		case 0x40:
			printf("Magnetometer: +-12 gauss\n");
			break;

		case 0x60:
			printf("Magnetometer: +-16 gauss\n");
			break;

		default:
			printf("Error gathering magnetometer data...\n");
			break;
	}
	
}




































