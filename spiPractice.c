#include <stdio.h>
//#include <wiringPi.h>
//#include <wiringPiSPI.h>
#include <spiFunc.h>

#define BAUD_RATE 500000
#define CHANNEL 0

int main(void)
{
	int ret, value;
	/*const int WHO_AM_I = 0x68;

	printf("Setting Up SPI... \n");

	// Parameters: (int channel, int speed)
	ret = wiringPiSPISetup(CHANNEL, BAUD_RATE);

	printf("Return Value: %d\n\n", ret);

	if(ret==-1) return -1;

	//unsigned char *data = (unsigned char *) 0x0F;
	unsigned char data[10] = {0,0,0,0,0,0,0,0,0,0};
	data[0] = 0x8F;
	int length = 2;


	//int wait = 0;
	printf("Sending Data: %d \n", data[0]);
	printf("Expecting Returned: %d \n", WHO_AM_I);

	// Parameters: (int channel, unsigned char *data, int len)
	ret = wiringPiSPIDataRW(CHANNEL, data, length);
	printf("Returned Data: %d \n", ret);
	for(value = 0; value < 10; value++)
	{
		printf("Value Contained in \"data[%d]\": %d \n", value, data[value]);
	}
	delay(50);

	ret = wiringPiSPIDataRW(CHANNEL, data, length);
	printf("Returned Data: %d \n", ret);
	printf("Value Contained in \"data\": %d \n", data[0]);
*/

	setUpSPI(CHANNEL, BAUD_RATE);

	ret = XGAttached(CHANNEL);

	printf("Is the Acc/Gyro attached: %d \n", ret);

	delay(50);

	ret = MAttached(1);

	printf("Is the Mag attached: %d \n", ret);

	return 0;
}
