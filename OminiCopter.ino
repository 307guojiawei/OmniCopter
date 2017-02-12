
#include <OmniCopter.h>
#include <Log.h>
OmniCopter omniCopter;
Log loger;
int RC1[10];
void InterruptService()
{
	static unsigned long int lastTime=0;
	static int cursor=0;
	if(digitalRead(2)==0)
	{
		unsigned long int now=micros();
		unsigned long int thisTime=now-lastTime;
		if(thisTime>3000)
		{
			cursor=0;
		}else
		{
			RC1[cursor++]=thisTime;
		}
		lastTime=now;
	}
}

//The setup function is called once at startup of the sketch
void setup()
{

	omniCopter.init();
#ifdef DEBUG_MODE
	loger.setDebugMode(true);
#endif
	loger.init();
	loger.setFreq(10);
	attachInterrupt(PPM_IN,InterruptService,CHANGE);
}

// The loop function is called in an endless loop
void loop()
{
	loger.showFreq(omniCopter);

	omniCopter.getRcValue(RC1);
	omniCopter.getCompleteInput();

	loger.showRcInput(omniCopter);

	omniCopter.attitudeProcess();
	for(int i=0;i<INNER_OUTER_RATIO;i++)
	{
		omniCopter.bodyRateProcess();
		omniCopter.positionProcess();

		omniCopter.controlAllocateProcess();

		omniCopter.excute();
	}

	loger.oneLoop();
}
