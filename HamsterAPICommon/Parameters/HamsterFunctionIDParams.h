/*
 * HamsterFunctionIDParams.h
 *
 *  Created on: Jul 13, 2016
 *      Author: ofir
 */

#ifndef INCLUDE_HAMSTERAPICOMMON_PARAMETERS_HAMSTERFUNCTIONIDPARAMS_H_
#define INCLUDE_HAMSTERAPICOMMON_PARAMETERS_HAMSTERFUNCTIONIDPARAMS_H_

#include <CogniAlgCPP/CogniAlgMessage.h>
#include <sstream>

namespace HamsterAPI
{
	class HamsterFunctionIDParams
	{
	public:
		cogni::M_ID gps_stream_id;
		cogni::M_ID imu_stream_id;
		cogni::M_ID lidar_stream_id;
		cogni::M_ID pose_stream_id;
		cogni::M_ID speed_stream_id;
		cogni::M_ID camera_stream_id;
		cogni::M_ID data_messages_stream_id;
		cogni::M_ID slam_occupancy_grid_stream_id;
		cogni::M_ID hamster_mode_stream_id;
		cogni::M_ID battery_state_stream_id;
		cogni::M_ID network_state_stream_id;
		cogni::M_ID navigation_state_stream_id;
		cogni::M_ID colored_scan_stream_id;
		cogni::M_ID fin_stream_id;
		cogni::M_ID hamster_connections_stream_id;

		cogni::M_ID data_messages_command_id;
		cogni::M_ID speed_command_id;
		cogni::M_ID occupancy_grid_command_id;
		cogni::M_ID hamster_mode_command_id;
		cogni::M_ID fin_command_id;
		cogni::M_ID initial_pose_command_id;

		cogni::M_ID handshake_request_id;
		cogni::M_ID goal_request_id;
		cogni::M_ID client_to_server_heartbeat_request_id;

		cogni::M_ID server_to_server_heartbeat_id;

		HamsterFunctionIDParams():gps_stream_id(200),imu_stream_id(201),lidar_stream_id(202),
								  pose_stream_id(203),speed_stream_id(204),camera_stream_id(205),
								  data_messages_stream_id(206),slam_occupancy_grid_stream_id(207),hamster_mode_stream_id(208),
								  battery_state_stream_id(209),network_state_stream_id(210),navigation_state_stream_id(211),
								  colored_scan_stream_id(212),fin_stream_id(213),hamster_connections_stream_id(214),
								  data_messages_command_id(400),speed_command_id(401),
								  occupancy_grid_command_id(402),hamster_mode_command_id(403),fin_command_id(404),initial_pose_command_id(405),
								  handshake_request_id(600),goal_request_id(601),client_to_server_heartbeat_request_id(602),
								  server_to_server_heartbeat_id(800){}

		virtual ~HamsterFunctionIDParams(){}

		std::string toString()const
		{
			std::stringstream output;

			output << "GPS Stream FID = " << gps_stream_id << std::endl;
			output << "IMU Stream FID = " << imu_stream_id << std::endl;
			output << "Lidar Stream FID = " << lidar_stream_id << std::endl;
			output << "Pose Stream FID = " << lidar_stream_id << std::endl;
			output << "Speed Stream FID = " << speed_stream_id << std::endl;
			output << "Camera Stream FID = " << camera_stream_id << std::endl;
			output << "Data Messages Stream FID = " << data_messages_stream_id << std::endl;
			output << "SLAM Occupancy Grid Stream FID = " << slam_occupancy_grid_stream_id << std::endl;
			output << "Hamster Mode Stream FID = " << hamster_mode_stream_id << std::endl;
			output << "Battery State Stream FID = " << battery_state_stream_id << std::endl;
			output << "Network State Stream FID = " << network_state_stream_id << std::endl;
			output << "Navigation State Stream FID = " << navigation_state_stream_id << std::endl;
			output << "Colored Scan Stream FID = " << colored_scan_stream_id << std::endl;
			output << "FIN Stream FID = " << fin_stream_id << std::endl;
			output << "Hamster Connections Stream FID = " << hamster_connections_stream_id << std::endl;

			output << "Data Messages Command FID = " << data_messages_command_id << std::endl;
			output << "Speed Command FID = " << speed_command_id << std::endl;
			output << "Occupancy Grid Command FID = " << occupancy_grid_command_id << std::endl;
			output << "Hamster Mode Command FID = " << hamster_mode_command_id << std::endl;
			output << "FIN Command FID = " << fin_command_id << std::endl;
			output << "Initial Pose Command FID = " << initial_pose_command_id << std::endl;

			output << "Handshake Request FID = " << handshake_request_id << std::endl;
			output << "Goal Request FID = " << goal_request_id << std::endl;
			output << "Client To Server Heartbeat Request FID = " << client_to_server_heartbeat_request_id << std::endl;

			output << "Server To Server Heartbeat FID = " << server_to_server_heartbeat_id << std::endl;

			return output.str();
		}
	};
}



#endif /* INCLUDE_HAMSTERAPICOMMON_PARAMETERS_HAMSTERFUNCTIONIDPARAMS_H_ */
