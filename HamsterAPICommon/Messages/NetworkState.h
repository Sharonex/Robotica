/*
 * NetworkState.h
 *
 *  Created on: Sep 19, 2016
 *      Author: ofir
 */

#ifndef INCLUDE_HAMSTERAPICOMMON_MESSAGES_NETWORKSTATE_H_
#define INCLUDE_HAMSTERAPICOMMON_MESSAGES_NETWORKSTATE_H_

#include <HamsterAPICommon/Messages/HamsterMessage.h>

namespace HamsterAPI
{
	class NetworkState : public HamsterMessage
	{
	private:
		uint32_t network_life_;

	public:
		NetworkState(uint32_t network_life=0):network_life_(network_life){}
		NetworkState(const NetworkState & network):network_life_(network.network_life_){}
		virtual ~NetworkState(){}

		uint32_t getNetworkState()const{return network_life_;}

	public:
		virtual std::string toString()const;

		friend class NetworkStateCreator;
	};

	class NetworkStateCreator
	{
	public:
		uint32_t network_life;

	public:
		NetworkState create()const;
		void setNetworkState(const NetworkState & network);
	};
}





#endif /* INCLUDE_HAMSTERAPICOMMON_MESSAGES_NETWORKSTATE_H_ */
