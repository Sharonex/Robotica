/*
 * LaserScan.h
 *
 *  Created on: Jul 10, 2016
 *      Author: ofir
 */

#ifndef INCLUDE_HAMSTERAPISERVER_MESSAGES_LIDARSCAN_H_
#define INCLUDE_HAMSTERAPISERVER_MESSAGES_LIDARSCAN_H_

#include <HamsterAPICommon/Messages/HamsterMessage.h>

namespace HamsterAPI
{
	class LidarScan : public HamsterMessage
	{
	private:
		float min_angle_, max_angle_, angle_increment_;
		float min_range_, max_range_;
		uint32_t scan_size_;
		std::vector<float> distances_;
		std::vector<float> intensities_;

	public:
		LidarScan();
		LidarScan(const LidarScan & lidar);
		virtual ~LidarScan(){}

	public:
		float getDistance(uint32_t index)const;
		float getIntensity(uint32_t index)const;

		virtual std::string toString()const;

	public:
		float getMinRange()const{return min_range_;}
		float getMaxRange()const{return max_range_;}
		float getMinScanAngle()const{return min_angle_;}
		float getMaxScanAngle()const{return max_angle_;}
		float getScanAngleIncrement()const{return angle_increment_;}
		uint32_t getScanSize()const{return scan_size_;}
		float * getDistances(){return distances_.data();}
		float * getIntensities(){return intensities_.data();}

		friend class LidarScanCreator;
	};

	class LidarScanCreator
	{
	public:
		float min_angle, max_angle, angle_increment;
		float min_range, max_range;
		uint32_t scan_size;
		std::vector<float> distances;
		std::vector<float> intensities;

		inline void resize(){distances.resize(scan_size);intensities.resize(scan_size);}

	public:
		void setLidarScan(const LidarScan & scan);
		LidarScan create()const;

	};
}



#endif /* INCLUDE_HAMSTERAPISERVER_MESSAGES_LIDARSCAN_H_ */
