
#include <OmniCopter.h>
#include <Log.h>
#include <FailSafe.h>
OmniCopter omniCopter;
Log loger;
FailSafe failSafe;
int RC1[10]={1506,1506,1506,1506,1506,1506,1400};
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
	loger.setFreq(12);
	attachInterrupt(PPM_IN,InterruptService,CHANGE);
}

// The loop function is called in an endless loop
void loop()
{
	loger.showFreq(omniCopter);

	omniCopter.getCompleteInput(RC1);

	loger.showRcInput(omniCopter);
	loger.showSensor(omniCopter);



	omniCopter.attitudeProcess();


	for(int i=0;i<INNER_OUTER_RATIO;i++)
	{
		omniCopter.bodyRateProcess();
		omniCopter.positionProcess();

		omniCopter.controlAllocateProcess();

		omniCopter.excute();
	}
	failSafe.safeToArm(omniCopter);
	loger.showForce(omniCopter);
	loger.showEscOutput(omniCopter);
	loger.oneLoop();
}
