/*
 * GoalCommand.h
 *
 *  Created on: Sep 27, 2016
 *      Author: ofir
 */

#ifndef SUBPROJECTS__HAMSTERCOMMON_INCLUDE_HAMSTERAPICOMMON_MESSAGES_GOALCOMMAND_H_
#define SUBPROJECTS__HAMSTERCOMMON_INCLUDE_HAMSTERAPICOMMON_MESSAGES_GOALCOMMAND_H_

#include <HamsterAPICommon/Messages/HamsterMessage.h>
#include <HamsterAPICommon/Messages/Goal.h>

namespace HamsterAPI
{
	enum GoalCommandType
	{
		GCT_START_GOAL,
		GCT_STOP_GOAL
	};
	class GoalCommand : public HamsterMessage
	{
	private:
		Goal goal_;
		GoalCommandType command_;

	public:
		GoalCommand(const Goal & goal=Goal(), GoalCommandType command=GCT_START_GOAL):goal_(goal), command_(command){}
		GoalCommand(const GoalCommand & goal_cmd):goal_(goal_cmd.goal_),command_(goal_cmd.command_){}
		virtual ~GoalCommand(){}

		Goal getGoal()const{return goal_;}
		GoalCommandType getGoalCommand()const{return command_;}

	public:
		void setGoal(const Goal & goal);
		void setGoalCommand(const GoalCommandType & command);

		virtual std::string toString()const;

		friend class GoalCommandCreator;
	};

	class GoalCommandCreator
	{
	public:
		float x,y,max_speed;
		GoalType type;
		GoalCommandType command;

	public:
		GoalCommand create()const;
		void setGoalCommand(const GoalCommand & goal_cmd);
	};
}




#endif /* SUBPROJECTS__HAMSTERCOMMON_INCLUDE_HAMSTERAPICOMMON_MESSAGES_GOALCOMMAND_H_ */
