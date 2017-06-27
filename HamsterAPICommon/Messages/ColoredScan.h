/*
 * ColoredScan.h
 *
 *  Created on: Sep 19, 2016
 *      Author: ofir
 */

#ifndef INCLUDE_HAMSTERAPICOMMON_MESSAGES_COLOREDSCAN_H_
#define INCLUDE_HAMSTERAPICOMMON_MESSAGES_COLOREDSCAN_H_

#include <HamsterAPICommon/Messages/HamsterMessage.h>
#include <HamsterAPICommon/Messages/LidarScan.h>
#include <HamsterAPICommon/Common/Color.h>

namespace HamsterAPI
{
	class ColoredScan : public HamsterMessage
	{
	private:
		LidarScan scan_;
		std::vector<unsigned char> scan_pixels_;

	public:
		ColoredScan(){}
		ColoredScan(const ColoredScan & scan):scan_(scan.scan_),scan_pixels_(scan.scan_pixels_){}
		virtual ~ColoredScan(){}

		bool isScanInImage(int index)const;
		Color getColorForScan(int index)const;
		std::vector<Color> getColorsForScans()const;

	public:
		LidarScan getRawLidarScan()const{return scan_;}

	public:
		virtual std::string toString()const;

		friend class ColoredScanCreator;
	};

	class ColoredScanCreator
	{
	public:
		LidarScan scan;
		std::vector<unsigned char> scan_pixels;

	public:
		void resize(){scan_pixels.resize(scan.getScanSize()*4);}
		ColoredScan create()const;
		void setColoredScan(const ColoredScan & scan);
	};
}



#endif /* INCLUDE_HAMSTERAPICOMMON_MESSAGES_COLOREDSCAN_H_ */
