/*
 * Hamster.h
 *
 *  Created on: Jul 11, 2016
 *      Author: ofir
 */

#ifndef INCLUDE_HAMSTERCLIENT_HAMSTER_H_
#define INCLUDE_HAMSTERCLIENT_HAMSTER_H_

#include <HamsterAPICommon/Messages/IMU.h>
#include <HamsterAPICommon/Messages/GPS.h>
#include <HamsterAPICommon/Messages/LidarScan.h>
#include <HamsterAPICommon/Messages/Image.h>
#include <HamsterAPICommon/Messages/Pose.h>
#include <HamsterAPICommon/Messages/DataMessage.h>
#include <HamsterAPICommon/Messages/OccupancyGrid.h>
#include <HamsterAPICommon/Messages/HamsterMode.h>
#include <HamsterAPICommon/Messages/BatteryState.h>
#include <HamsterAPICommon/Messages/NetworkState.h>
#include <HamsterAPICommon/Messages/NavigationState.h>
#include <HamsterAPICommon/Messages/ColoredScan.h>
#include <HamsterAPICommon/Messages/Speed.h>
#include <HamsterAPICommon/Messages/Goal.h>
#include <HamsterAPICommon/Messages/HamsterConnections.h>

#include <HamsterAPICommon/Parameters/HamsterClientParameters.h>

#include <HamsterAPICommon/Common/HamsterError.h>
#include <HamsterAPICommon/Common/Log.h>

namespace HamsterAPI
{
	class HamsterImpl;
	class Hamster
	{
	private:
		HamsterImpl * pimpl_;

	public:
		/**
		 * Hamster Constructor
		 * The client parameters contain the following:
		 * 	- base_address - The network base address to work with, if the address is 127.0.0 then the connection will always go to loopback
		 * 					 Otherwise it will go to base_adress.agent_id
		 * 					 For example : base_address = 10.0.2 agent_id = 1 so it will connect to 10.0.2.1:port
		 * 	- port - The port to connect on
		 * @param agent_id
		 * @param params
		 */
		Hamster(const AgentID & agent_id, HamsterClientParameters params = HamsterClientParameters());

		/**
		 * Destructor
		 */
		virtual ~Hamster();

		/**
		 * Retrieves the camera image from the hamster.
		 * Buffer Size - 1.
		 * @return - Camera Image.
		 * @throw - HamsterError is thrown for the following:
		 * 	- Empty Buffer.
		 * 	- Connection Issue.
		 */
		Image getCameraImage()const;

		/**
		 * Retrieves the global pose of the hamster.
		 * The global pose is associated with the SLAM part of the hamster.
		 * Buffer Size - 1.
		 * @return - Global Pose.
		 * @throw - HamsterError is thrown for the following:
		 * 	- Empty Buffer.
		 * 	- Connection Issue.
		 */
		Pose getPose()const;

		/**
		 * Retrieves the IMU information from the hamster if an IMU exists.
		 * Buffer Size - 1.
		 * @return - IMU.
		 * @throw - HamsterError is thrown for the following:
		 * 	- Empty Buffer.
		 * 	- Connection Issue.
		 */
		IMU getIMU()const;

		/**
		 * Retrieves the GPS information from the hamster is a GPS exists.
		 * Buffer Size - 1.
		 * @return - GPS.
		 * @throw - HamsterError is thrown for the following:
		 * 	- Empty Buffer.
		 * 	- Connection Issue.
		 */
		GPS getGPS()const;

		/**
		 * Retrieves the 360 degree lidar scan from the hamster.
		 * Buffer Size - 1.
		 * @return - LidarScan.
		 * @throw - HamsterError is thrown for the following:
		 * 	- Empty Buffer.
		 * 	- Connection Issue.
		 */
		LidarScan getLidarScan()const;

