/*
 * Speed.h
 *
 *  Created on: Jul 12, 2016
 *      Author: ofir
 */

#ifndef INCLUDE_HAMSTERAPICOMMON_MESSAGES_SPEED_H_
#define INCLUDE_HAMSTERAPICOMMON_MESSAGES_SPEED_H_

#include <HamsterAPICommon/Messages/HamsterMessage.h>

namespace HamsterAPI
{
	class Speed : public HamsterMessage
	{
	private:
		float velocity_;
		float wheels_angle_;

	public:
		Speed(const Speed & speed):velocity_(speed.velocity_),wheels_angle_(speed.wheels_angle_){}
		Speed(double velocity=0, double wheels_angle=0):velocity_(velocity),wheels_angle_(wheels_angle){}
		virtual ~Speed(){}

		float getVelocity()const{return velocity_;}
		float getWheelsAngle()const{return wheels_angle_;}

	public:
		virtual std::string toString()const;

		friend class SpeedCreator;
	};

	class SpeedCreator
	{
	public:
		float velocity, wheels_angle;

	public:
		Speed create()const;
		void setSpeed(const Speed & speed);
	};
}



#endif /* INCLUDE_HAMSTERAPICOMMON_MESSAGES_SPEED_H_ */
