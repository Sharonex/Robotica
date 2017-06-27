/*
 * HeartbeatRequest.h
 *
 *  Created on: Oct 5, 2016
 *      Author: ofir
 */

#ifndef HAMSTERCOMMON_INCLUDE_HAMSTERAPICOMMON_MESSAGES_HEARTBEATREQUEST_H_
#define HAMSTERCOMMON_INCLUDE_HAMSTERAPICOMMON_MESSAGES_HEARTBEATREQUEST_H_

#include <HamsterAPICommon/Messages/HamsterMessage.h>
#include <limits>

namespace HamsterAPI
{
	class Heartbeat : public HamsterMessage
	{
	private:
		AgentID agent_;
		uint32_t connection_time_;

	public:
		Heartbeat(AgentID agent=1):agent_(agent)
		{
			static uint32_t connection_time = 0;
			connection_time_ = (++connection_time) % std::numeric_limits<uint32_t>::max();
		}
		Heartbeat(const Heartbeat & beat):agent_(beat.agent_), connection_time_(beat.connection_time_){}
		virtual ~Heartbeat(){}

		AgentID getAgentID()const{return agent_;}
		uint32_t getConnectionTime()const{return connection_time_;}

	public:
		virtual std::string toString()const;

		friend class HeartbeatCreator;
	};

	class HeartbeatCreator
	{
	public:
		AgentID agent;
		uint32_t connection_time;

	public:
		Heartbeat create()const;
		void setHeartbeat(const Heartbeat & beat);
	};
}

#endif /* HAMSTERCOMMON_INCLUDE_HAMSTERAPICOMMON_MESSAGES_HEARTBEATREQUEST_H_ */
