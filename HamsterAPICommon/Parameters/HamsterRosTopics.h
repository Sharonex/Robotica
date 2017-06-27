/*
 * HamsterRosTopics.h
 *
 *  Created on: Jul 13, 2016
 *      Author: ofir
 */

#ifndef INCLUDE_HAMSTERAPICOMMON_PARAMETERS_HAMSTERROSTOPICS_H_
#define INCLUDE_HAMSTERAPICOMMON_PARAMETERS_HAMSTERROSTOPICS_H_

#include <sstream>

namespace HamsterAPI
{
	struct HamsterGlobalTopics
	{
		std::string data_messages_topic_;
		std::string slam_occupancy_grid_topic_;
		std::string navigation_finished_topic_;
		std::string hamster_mode_topic_;
		std::string heartbeat_topic_;

		HamsterGlobalTopics():data_messages_topic_("/agents/data_messages"),slam_occupancy_grid_topic_("/map"),
				navigation_finished_topic_("/mrm/navigation/finished"),hamster_mode_topic_("/mapping_command"),
				heartbeat_topic_("/agents/heartbeat"){}
		virtual ~HamsterGlobalTopics(){}

		std::string toString()const
		{
			std::stringstream output;

			output << "Global Topics : " << std::endl;
			output << "Data Messages Topic = " << data_messages_topic_ << std::endl;
			output << "SLAM Occupancy Grid Topic = " << slam_occupancy_grid_topic_ << std::endl;
			output << "Navigation Finished Topic " << navigation_finished_topic_ << std::endl;
			output << "Hamster Mode Topic = " << hamster_mode_topic_ << std::endl;
			output << "Heartbeat Topic = " << heartbeat_topic_ << std::endl;

			return output.str();
		}
	};

	struct HamsterAgentTopics
	{
		std::string speed_topic_;
		std::string pose_topic_;
		std::string gps_topic_;
		std::string imu_topic_;
		std::string camera_topic_;
		std::string camera_info_topic_;
		std::string lidar_topic_;
		std::string occupancy_grid_publisher_topic_;
		std::string battery_topic_;
		std::string network_topic_;
		std::string navigation_goal_topic_;
		std::string navigation_stop_topic_;
		std::string navigation_status_topic_;
		std::string initial_pose_topic_;

		HamsterAgentTopics():speed_topic_("/agent1/ackermann_cmd"),pose_topic_("/agent1/pose"),
				   gps_topic_("/agent1/gps"),imu_topic_("/agent1/imu"),
				   camera_topic_("/agent1/image"),camera_info_topic_("/agent1/camera/camera_info"),lidar_topic_("/agent1/scan"),
				   occupancy_grid_publisher_topic_("/agent1/occupancy_grid"),
				   battery_topic_("/agent1/battery"),network_topic_("/agent1/rssi"),
				   navigation_status_topic_("/agent1/navigation/status"),navigation_goal_topic_("/agent1/move_base_simple/goal"),
				   navigation_stop_topic_("/agent1/move_base_simple/cancel"),initial_pose_topic_("/agent1/initialpose"){}
		virtual ~HamsterAgentTopics(){}

		std::string toString()const
		{
			std::stringstream output;

			output << "Agent Topics : " << std::endl;
			output << "Speed Topic = " << speed_topic_ << std::endl;
			output << "Pose Topic = " << pose_topic_ << std::endl;
			output << "GPS Topic = " << gps_topic_ << std::endl;
			output << "IMU Topic = " << imu_topic_ << std::endl;
			output << "Camera Topic = " << camera_topic_ << std::endl;
			output << "Camera Info Topic = " << camera_info_topic_ << std::endl;
			output << "Lidar Topic = " << lidar_topic_ << std::endl;
			output << "User Occupancy Grid Topic = " << occupancy_grid_publisher_topic_ << std::endl;
			output << "Battery Topic = " << battery_topic_ << std::endl;
			output << "Network Topic = " << network_topic_ << std::endl;
			output << "Navigation Status Topic " << navigation_status_topic_ << std::endl;
			output << "Navigation Goal Topic = " << navigation_goal_topic_ << std::endl;
			output << "Navigation Stop Topic " << navigation_stop_topic_ << std::endl;
			output << "Initial Pose Topic " << initial_pose_topic_ << std::endl;

			return output.str();
		}
	};

	class HamsterRosTopics
	{
	public:
		HamsterGlobalTopics global_topics;
		HamsterAgentTopics agent_topics;

		HamsterRosTopics(){}
		virtual ~HamsterRosTopics(){}

		std::string toString()const
		{
			std::stringstream output;

			output << global_topics.toString() << std::endl;
			output << agent_topics.toString() << std::endl;

			return output.str();
		}
	};
}



#endif /* INCLUDE_HAMSTERAPICOMMON_PARAMETERS_HAMSTERROSTOPICS_H_ */
