/*
 * HandshakeResponseInfo.h
 *
 *  Created on: Jul 14, 2016
 *      Author: ofir
 */

#ifndef INCLUDE_HAMSTERAPICOMMON_MESSAGES_HANDSHAKERESPONSEINFO_H_
#define INCLUDE_HAMSTERAPICOMMON_MESSAGES_HANDSHAKERESPONSEINFO_H_

#include <HamsterAPICommon/Messages/HamsterMessage.h>
#include <HamsterAPICommon/Parameters/HamsterClientParameters.h>
#include <HamsterAPICommon/Common/Version.h>

namespace HamsterAPI
{
	enum HandshakeResponse
	{
		HSR_DIFFERENT_AGENT_ID,
		HSR_FAILURE_DIFFERENT_VERSIONS,
		HSR_SUCCESS,
		HSR_UNKNOWN_FAILURE
	};

	class HandshakeResponseInfo : public HamsterMessage
	{
	private:
		HamsterFunctionIDParams params_;
		Version server_version_;
		HandshakeResponse response_;

	public:
		HandshakeResponseInfo(const HamsterFunctionIDParams & params=HamsterFunctionIDParams(),
				Version server_version=Version(),HandshakeResponse response = HSR_SUCCESS)
				:params_(params),server_version_(server_version),response_(response){}
		HandshakeResponseInfo(const HandshakeResponseInfo & response):params_(response.params_),response_(response.response_){}
		virtual ~HandshakeResponseInfo(){}

		HamsterFunctionIDParams getClientParam()const{return params_;}
		HandshakeResponse getResponse()const{return response_;}
		Version getServerVersion()const{return server_version_;}

	public:
		virtual std::string toString()const;

		void setClientParams(const HamsterFunctionIDParams & params){params_ = params;}
		void setResponse(HandshakeResponse response){response_ = response;}
		void setServerVersion(const Version & version){server_version_ = version;}

		friend class HandshakeResponsetInfoCreator;
	};

	class HandshakeResponsetInfoCreator
	{
	public:
		HamsterFunctionIDParams params;
		uint8_t major, semi, minor;
		HandshakeResponse response;

	public:
		HandshakeResponseInfo create()const;
		void setHandshakeResponseInfo(const HandshakeResponseInfo & response);
	};
}




#endif /* INCLUDE_HAMSTERAPICOMMON_MESSAGES_HANDSHAKERESPONSEINFO_H_ */
