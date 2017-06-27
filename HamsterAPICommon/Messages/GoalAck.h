/*
 * GoalAck.h
 *
 *  Created on: Sep 27, 2016
 *      Author: ofir
 */

#ifndef SUBPROJECTS__HAMSTERCOMMON_INCLUDE_HAMSTERAPICOMMON_MESSAGES_GOALACK_H_
#define SUBPROJECTS__HAMSTERCOMMON_INCLUDE_HAMSTERAPICOMMON_MESSAGES_GOALACK_H_

#include <HamsterAPICommon/Messages/HamsterMessage.h>

namespace HamsterAPI
{
	enum GoalAckType
	{
		GAT_SENT_SUCCESSFULY,
		GAT_FAILURE
	};
	class GoalAck : public HamsterMessage
	{
	private:
		GoalAckType ack_;

	public:
		GoalAck(GoalAckType ack = GAT_SENT_SUCCESSFULY):ack_(ack){}
		GoalAck(const GoalAck & goal_ack):ack_(goal_ack.ack_){}
		virtual ~GoalAck(){}

		GoalAckType getGoalAck()const{return ack_;}

	public:
		void setGoalAck(GoalAckType ack);

		virtual std::string toString()const;

		friend class GoalAckCreator;
	};

	class GoalAckCreator
	{
	public:
		GoalAckType ack;

	public:
		GoalAck create()const;
		void setGoalAck(const GoalAck & goal_ack);
	};
}



#endif /* SUBPROJECTS__HAMSTERCOMMON_INCLUDE_HAMSTERAPICOMMON_MESSAGES_GOALACK_H_ */
