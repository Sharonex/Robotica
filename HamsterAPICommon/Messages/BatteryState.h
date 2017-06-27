/*
 * BatteryState.h
 *
 *  Created on: Sep 19, 2016
 *      Author: ofir
 */

#ifndef INCLUDE_HAMSTERAPICOMMON_MESSAGES_BATTERYSTATE_H_
#define INCLUDE_HAMSTERAPICOMMON_MESSAGES_BATTERYSTATE_H_

#include <HamsterAPICommon/Messages/HamsterMessage.h>

namespace HamsterAPI
{
	class BatteryState : public HamsterMessage
	{
	private:
		uint32_t battery_life_;

	public:
		BatteryState(uint32_t battery_life=0):battery_life_(battery_life){}
		BatteryState(const BatteryState & battery):battery_life_(battery.battery_life_){}
		virtual ~BatteryState(){}

		uint32_t getBatteryState()const{return battery_life_;}

	public:
		virtual std::string toString()const;

		friend class BatteryStateCreator;
	};

	class BatteryStateCreator
	{
	public:
		uint32_t battery_life;

	public:
		BatteryState create()const;
		void setBatteryState(const BatteryState & battery);
	};
}



#endif /* INCLUDE_HAMSTERAPICOMMON_MESSAGES_BATTERYSTATE_H_ */
