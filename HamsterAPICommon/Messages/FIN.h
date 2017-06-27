/*
 * FIN.h
 *
 *  Created on: Sep 27, 2016
 *      Author: ofir
 */

#ifndef HAMSTERAPICOMMON_INCLUDE_HAMSTERAPICOMMON_MESSAGES_FIN_H_
#define HAMSTERAPICOMMON_INCLUDE_HAMSTERAPICOMMON_MESSAGES_FIN_H_

#include <HamsterAPICommon/Messages/HamsterMessage.h>

namespace HamsterAPI
{
	class FIN : public HamsterMessage
	{
	private:
		AgentID agent_;

	public:
		FIN(const AgentID & agent=0):agent_(agent){}
		FIN(const FIN & fin):agent_(fin.agent_){}
		virtual ~FIN(){}

		AgentID getAgentID()const{return agent_;}

	public:
		virtual std::string toString()const;

		friend class FINCreator;
	};

	class FINCreator
	{
	public:
		AgentID agent;

	public:
		FIN create()const;
		void setFIN(const FIN & fin);
	};
}



#endif /* HAMSTERAPICOMMON_INCLUDE_HAMSTERAPICOMMON_MESSAGES_FIN_H_ */
