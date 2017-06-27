/*
 * Color.h
 *
 *  Created on: Sep 20, 2016
 *      Author: ofir
 */

#ifndef INCLUDE_HAMSTERAPICOMMON_COMMON_COLOR_H_
#define INCLUDE_HAMSTERAPICOMMON_COMMON_COLOR_H_

namespace HamsterAPI
{
	struct Color
	{
		unsigned char r,g,b;
		unsigned char getGray()const{ return (unsigned char)(((double)r+(double)g+(double)b)/3.0); }
		unsigned char getRed()const{ return r; }
		unsigned char getGreen()const{ return g; }
		unsigned char getBlue()const{ return b; }
		Color(unsigned char rr=0, unsigned char gg=0, unsigned char bb=0):r(rr),g(gg),b(bb){}
	};
};



#endif /* INCLUDE_HAMSTERAPICOMMON_COMMON_COLOR_H_ */
