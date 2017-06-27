/*
 * IMU.h
 *
 *  Created on: Jul 11, 2016
 *      Author: ofir
 */

#ifndef INCLUDE_HAMSTERAPICOMMON_MESSAGES_IMU_H_
#define INCLUDE_HAMSTERAPICOMMON_MESSAGES_IMU_H_

#include <HamsterAPICommon/Messages/HamsterMessage.h>

namespace HamsterAPI
{
	class IMU : public HamsterMessage
	{
	private:
		double roll_, pitch_, yaw_;

	public:
		IMU(double roll=0,double pitch=0,double yaw=0):roll_(roll),pitch_(pitch),yaw_(yaw){}
		IMU(const IMU & imu):roll_(imu.roll_),pitch_(imu.pitch_),yaw_(imu.yaw_){}
		virtual ~IMU(){}

		double getRoll()const{return roll_;}
		double getPitch()const{return pitch_;}
		double getYaw()const{return yaw_;}

	public:
		virtual std::string toString()const;

		friend class IMUCreator;
	};

	class IMUCreator
	{
	public:
		double roll,pitch,yaw;

	public:
		IMU create()const;
		void setIMU(const IMU & imu);
	};
}



#endif /* INCLUDE_HAMSTERAPICOMMON_MESSAGES_IMU_H_ */
