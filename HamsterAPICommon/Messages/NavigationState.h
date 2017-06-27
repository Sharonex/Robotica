/*
 * NavigationState.h
 *
 *  Created on: Sep 19, 2016
 *      Author: ofir
 */

#ifndef INCLUDE_HAMSTERAPICOMMON_MESSAGES_NAVIGATIONSTATE_H_
#define INCLUDE_HAMSTERAPICOMMON_MESSAGES_NAVIGATIONSTATE_H_

#include <HamsterAPICommon/Messages/HamsterMessage.h>

namespace HamsterAPI
{
	enum NavigationStatus
	{
		NS_OFFLINE,
		NS_IN_PROGRESS,
		NS_REACHED_GOAL,
		NS_FAILED
	};
	class NavigationState : public HamsterMessage
	{
	private:
		NavigationStatus status_;

	public:
		static std::string statusToString(NavigationStatus status);
		static NavigationStatus stringToStatus(const std::string & str);

	public:
		NavigationState(NavigationStatus status=NS_OFFLINE):status_(status){}
		NavigationState(const NavigationState & state):status_(state.status_){}
		virtual ~NavigationState(){}

		NavigationStatus getStatus()const{return status_;}

	public:
		virtual std::string toString()const;

		void setStatus(NavigationStatus status){status_ = status;}

		friend class NavigationStateCreator;
	};

	class NavigationStateCreator
	{
	public:
		NavigationStatus status;

	public:
		NavigationState create()const;
		void setNavigationState(const NavigationState & navigation);
	};
}



#endif /* INCLUDE_HAMSTERAPICOMMON_MESSAGES_NAVIGATIONSTATE_H_ */
