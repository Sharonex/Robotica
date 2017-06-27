/*
 * Goal.h
 *
 *  Created on: Jul 11, 2016
 *      Author: ofir
 */

#ifndef INCLUDE_HAMSTERAPICOMMON_MESSAGES_GOAL_H_
#define INCLUDE_HAMSTERAPICOMMON_MESSAGES_GOAL_H_

#include <HamsterAPICommon/Messages/HamsterMessage.h>

namespace HamsterAPI
{
	enum GoalType
	{
		GT_LOCAL_GOAL,
		GT_GLOBAL_GOAL
	};

	class Goal : public HamsterMessage
	{
	private:
		float x_, y_;
		float max_speed_;
		GoalType type_;

	public:
		Goal(float x=0,float y=0,float max_speed=2.0, GoalType type=GT_GLOBAL_GOAL):x_(x),y_(y),max_speed_(max_speed), type_(type){}
		Goal(const Goal & goal):x_(goal.x_),y_(goal.y_),max_speed_(goal.max_speed_), type_(goal.type_){}
		virtual ~Goal(){}

		float getX()const{return x_;}
		float getY()const{return y_;}
		float getMaxSpeed()const{return max_speed_;}
		GoalType getGoalType()const{return type_;}

	public:
		void setX(float x);
		void setY(float y);
		void setMaxSpeed(float maxSpeed);
		void setGoalType(GoalType type);

		virtual std::string toString()const;

		friend class GoalCreator;
	};

	class GoalCreator
	{
	public:
		float x,y,max_speed;
		GoalType type;

	public:
		Goal create()const;
		void setGoal(const Goal & goal);
	};
}



#endif /* INCLUDE_HAMSTERAPICOMMON_MESSAGES_GOAL_H_ */
