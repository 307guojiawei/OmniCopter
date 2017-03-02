
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
	if (digitalRead(PPM_SWITCH_PIN) == LOW)
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
}/*
void Serial1Event()
{
	while(SERIALNUM.available())
	{
		config.decode(SERIALNUM.read());
	}
}*/
//The setup function is called once at startup of the sketch
void setup()
{

	omniCopter.init();
#ifdef DEBUG_MODE
	loger.setDebugMode(true);
#endif
	loger.init();
	loger.setFreq(7);
	attachInterrupt(PPM_INT,InterruptService,CHANGE);
}

// The loop function is called in an endless loop
void loop()
{
#ifdef DEBUG_MODE
	loger.showFreq(omniCopter);
#endif

	omniCopter.getCompleteInput(RC1);
	omniCopter.getAngle(omniCopter.lastAngle);

#ifdef DEBUG_MODE
	loger.showRcInput(omniCopter);
	loger.showSensor(omniCopter);
#endif


//	omniCopter.desiredBodyRate.rollRate=0;
//	omniCopter.desiredBodyRate.pitchRate=0;
//	omniCopter.desiredBodyRate.yawRate=0;
	omniCopter.attitudeProcess();


	for (int i=0; i <= config.INNER_OUTER_RATIO; i++) {
    if (i == config.INNER_OUTER_RATIO) {
      omniCopter.cleanAngleErrorCollection();
    } else {
      omniCopter.collectAngleError();
    }

		omniCopter.bodyRateProcess();
		omniCopter.positionProcess();

		omniCopter.controlAllocateProcess();

		omniCopter.excute();
	}

	failSafe.safeToArm(omniCopter);

#ifdef DEBUG_MODE
	loger.showForce(omniCopter);
	loger.showEscOutput(omniCopter);
	loger.oneLoop();
#endif
}
