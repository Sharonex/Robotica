/*
 * Pose.h
 *
 *  Created on: Jul 11, 2016
 *      Author: ofir
 */

#ifndef INCLUDE_HAMSTERAPICOMMON_MESSAGES_POSE_H_
#define INCLUDE_HAMSTERAPICOMMON_MESSAGES_POSE_H_

#include <HamsterAPICommon/Messages/HamsterMessage.h>

namespace HamsterAPI
{
	class Pose : public HamsterMessage
	{
	private:
		float x_, y_;
		float heading_;

	public:
		Pose(float x=0, float y=0, float heading=0):x_(x),y_(y),heading_(heading){}
		Pose(const Pose & pose):x_(pose.x_),y_(pose.y_),heading_(pose.heading_){}
		virtual ~Pose(){}

		float getX()const{return x_;}
		float getY()const{return y_;}
		float getHeading()const{return heading_;}

		void setX(float x){x_ = x;}
		void setY(float y){y_ = y;}
		void setHeading(float heading){heading_ = heading;}
	public:
		virtual std::string toString()const;

		friend class PoseCreator;
	};

	class PoseCreator
	{
	public:
		float x,y,heading;

	public:
		Pose create()const;
		void setPose(const Pose & pose);
	};
}



#endif /* INCLUDE_HAMSTERAPICOMMON_MESSAGES_POSE_H_ */
