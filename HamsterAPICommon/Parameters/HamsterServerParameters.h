/*
 * HamsterServerParameters.h
 *
 *  Created on: Jul 13, 2016
 *      Author: ofir
 */

#ifndef INCLUDE_HAMSTERAPICOMMON_PARAMETERS_HAMSTERSERVERPARAMETERS_H_
#define INCLUDE_HAMSTERAPICOMMON_PARAMETERS_HAMSTERSERVERPARAMETERS_H_

#include <HamsterAPICommon/Parameters/HamsterFunctionIDParams.h>
#include <HamsterAPICommon/Parameters/HamsterRosTopics.h>

namespace HamsterAPI
{
	class HamsterServerParameters
	{
	public:
		std::string base_address;
		size_t port;
		size_t agent_id;
		std::string agent_namespace;
		size_t publish_rate_;
		HamsterFunctionIDParams functions;
		HamsterRosTopics topics;

		HamsterServerParameters():base_address("127.0.0"),port(8101),agent_id(1),
								  agent_namespace("/agent1"),publish_rate_(30){}
		virtual ~HamsterServerParameters(){}

		std::string toString()const
		{
			std::stringstream output;

			output << "Base Address = " << base_address << std::endl;
			output << "Port = " << port << std::endl;
			output << "Robot ID = " << agent_id << std::endl;
			output << "Robot Namespace = " << agent_namespace << std::endl;
			output << "Publish Rate = " << publish_rate_ << std::endl;
			output << "Functions = " << functions.toString() << std::endl;
			output << "Topics = " << topics.toString() << std::endl;

			return output.str();
		}
	};
}



#endif /* INCLUDE_HAMSTERAPICOMMON_PARAMETERS_HAMSTERSERVERPARAMETERS_H_ */
