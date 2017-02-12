
#include <OmniCopter.h>
OmniCopter omniCopter;


unsigned long loopTime=0;
unsigned long lastLoopTime=0;
int outTimer=0;
double outSum=0;
unsigned long time1=0;
//The setup function is called once at startup of the sketch
void setup()
{
	omniCopter.init();
	Serial.begin(19200);
	Serial.println("init\n");
}

// The loop function is called in an endless loop
void loop()
{
	loopTime=micros();
	outSum+=1000000.0/(double)(loopTime-lastLoopTime);
	outTimer++;
	lastLoopTime=loopTime;
	time1++;
	if(outTimer>=10)
	{
		outTimer=0;
		Serial.print(time1);
		Serial.print("Outer loop:");
		Serial.print(outSum/10.0);
		Serial.println("HZ");
		Serial.print("Inner loop:");
		Serial.print(outSum/(10.0/INNER_OUTER_RATIO));
		Serial.println("Hz");
		outSum=0;
	}



	omniCopter.getCompleteInput();

	omniCopter.attitudeProcess();
	for(int i=0;i<INNER_OUTER_RATIO;i++)
	{
		omniCopter.bodyRateProcess();
		omniCopter.positionProcess();

		omniCopter.controlAllocateProcess();

		omniCopter.excute();
	}


}
