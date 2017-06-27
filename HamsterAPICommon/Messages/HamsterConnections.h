/*
 * HamsterConnections.h
 *
 *  Created on: Oct 5, 2016
 *      Author: ofir
 */

#ifndef HAMSTERAPICOMMON_INCLUDE_HAMSTERAPICOMMON_MESSAGES_HAMSTERCONNECTIONS_H_
#define HAMSTERAPICOMMON_INCLUDE_HAMSTERAPICOMMON_MESSAGES_HAMSTERCONNECTIONS_H_

#include <HamsterAPICommon/Messages/HamsterMessage.h>

namespace HamsterAPI
{
	class HamsterConnections : public HamsterMessage
	{
	private:
		uint32_t connected_agents_size_;
		std::vector<AgentID> connected_agents_;

	public:
		HamsterConnections():connected_agents_size_(0){}
		HamsterConnections(std::vector<AgentID> connected_agents)
		:connected_agents_(connected_agents), connected_agents_size_(connected_agents.size()){}
		HamsterConnections(const HamsterConnections & connections)
		:connected_agents_(connections.connected_agents_),connected_agents_size_(connections.connected_agents_size_){}
		virtual ~HamsterConnections(){}

		std::vector<AgentID> getConnectedAgentsIDS()const{return connected_agents_;}
		uint32_t getAmountOfConnectedAgents()const{return connected_agents_size_;}

	public:
		virtual std::string toString()const;

		friend class HamsterConnectionsCreator;
	};

	class HamsterConnectionsCreator
	{
	public:
		uint32_t connected_agents_size;
		std::vector<AgentID> connected_agents;

	public:
		inline void resize(){connected_agents.resize(connected_agents_size);}

	public:
		HamsterConnections create()const;
		void setHamsterConnections(const HamsterConnections & conections);
	};
}



#endif /* HAMSTERAPICOMMON_INCLUDE_HAMSTERAPICOMMON_MESSAGES_HAMSTERCONNECTIONS_H_ */
