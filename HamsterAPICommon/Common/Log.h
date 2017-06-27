/*
 * Log.h
 *
 *  Created on: Jul 14, 2016
 *      Author: ofir
 */

#ifndef LOG_H_
#define LOG_H_

#include <iostream>

namespace HamsterAPI
{
	class Log
	{
	public:
		static void i(const std::string & tag, const std::string & message)
		{
			std::cout << "[" << tag << "] " << message << std::endl;
		}

		static void i(const std::string & message)
		{
			i("info", message);
		}

		static void e(const std::string & message)
		{
			i("error", message);
		}

		static void e(std::exception e)
		{
			i("error", e.what());
		}
	};
}
#endif /* LOG_H_ */
