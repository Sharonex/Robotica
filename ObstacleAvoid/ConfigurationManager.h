/*
 * HamsterConf.h
 *
 *  Created on: Jul 13, 2017
 *      Author: user
 */

#ifndef SRC_CONFIGURATIONMANAGER_H_
#define SRC_CONFIGURATIONMANAGER_H_

#include <string>
#include <opencv/cv.h>
#include <HamsterAPIClientCPP/Hamster.h>

using namespace HamsterAPI;
using namespace std;

class ConfigurationManager
{
public:
	static void Init()
	{
		s_instance = new ConfigurationManager(Pose(0,0,0),cv::Point2f(3,0),cv::Size2f(0.20,0.20),0.05);
	}

	static void Init(std::string* fileName)
	{
		s_instance = new ConfigurationManager(Pose(0,0,0),cv::Point2f(3,0),cv::Size2f(0.20,0.20),0.05);
	}

	static Pose getStartPose()
	{
		return s_instance->m_startPose;
	}

	static cv::Size2f getRobotSize()
	{
		return s_instance->m_robotSize;
	}

	static cv::Point2f getTargetPoint()
	{
		return s_instance->m_targetPoint;
	}

	static float getMapResolution()
	{
		return s_instance->m_mapResolutionMeter;
	}

	static void Destroy()
	{
		if (s_instance)
		{
			delete s_instance;
		}
	}
private:
	static ConfigurationManager *s_instance;

	// Class members
	Pose m_startPose;
	cv::Point2f m_targetPoint;
	cv::Size2f m_robotSize;
	float m_mapResolutionMeter;

	ConfigurationManager(Pose startPose,cv::Point2f targetPoint,cv::Size2f robotSize,float mapResolutionMeter){
		// x, y, Yaw
		m_startPose = startPose;
		m_targetPoint = targetPoint;
		m_robotSize = robotSize;
		m_mapResolutionMeter = mapResolutionMeter;
	}
};

// Define static members
ConfigurationManager *ConfigurationManager::s_instance = 0;


#endif /* SRC_CONFIGURATIONMANAGER_H_ */
