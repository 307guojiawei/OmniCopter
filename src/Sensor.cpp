/*
 * Sensor.cpp
 *
 *  Created on: 2017年2月4日
 *      Author: jiawei
 */

#include "Omnicopter.h"

void Sensor::sensorInit()	//传感器初始化
{
	SERIALNUM.begin(DEBUG_SERIAL_RATE);
	JY901.StartIIC();
	if(Pozyx.begin()==POZYX_FAILURE)
	{
		SERIALNUM.println(F("ERROR: Unable to connect to POZYX shield"));
    SERIALNUM.println(F("Reset required"));
    delay(100);
		abort();
	}
	Pozyx.clearDevices(NULL);
	setAnchorsManual();
	delay(2000);
	SERIALNUM.println(F("Starting positioning: "));
	SERIALNUM.end();
}

void Sensor::getSensorData()	//获取传感器数据
{
	Sensor_Raw sensorData;
	JY901.GetGyro();
	JY901.GetAngle();
	JY901.GetQuater();
	sensorData.bodyAngle.roll=(double)JY901.stcAngle.Angle[0]/32768.0*180;
	sensorData.bodyAngle.pitch=(double)JY901.stcAngle.Angle[1]/32768.0*180;
	sensorData.bodyAngle.yaw=(double)JY901.stcAngle.Angle[2]/32768.0*180;
	sensorData.bodyRate.rollRate=(double)JY901.stcGyro.w[0]/32768.0*2000.0*PI/180.0;
	sensorData.bodyRate.pitchRate=(double)JY901.stcGyro.w[1]/32768.0*2000.0*PI/180.0;
	sensorData.bodyRate.yawRate=(double)JY901.stcGyro.w[2]/32768.0*2000.0*PI/180.0;
	sensorData.bodyQuaternion.q[0]=(double)JY901.stcQuater.q0/32768.0;
	sensorData.bodyQuaternion.q[1]=(double)JY901.stcQuater.q1/32768.0;
	sensorData.bodyQuaternion.q[2]=(double)JY901.stcQuater.q2/32768.0;
	sensorData.bodyQuaternion.q[3]=(double)JY901.stcQuater.q3/32768.0;
	sensorData.bodyQuaternion.q[0]=ceil(sensorData.bodyQuaternion.q[0]*config.PERCISION)/(double)config.PERCISION;
	sensorData.bodyQuaternion.q[1]=ceil(sensorData.bodyQuaternion.q[1]*config.PERCISION)/(double)config.PERCISION;
	sensorData.bodyQuaternion.q[2]=ceil(sensorData.bodyQuaternion.q[2]*config.PERCISION)/(double)config.PERCISION;
	sensorData.bodyQuaternion.q[3]=ceil(sensorData.bodyQuaternion.q[3]*config.PERCISION)/(double)config.PERCISION;
	this->sensorRaw =sensorData;
}
void Sensor::getSensorRate()
{
	JY901.GetGyro();
	this->sensorRaw.bodyRate.rollRate=(double)JY901.stcGyro.w[0]/32768.0*2000.0*PI/180.0;
	this->sensorRaw.bodyRate.pitchRate=(double)JY901.stcGyro.w[1]/32768.0*2000.0*PI/180.0;
	this->sensorRaw.bodyRate.yawRate=(double)JY901.stcGyro.w[2]/32768.0*2000.0*PI/180.0;
	this->sensorRaw.bodyRate.rollRate=ceil(this->sensorRaw.bodyRate.rollRate*config.PERCISION)/(double)config.PERCISION;
	this->sensorRaw.bodyRate.pitchRate=ceil(this->sensorRaw.bodyRate.pitchRate*config.PERCISION)/(double)config.PERCISION;
	this->sensorRaw.bodyRate.yawRate=ceil(this->sensorRaw.bodyRate.yawRate*config.PERCISION)/(double)config.PERCISION;

}

int Sensor::callPositioning()
{
	assert(&(this->sensorRaw.position)!= NULL);
  assert( (config.algorithm == POZYX_POS_ALG_UWB_ONLY ) || (config.algorithm == POZYX_POS_ALG_LS) );
  assert( (config.dimension == POZYX_3D ) || (config.dimension == POZYX_2D) || (config.dimension == POZYX_2_5D) );

	int status;

	// set dimension and algorithm
  uint8_t alg_options = (config.dimension<<4) | config.algorithm;
  status = Pozyx.regWrite(POZYX_POS_ALG, &alg_options, 1);

  // in 2.5D mode, we also supply the height
  if(config.dimension == POZYX_2_5D) {
    status = Pozyx.regWrite(POZYX_POS_Z, (uint8_t*)&config.height, sizeof(int32_t));
  }

  // trigger positioning
  uint8_t int_status = 0;
  Pozyx.regRead(POZYX_INT_STATUS, &int_status, 1);      // first clear out the interrupt status register by reading from it
  status = Pozyx.regFunction(POZYX_DO_POSITIONING, NULL, 0, NULL, 0);
  if (status != POZYX_SUCCESS )
    return POZYX_FAILURE;
}

int Sensor::readPositioning(coordinates_t *position)
{
	int status;
	uint8_t int_status = 0;
	// now wait for the positioning to finish or generate an error
	if (Pozyx.waitForFlag_safe(POZYX_INT_STATUS_POS | POZYX_INT_STATUS_ERR, 2*POZYX_DELAY_INTERRUPT, &int_status)){
		if((int_status & POZYX_INT_STATUS_ERR) == POZYX_INT_STATUS_ERR)
		{
			// An error occured during positioning.
			// Please read out the register POZYX_ERRORCODE to obtain more information about the error
			return POZYX_FAILURE;
		}else{
			status = Pozyx.getCoordinates(position);
			return POZYX_SUCCESS;
		}
	}else{
		return POZYX_TIMEOUT;
	}
}

int Sensor::getPosition()
{
	if(this->calledPositioning){
		this->positionupdate=readPositioning(&(this->sensorRaw.position));
		callPositioning();
		this->calledPositioning=1;
		return POZYX_SUCCESS;
	}
	else{
		callPositioning();
		this->calledPositioning=1;
		return POZYX_FAILURE;
	}

}


void setAnchorsManual()
{
	for(int i = 0; i < config.num_anchors; i++){
		device_coordinates_t anchor;
		anchor.network_id = config.anchors[i];
		anchor.flag = 0x1;
		anchor.pos.x = config.anchors_x[i];
		anchor.pos.y = config.anchors_y[i];
		anchor.pos.z = config.heights[i];
		Pozyx.addDevice(anchor, NULL);
	}
}
