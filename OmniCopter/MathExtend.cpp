#include "OmniCopter.h"

Quaternion Quaternion::constantMutiply(double s)
{
	Quaternion ans;
	ans.q[0]=this->q[0]*s;
	ans.q[1]=this->q[1]*s;
	ans.q[2]=this->q[2]*s;
	ans.q[3]=this->q[3]*s;
	return ans;
}

Quaternion Quaternion::createFromAngle(Angle angle)
{
	Quaternion ans;
	double sinRoll=sin(angle.roll/2);
	double cosRoll=cos(angle.roll/2);
	double sinPitch=sin(angle.pitch/2);
	double cosPitch=cos(angle.pitch/2);
	double sinYaw=sin(angle.yaw/2);
	double cosYaw=cos(angle.yaw/2);
	ans.q[0]=cosRoll*cosPitch*cosYaw+sinRoll*sinPitch*sinYaw;
	ans.q[1]=sinRoll*cosPitch*cosYaw-cosRoll*sinPitch*sinYaw;
	ans.q[2]=cosRoll*sinPitch*cosYaw+sinRoll*cosPitch*sinYaw;
	ans.q[3]=cosRoll*cosPitch*sinYaw-sinRoll*sinPitch*cosYaw;
	return ans;
}

Quaternion Quaternion::reverse()
{
	Quaternion ans;
	double a0=this->q[0];
	double ax=this->q[1];
	double ay=this->q[2];
	double az=this->q[3];
	double div=a0*a0+ax*ax+ay*ay+az*az;
	//div=sqrt(div);
	ans.q[0]=a0/div;
	ans.q[1]=(-ax)/div;
	ans.q[2]=(-ay)/div;
	ans.q[3]=(-az)/div;
	return ans;
}
