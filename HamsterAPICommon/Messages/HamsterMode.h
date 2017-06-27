/*
 * HamsterMode.h
 *
 *  Created on: Aug 28, 2016
 *      Author: ofir
 */

#ifndef INCLUDE_HAMSTERAPICOMMON_MESSAGES_HAMSTERMODE_H_
#define INCLUDE_HAMSTERAPICOMMON_MESSAGES_HAMSTERMODE_H_

#include <HamsterAPICommon/Messages/HamsterMessage.h>

namespace HamsterAPI
{
	enum HamsterModeType
	{
		HMT_MAPPING,
		HMT_LOCALIZATION
	};

	class HamsterMode : public HamsterMessage
	{
	private:
		HamsterModeType mode_;

	public:
		HamsterMode(const HamsterModeType & mode=HMT_MAPPING):mode_(mode){}
		HamsterMode(const HamsterMode & mode):mode_(mode.mode_){}
		virtual ~HamsterMode(){}

		HamsterModeType getMode()const{return mode_;}
		void setMode(const HamsterModeType & mode){mode_ = mode;}

	public:
		virtual std::string toString()const;

		friend class HamsterModeCreator;
	};

	class HamsterModeCreator
	{
	public:
		HamsterModeType mode_type;

	public:
		HamsterMode create()const;
		void setMode(const HamsterMode & mode);
	};
}



#endif /* INCLUDE_HAMSTERAPICOMMON_MESSAGES_HAMSTERMODE_H_ */
