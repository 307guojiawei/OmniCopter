/*
 * FailSafe.cpp
 *
 *  Created on: 2017年2月13日
 *      Author: jiawei
 */
#include <FailSafe.h>


void FailSafe::safeToArm(OmniCopter o)
{
	bool disArm=false;	//人为停止
	bool outOfControl=false;	//失控
	int* RC=o.RC;
	do
	{
		for(int i=0;i<6;i++)	//失控检测
		{
			if(RC[i]<800||RC[i]>2500)
			{
				outOfControl=true;
				break;
			}else
			{
				outOfControl=false;
			}
		}
		int status=RC[6];
		if(status>1800)
		{
			disArm=true;
		}else
		{
			disArm=false;
		}
		if(disArm||outOfControl)
		{
			PropData prop;
			prop.fProp[0]=0;
			prop.fProp[1]=0;
			prop.fProp[2]=0;
			prop.fProp[3]=0;
			prop.fProp[4]=0;
			prop.fProp[5]=0;
			prop.fProp[6]=0;
			prop.fProp[7]=0;
			o.escDriver.excute(prop);
			digitalWrite(LED_BUILTIN,HIGH);
		}else
		{
			digitalWrite(LED_BUILTIN,LOW);
		}
	}while(disArm||outOfControl);

}