		/**
		 * Retrieves a ColoredScan.
		 * ColoredScan is a combination of the hamster lidar and camera synchronized.
		 * It contains the raw lidar scan and the associated pixels RGB color of the image.
		 * Buffer Size - 1.
		 * @return - ColoredScan.
		 * @throw - HamsterError is thrown for the following:
		 * 	- Empty Buffer.
		 * 	- Connection Issue.
		 */
		ColoredScan getColoredScan()const;

		/**
		 * Retrieves the current speed of the hamster.
		 * The is usually the speed given by the latest speed command or from the wandering / navigation.
		 * Buffer Size - 1.
		 * @return - Speed.
		 * @throw - HamsterError is thrown for the following:
		 * 	- Empty Buffer.
		 * 	- Connection Issue.
		 */
		Speed getSpeed()const;

		/**
		 * Retrieves the current mode of the hamster.
		 * The available modes are:
		 * 	- Localization.
		 * 	- Mapping.
		 * Buffer Size - 1.
		 * @return - HamsterMode.
		 * @throw - HamsterError is thrown for the following:
		 * 	- Empty Buffer.
		 * 	- Connection Issue.
		 */
		HamsterMode getHamsterMode()const;

		/**
		 * Retrieves the current SLAM map that was loaded or created by the hamster as an occupancy grid.
		 * Buffer Size - 1.
		 * @return - OccupancyGrid.
		 * @throw - HamsterError is thrown for the following:
		 * 	- Empty Buffer.
		 * 	- Connection Issue.
		 */
		OccupancyGrid getSLAMMap()const;

		/**
		 * Retrieves the currently living hamsters on the network.
		 * Meaning that for example there are 3 hamsters on the same network {agent1, agent2, agent3}
		 * If the current hamster got an heartbeat from all the others, there will be 3 connections on the list.
		 * Buffer Size - 1.
		 * @return - HamsterConnections
		 * @throw - HamsterError is thrown for the following:
		 * 	- Empty Buffer.
		 * 	- Connection Issue.
		 */
		HamsterConnections getConnectedHamsters()const;

		/**
		 * Retrieves the current battery state of the hamster.
		 * Buffer Size - 1.
		 * @return - BatteryState.
		 * @throw - HamsterError is thrown for the following:
		 * 	- Empty Buffer.
		 * 	- Connection Issue.
		 */
		BatteryState getBatteryState()const;

		/**
		 * Retrieves the current network state of the hamster with the network.
		 * Buffer Size - 1.
		 * @return - NetworkState
		 * @throw - HamsterError is thrown for the following:
		 * 	- Empty Buffer.
		 * 	- Connection Issue.
		 */
		NetworkState getNetworkState()const;

		/**
		 * Retrieves the navigation state of the hamster.
		 * The navigation state depends whether there was a goal request or not.
		 * There are four types of states:
		 * 	- Offline.
		 * 	- In Progress.
		 * 	- Reached Goal.
		 * 	- Failure.
		 * Buffer Size - 1.
		 * @return - NavigationState.
		 * @throw - HamsterError is thrown for the following:
		 * 	- Empty Buffer.
		 * 	- Connection Issue.
		 */
		NavigationState getNavigationState()const;


		/**
		 * Sends a speed request to the hamster.
		 * If there is an active goal, the speed request will be ignored and an HamsterError will be thrown.
		 * This method is based on ackermann speed.
		 * @param velocity.
		 * @param wheels_angle.
		 * @throw - HamsterError is thrown for the following:
		 * 	- Connection Issue.
		 * 	- Running Goal.
		 */
		void sendSpeed(float velocity, float wheels_angle);

		/**
		 * Sends an Occupancy Grid to the server to be published.
		 * Can be viewed via RViz.
		 * @param grid.
		 * @throw - HamsterError is thrown for the following:
		 * 	- Connection Issue.
		 */
		void sendOccupancyGrid(const OccupancyGrid & grid);

		/**
		 * Switches hamster mode to one of the following:
		 * 	- Mapping.
		 * 	- Localization.
		 * @param mode.
		 * @throw - HamsterError is thrown for the following:
		 * 	- Connection Issue.
		 */
		void switchMode(const HamsterMode & mode);

