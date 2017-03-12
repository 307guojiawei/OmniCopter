/*
 * Sensor.cpp
 *
 *  Created on: 2017年2月4日
 *      Author: jiawei
 */

#include "Omnicopter.h"

kalman_state kalman_state_0;
kalman_state kalman_state_1;
kalman_state kalman_state_2;

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
	this->setAnchorsManual();
	delay(2000);

	// set dimension and algorithm
	uint8_t alg_options = (config.dimension<<4) | config.algorithm;
	Pozyx.regWrite(POZYX_POS_ALG, &alg_options, 1);

	//SERIALNUM.println(F("Starting positioning: "));
	SERIALNUM.end();

	kalman_init(&kalman_state_0, 0.0, 0.0);
	kalman_init(&kalman_state_1, 0.0, 0.0);
	kalman_init(&kalman_state_2, 0.0, 0.0);
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
/*
	assert(&(this->sensorRaw.position)!= NULL);
  assert( (config.algorithm == POZYX_POS_ALG_UWB_ONLY ) || (config.algorithm == POZYX_POS_ALG_LS) );
  assert( (config.dimension == POZYX_3D ) || (config.dimension == POZYX_2D) || (config.dimension == POZYX_2_5D) );
*/
	int status;

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
	/*static int cur =0;
	static int  pos_x_list[POS_FLITER_NUM]={0};
	static int  pos_y_list[POS_FLITER_NUM]={0};
	static int  pos_z_list[POS_FLITER_NUM]={0};
*/
	if(this->calledPositioning){

		this->positionupdate=readPositioning(&(this->sensorRaw.position));

		this->sensorRaw.position.x=kalman_filter(&kalman_state_0,this->sensorRaw.position.x);
		this->sensorRaw.position.y=kalman_filter(&kalman_state_1,this->sensorRaw.position.y);
		this->sensorRaw.position.z=kalman_filter(&kalman_state_2,this->sensorRaw.position.z);

/*
		{
			pos_x_list[cur]=this->sensorRaw.position.x;
			pos_y_list[cur]=this->sensorRaw.position.y;
			pos_z_list[cur]=this->sensorRaw.position.z;
			cur++;
			if(cur==POS_FLITER_NUM)cur=0;
			this->sensorRaw.position.x=average(pos_x_list,POS_FLITER_NUM);
			this->sensorRaw.position.y=average(pos_y_list,POS_FLITER_NUM);
			this->sensorRaw.position.z=average(pos_z_list,POS_FLITER_NUM);
		}
*/
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


void Sensor::setAnchorsManual()
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

void Sensor::setPosInit(){
	this->pos_init[0]=this->sensorRaw.position.x;
	this->pos_init[1]=this->sensorRaw.position.y;
	this->pos_init[2]=this->sensorRaw.position.z;
}

double average(int * list,int num){
	double sum=0;
	for(int i=0;i<num;i++){
		sum+=*(list+i);
	}
	sum=(sum*1.0/num);
	return sum;
}

void kalman_init(kalman_state *state,float init_x,  float init_p)
{
    state->x = init_x;
    state->p = init_p;
    state->A = 1;
    state->H = 1;
    state->q = 5;//10e-6;  /* predict noise convariance */
    state->r = 120;//10e-5;  /* measure error convariance */
}

float kalman_filter(kalman_state *state, float z_measure)
{
    /* Predict */
    state->x = state->A * state->x;
    state->p = state->A * state->A * state->p + state->q;  /* p(n|n-1)=A^2*p(n-1|n-1)+q */

    /* Measurement */
    state->gain = state->p * state->H / (state->p * state->H * state->H + state->r);
    state->x = state->x + state->gain * (z_measure - state->H * state->x);
    state->p = (1 - state->gain * state->H) * state->p;

    return state->x;
}
