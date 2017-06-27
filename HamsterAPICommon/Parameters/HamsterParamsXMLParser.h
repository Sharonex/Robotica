/*
 * HamsterParamsXMLParser.h
 *
 *  Created on: Jul 13, 2016
 *      Author: ofir
 */

#ifndef INCLUDE_HAMSTERAPICOMMON_PARAMETERS_HAMSTERPARAMSXMLPARSER_H_
#define INCLUDE_HAMSTERAPICOMMON_PARAMETERS_HAMSTERPARAMSXMLPARSER_H_

#include <HamsterAPICommon/Parameters/HamsterClientParameters.h>
#include <HamsterAPICommon/Parameters/HamsterServerParameters.h>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/lexical_cast.hpp>
#include <HamsterAPICommon/Common/Log.h>

namespace HamsterAPI
{
	class HamsterParamsXMLParser
	{
		typedef boost::property_tree::ptree XMLTree;
	private:
		template <class T>
		T get(const std::string & name, const XMLTree & tree, const T & def_val)const
		{
			try
			{
				T t = boost::lexical_cast<T>(tree.get_child(name).data());
				return t;
			}
			catch(...)
			{
				return def_val;
			}
		}

		HamsterFunctionIDParams parseFunctions(const XMLTree & tree)const;
		HamsterRosTopics parseTopics(const XMLTree & tree, const std::string & ns)const;
		HamsterGlobalTopics parseGlobalTopics(const XMLTree & tree)const;
		HamsterAgentTopics parseAgentTopics(const XMLTree & tree, const std::string & ns)const;

	public:
		HamsterClientParameters parseClientParams(const std::string & file)const;
		HamsterServerParameters parseServerParams(const std::string & file)const;
	};
}



#endif /* INCLUDE_HAMSTERAPICOMMON_PARAMETERS_HAMSTERPARAMSXMLPARSER_H_ */
