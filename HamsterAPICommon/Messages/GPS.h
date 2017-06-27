/*
 * GPS.h
 *
 *  Created on: Jul 11, 2016
 *      Author: ofir
 */

#ifndef INCLUDE_HAMSTERAPICOMMON_MESSAGES_GPS_H_
#define INCLUDE_HAMSTERAPICOMMON_MESSAGES_GPS_H_

#include <HamsterAPICommon/Messages/HamsterMessage.h>

namespace HamsterAPI
{
	class GPS : public HamsterMessage
	{
	private:
		float lat_, lon_, alt_;

	public:
		GPS(float lat=0, float lon=0, float alt=0):lat_(lat),lon_(lon),alt_(alt){}
		GPS(const GPS & gps):lat_(gps.lat_),lon_(gps.lon_),alt_(gps.alt_){}
		virtual ~GPS(){}

		float getLatitude()const{return lat_;}
		float getLongitude()const{return lon_;}
		float getAltitude()const{return alt_;}

	public:
		virtual std::string toString()const;

		friend class GPSCreator;
	};

	class GPSCreator
	{
	public:
		float lat, lon, alt;

	public:
		GPS create()const;
		void setGPS(const GPS & gps);
	};
}



#endif /* INCLUDE_HAMSTERAPICOMMON_MESSAGES_GPS_H_ */
