#include    "reg51.h"
#define FOSC 18432000L
#define T1MS ((65536)-(FOSC)/(12)/(1000))
sbit TEST_LED=P1^0;

unsigned int count;
void tm0_isr() interrupt 1 using 1
{
	TL0 = T1MS;
	TH0 = T1MS >> 8;
	if (count-- == 0)
	{
		count = 1000;
		TEST_LED = !TEST_LED;
	}
}

void main()
{
	TMOD = 0x01;
	TL0 = T1MS;
	TH0 = T1MS >> 8;
	TR0 = 1;
	ET0 = 1;
	EA = 1;
	count = 0;
	
	while(1);
}