/*
 * HamsterClientParameters.h
 *
 *  Created on: Jul 13, 2016
 *      Author: ofir
 */

#ifndef INCLUDE_HAMSTERAPICOMMON_PARAMETERS_HAMSTERCLIENTPARAMETERS_H_
#define INCLUDE_HAMSTERAPICOMMON_PARAMETERS_HAMSTERCLIENTPARAMETERS_H_

#include <HamsterAPICommon/Parameters/HamsterFunctionIDParams.h>

#define DEFAULT_BASE_ADDRESS "127.0.0"
#define DEFAULT_PORT 8101

namespace HamsterAPI
{
	class HamsterClientParameters
	{
	public:
		std::string base_address;
		size_t port;

		HamsterClientParameters():base_address(DEFAULT_BASE_ADDRESS),port(DEFAULT_PORT){}
		virtual ~HamsterClientParameters(){}

		std::string toString()const
		{
			std::stringstream output;

			output << "Base Address = " << base_address << std::endl;
			output << "Port = " << port << std::endl;

			return output.str();
		}
	};
}




#endif /* INCLUDE_HAMSTERAPICOMMON_PARAMETERS_HAMSTERCLIENTPARAMETERS_H_ */
