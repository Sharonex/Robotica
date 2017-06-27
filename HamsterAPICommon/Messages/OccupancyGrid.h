/*
 * OccupancyGrid.h
 *
 *  Created on: Jul 20, 2016
 *      Author: ofir
 */

#ifndef INCLUDE_HAMSTERAPICOMMON_MESSAGES_OCCUPANCYGRID_H_
#define INCLUDE_HAMSTERAPICOMMON_MESSAGES_OCCUPANCYGRID_H_

#include <HamsterAPICommon/Messages/HamsterMessage.h>

namespace HamsterAPI
{
	enum Cell
	{
		CELL_FREE,
		CELL_OCCUPIED,
		CELL_UNKNOWN
	};
	class OccupancyGrid : public HamsterMessage
	{
	private:
		uint32_t w_, h_;
		double resolution_;
		std::vector<unsigned char> grid_;

	private:
		inline uint32_t getIndex(uint32_t x,uint32_t y)const{return y*w_ + x;}

	public:
		OccupancyGrid(uint32_t width=0,uint32_t height=0, double resolution=1):w_(width),h_(height),resolution_(resolution),grid_(w_*h_,'2'){}
		OccupancyGrid(const OccupancyGrid & other):w_(other.w_),h_(other.h_),resolution_(other.resolution_),grid_(other.grid_){}
		virtual ~OccupancyGrid(){}

		uint32_t getWidth()const{return w_;}
		uint32_t getHeight()const{return h_;}
		double getResolution()const{return resolution_;}
		Cell getCell(uint32_t x, uint32_t y)const;
		unsigned char * getRawData(){return grid_.data();}

		void setCell(uint32_t x, uint32_t y, Cell c);

		virtual std::string toString()const;

		friend class OccupancyGridCreator;
	};

	class OccupancyGridCreator
	{
	public:
		uint32_t w, h;
		double resolution;
		std::vector<unsigned char> grid;

	public:
		void resize(){grid.resize(w*h);}

	public:
		void setOccupancyGrid(const OccupancyGrid & grid);
		OccupancyGrid create()const;
	};
}



#endif /* INCLUDE_HAMSTERAPICOMMON_MESSAGES_OCCUPANCYGRID_H_ */
