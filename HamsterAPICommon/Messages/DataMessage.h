/*
 * TextMessage.h
 *
 *  Created on: Jul 12, 2016
 *      Author: ofir
 */

#ifndef INCLUDE_HAMSTERAPICOMMON_MESSAGES_DATAMESSAGE_H_
#define INCLUDE_HAMSTERAPICOMMON_MESSAGES_DATAMESSAGE_H_

#include <HamsterAPICommon/Messages/HamsterMessage.h>
#include <boost/lexical_cast.hpp>
#include <CogniAlgCPP/CogniAlgMessage.h>

namespace HamsterAPI
{
	class DataMessage : public HamsterMessage
	{
	private:
		AgentID source_id_, target_id_;
		uint32_t data_size_;
		cogni::M_DATA data_;

	public:
		DataMessage(AgentID source_id=-1, AgentID target_id=-1, uint32_t data_size=0, const cogni::M_DATA & data=cogni::M_DATA())
		:source_id_(source_id),target_id_(target_id),data_size_(data_size),data_(data){}
		DataMessage(const DataMessage & data)
		:source_id_(data.source_id_),target_id_(data.target_id_),data_size_(data.data_size_),data_(data.data_){}
		DataMessage(const std::string & message, AgentID source_id=-1, AgentID target_id=-1);
		virtual ~DataMessage(){}

		AgentID getTargetAgentID()const{return target_id_;}
		AgentID getSourceAgentID()const{return source_id_;}
		cogni::M_DATA getData()const{return data_;}
		std::string getStringData()const{return std::string(data_.begin(), data_.end());}
		uint32_t getDataSize()const{return data_size_;}

	public:
		void setTargetAgentID(const AgentID & id){target_id_ = id;}
		void setSourceAgentID(const AgentID & id){source_id_ = id;}
		void setData(const cogni::M_DATA & data){data_ = data; data_size_ = data_.size();}
		void setStringData(const std::string & data);

		virtual std::string toString()const;

		friend class DataMessageCreator;
	};

	class DataMessageCreator
	{
	public:
		AgentID source_id_number,target_id_number;
		uint32_t data_size;
		cogni::M_DATA data;

	public:
		void resize();
		DataMessage create()const;
		void setDataMessage(const DataMessage & datamsg);
	};
}



#endif /* INCLUDE_HAMSTERAPICOMMON_MESSAGES_DATAMESSAGE_H_ */