		/**
		 * Navigates to a given goal.
		 * The goal can be either local goal or global goal.
		 * @param goal.
		 * @throw - HamsterError is thrown for the following:
		 * 	- Connection Issue.
		 */
		void navigateTo(const Goal & goal);

		/**
		 * Navigates to a given distance and angle.
		 * This is simillar to giving a local goal with distance and angle calculated to X and Y.
		 * @param distance
		 * @param angle
		 * @throw - HamsterError is thrown for the following:
		 * 	- Connection Issue.
		 */
		void navigateTo(float distance, float angle);

		/**
		 * Sets the initial position of the agent on the global map.
		 * This is useful for a starting 0,0 position for mapping or if an agent needs to reposition to a starting position.
		 * @param pose
		 * @throw - HamsterError is thrown for the following:
		 * 	- Connection Issue.
		 */
		void setInitialPose(const Pose & pose);


		/**
		 * Stops the navigation if there is an active goal.
		 * @throw - HamsterError is thrown for the following:
		 * 	- Connection Issue.
		 */
		void stopNavigation();


		/**
		 * Getter for the current Agent ID.
		 * @return - AgentID.
		 */
		AgentID getAgentID()const;

		/**
		 * Getter for the lidar resolution.
		 * @return - float.
		 */
		float getLidarResolution()const;


		/**
		 * Checks whether the client is still connected to the server.
		 * A connection problem can arise from heartbeat failure or from FIN from the server side.
		 * @return - bool.
		 */
		bool isConnected()const;

		/**
		 * Cleans all the buffers for all the messages (this includes the text messages).
		 */
		void cleanBuffers();


		/**
		 * Sends a data message to another hamster.
		 * This will be published on the network with the current agent id and the target agent id.
		 * If the target is in the network, it will receive it.
 	 	 * The following API can be used for messages:
		 * 	- hasDataMessages().
		 * 	- getLatestDataMessage().
		 * 	- getLatestDataMessages(Amount).
		 * 	- getDataMessagesAmount().
		 * 	- clearDataMessagesBuffer().
		 *  - setDataMessageBufferSize(Amount).
		 *  - getDataMessageBufferSize().
		 *  - sendDataMessage(Agent, DataMessage).
		 *  - sendBroadcastDataMessage(DataMessage).
		 * @param agent_id.
		 * @param message.
		 * @throw - HamsterError is thrown for the following:
		 * 	- Connection Issue.
		 */
		void sendDataMessage(const AgentID & target_agent_id, const std::string & message);
		void sendDataMessage(const DataMessage & message);

		/**
		 * Sends a data message to all the hamsters on the network
		 * Every hamster that see's the message will pick it up
 	 	 * The following API can be used for messages:
		 * 	- hasDataMessages().
		 * 	- getLatestDataMessage().
		 * 	- getLatestDataMessages(Amount).
		 * 	- getDataMessagesAmount().
		 * 	- clearDataMessagesBuffer().
		 *  - setDataMessageBufferSize(Amount).
		 *  - getDataMessageBufferSize().
		 *  - sendDataMessage(Agent, DataMessage).
		 *  - sendBroadcastDataMessage(DataMessage)
		 * @param message
		 * @throw - HamsterError is thrown for the following:
		 * 	- Connection Issue.
		 */
		void sendBroadcastDataMessage(const DataMessage & message);
		void sendBroadcastDataMessage(const std::string & message);

		/**
		 * Gets/Pops the data messages that were received from the other agents.
		 * Will try to get the max possible messages untill the given amount.
 	 	 * The following API can be used for messages:
		 * 	- hasDataMessages().
		 * 	- getLatestDataMessage().
		 * 	- getLatestDataMessages(Amount).
		 * 	- getDataMessagesAmount().
		 * 	- clearDataMessagesBuffer().
		 *  - setDataMessageBufferSize(Amount).
		 *  - getDataMessageBufferSize().
		 *  - sendDataMessage(Agent, DataMessage).
		 *  - sendBroadcastDataMessage(DataMessage).
		 * Buffer Size - Determined by setDataMessageBufferSize, Defaults to 1000.
		 * @param message
		 * @throw - HamsterError is thrown for the following:
		 *  - Empty Buffer.
		 * 	- Connection Issue.
		 */
		DataMessage getLatestDataMessage()const;
		std::vector<DataMessage> getLatestDataMessages(uint32_t amount)const;
		DataMessage popLatestDataMessage();
		std::vector<DataMessage> popLatestDataMessages(uint32_t amount);

