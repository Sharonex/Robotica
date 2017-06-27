/*
 * HamsterError.h
 *
 *  Created on: Jul 11, 2016
 *      Author: ofir
 */

#ifndef INCLUDE_HAMSTERAPICOMMON_COMMON_HAMSTERERROR_H_
#define INCLUDE_HAMSTERAPICOMMON_COMMON_HAMSTERERROR_H_

#include <HamsterAPICommon/Common/HamsterErrorCodes.h>

namespace HamsterAPI
{
	class HamsterError
	{
	private:
		int error_code_;
		std::string error_;

	public:
		HamsterError(int error_code, const std::string & error = ""):error_code_(error_code),error_(error)
		{if(error_code != ERROR_CODE_MESSAGE_CUSTOM)error_ = errorCodeToString(error_code);}
		virtual ~HamsterError(){}

		std::string what()const{return error_;}
		int error()const{return error_code_;}

		bool operator()()const{return error_code_ != ERROR_CODE_NONE;}
	};
}

#endif /* INCLUDE_HAMSTERAPICOMMON_COMMON_HAMSTERERROR_H_ */
