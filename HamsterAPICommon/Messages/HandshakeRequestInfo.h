/*
 * HandshakeRequestInfo.h
 *
 *  Created on: Jul 14, 2016
 *      Author: ofir
 */

#ifndef INCLUDE_HAMSTERAPICOMMON_MESSAGES_HANDSHAKEREQUESTINFO_H_
#define INCLUDE_HAMSTERAPICOMMON_MESSAGES_HANDSHAKEREQUESTINFO_H_

#include <HamsterAPICommon/Messages/HamsterMessage.h>
#include <HamsterAPICommon/Common/Version.h>

namespace HamsterAPI
{
	class HandshakeRequestInfo : public HamsterMessage
	{
	private:
		AgentID agent_id_;
		Version client_version_;

	public:
		HandshakeRequestInfo(AgentID agent_id=1, Version client_version=Version()):agent_id_(agent_id){}
		HandshakeRequestInfo(const HandshakeRequestInfo & request):agent_id_(request.agent_id_),client_version_(request.client_version_){}
		virtual ~HandshakeRequestInfo(){}

		AgentID getAgentID()const{return agent_id_;}
		Version getClientVersion()const{return client_version_;}

	public:
		virtual std::string toString()const;

		void setAgentID(const AgentID & agent){agent_id_ = agent;}
		void setVersion(const Version & version){client_version_ = version;}

		friend class HandshakeRequestInfoCreator;
	};

	class HandshakeRequestInfoCreator
	{
	public:
		AgentID agent_id;
		uint8_t major, semi, minor;

	public:
		HandshakeRequestInfo create()const;
		void setHandshakeRequestInfo(const HandshakeRequestInfo & request);
	};
}




#endif /* INCLUDE_HAMSTERAPICOMMON_MESSAGES_HANDSHAKEREQUESTINFO_H_ */