		/**
		 * Checks whether there are any messages.
 	 	 * The following API can be used for messages:
		 * 	- hasDataMessages().
		 * 	- getLatestDataMessage().
		 * 	- getLatestDataMessages(Amount).
		 * 	- getDataMessagesAmount().
		 * 	- clearDataMessagesBuffer().
		 *  - setDataMessageBufferSize(Amount).
		 *  - getDataMessageBufferSize().
		 *  - sendDataMessage(Agent, DataMessage).
		 *  - sendBroadcastDataMessage(DataMessage).
		 * @param message
		 */
		bool hasDataMessages()const;

		/**
		 * Getter for the amount of data messages.
 	 	 * The following API can be used for messages:
		 * 	- hasDataMessages().
		 * 	- getLatestDataMessage().
		 * 	- getLatestDataMessages(Amount).
		 * 	- getDataMessagesAmount().
		 * 	- clearDataMessagesBuffer().
		 *  - setDataMessageBufferSize(Amount).
		 *  - getDataMessageBufferSize().
		 *  - sendDataMessage(Agent, DataMessage).
		 *  - sendBroadcastDataMessage(DataMessage).
		 * @param message
		 */
		uint32_t getDataMessagesAmount()const;

		/**
		 * Cleans the data message buffer completely.
 	 	 * The following API can be used for messages:
		 * 	- hasDataMessages().
		 * 	- getLatestDataMessage().
		 * 	- getLatestDataMessages(Amount).
		 * 	- getDataMessagesAmount().
		 * 	- clearDataMessagesBuffer().
		 *  - setDataMessageBufferSize(Amount).
		 *  - getDataMessageBufferSize().
		 *  - sendDataMessage(Agent, DataMessage).
		 *  - sendBroadcastDataMessage(DataMessage).
		 * @param message
		 */
		void clearDataMessagesBuffer();

		/**
		 * Setter for the size of the data message buffer.
 	 	 * The following API can be used for messages:
		 * 	- hasDataMessages().
		 * 	- getLatestDataMessage().
		 * 	- getLatestDataMessages(Amount).
		 * 	- getDataMessagesAmount().
		 * 	- clearDataMessagesBuffer().
		 *  - setDataMessageBufferSize(Amount).
		 *  - getDataMessageBufferSize().
		 *  - sendDataMessage(Agent, DataMessage).
		 *  - sendBroadcastDataMessage(DataMessage).
		 * @param message
		 */
		void setDataMessageBufferSize(uint32_t amount);

		/**
		 * Getter for the size of the data message buffer.
 	 	 * The following API can be used for messages:
		 * 	- hasDataMessages().
		 * 	- getLatestDataMessage().
		 * 	- getLatestDataMessages(Amount).
		 * 	- getDataMessagesAmount().
		 * 	- clearDataMessagesBuffer().
		 *  - setDataMessageBufferSize(Amount).
		 *  - getDataMessageBufferSize().
		 *  - sendDataMessage(Agent, DataMessage).
		 *  - sendBroadcastDataMessage(DataMessage).
		 * @param message
		 */
		uint32_t getDataMessageBufferSize()const;


		/**
		 * Tries to reconnect to the server.
		 * @throw - HamsterError is thrown for the following:
		 * 	- Connection Issue.
		 */
		void reconnect();

		/**
		 * Disconnects from the server.
		 */
		void disconnect();
	};
}

#endif /* INCLUDE_HAMSTERCLIENT_HAMSTER_H_ */
