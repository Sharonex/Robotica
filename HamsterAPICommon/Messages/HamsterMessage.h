/*
 * HamsterMessage.h
 *
 *  Created on: Jul 11, 2016
 *      Author: ofir
 */

#ifndef INCLUDE_HAMSTERAPICOMMON_MESSAGES_HAMSTERMESSAGE_H_
#define INCLUDE_HAMSTERAPICOMMON_MESSAGES_HAMSTERMESSAGE_H_

#include <string>
#include <vector>
#include <sstream>
#include <HamsterAPICommon/HamsterCommon.h>

namespace HamsterAPI
{
	class HamsterMessage
	{
	public:
		HamsterMessage(){}
		virtual ~HamsterMessage(){}

		virtual std::string toString()const=0;
	};
}



#endif /* INCLUDE_HAMSTERAPICOMMON_MESSAGES_HAMSTERMESSAGE_H_ */
