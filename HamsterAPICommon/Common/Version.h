/*
 * Version.h
 *
 *  Created on: Sep 25, 2016
 *      Author: ofir
 */

#ifndef HAMSTERAPICOMMON_INCLUDE_HAMSTERAPICOMMON_COMMON_VERSION_H_
#define HAMSTERAPICOMMON_INCLUDE_HAMSTERAPICOMMON_COMMON_VERSION_H_

#include <boost/algorithm/string.hpp>
#include <HamsterAPICommon/Common/HamsterError.h>
#include <vector>
#include <boost/lexical_cast.hpp>

namespace HamsterAPI
{
	class Version
	{
	private:
		uint8_t major_, semi_, minor_;

	public:
		Version(uint8_t major=0, uint8_t semi=0, uint8_t minor=0):major_(major),semi_(semi),minor_(minor){}
		Version(const std::string & version){setVersion(version);}
		virtual ~Version(){}

		uint8_t getMajorVersion()const{return major_;}
		uint8_t getSemiMinorVersion()const{return semi_;}
		uint8_t getMinorVersion()const{return minor_;}
		std::string toString()const;

	public:
		void setMajorVersion(uint8_t major){major_ = major;}
		void setSemiMinorVersion(uint8_t semi){semi_ = semi;}
		void setMinorVersion(uint8_t minor){minor_ = minor;}
		void setVersion(const std::string & version);

	public:
		bool operator==(const Version & v)const;
		bool operator!=(const Version & v)const;
		bool operator<(const Version & v)const;
		bool operator<=(const Version & v)const;
		bool operator>(const Version & v)const;
		bool operator>=(const Version & v)const;
	};
}



#endif /* HAMSTERAPICOMMON_INCLUDE_HAMSTERAPICOMMON_COMMON_VERSION_H_ */
