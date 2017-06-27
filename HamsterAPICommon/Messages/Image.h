/*
 * Image.h
 *
 *  Created on: Jul 10, 2016
 *      Author: ofir
 */

#ifndef INCLUDE_HAMSTERAPISERVER_MESSAGES_IMAGE_H_
#define INCLUDE_HAMSTERAPISERVER_MESSAGES_IMAGE_H_

#include <HamsterAPICommon/Messages/HamsterMessage.h>
#include <opencv2/opencv.hpp>
#include <HamsterAPICommon/Common/Color.h>

namespace HamsterAPI
{
	class Image : public HamsterMessage
	{
	private:
		uint32_t w_, h_, c_, step_;
		std::vector<unsigned char> data_;

	private:
		int getIndex(int x, int y, int cc)const;

	public:
		Image();
		Image(const Image& img);

		Color getPixel(int x, int y)const;
		void setPixel(int x, int y, Color color);
		Image& operator=(const Image& img);
		cv::Mat toCVMat()const;

		virtual std::string toString()const;

	public:
		uint32_t getWidth()const{return w_;}
		uint32_t getHeight()const{return h_;}
		uint32_t getChannelsNumber()const{return c_;}
		unsigned char * getData(){return data_.data();}
		size_t getDataSize()const{ return data_.size(); }

		friend class ImageCreator;
	};

	class ImageCreator
	{
	public:
		uint32_t w, h, c, step;
		std::vector<unsigned char> data;

	public:
		inline void resize(){data.resize(w*h*c);}

	public:
		Image create();
		void setImage(const Image& img);
	};
}



#endif /* INCLUDE_HAMSTERAPISERVER_MESSAGES_IMAGE_H_ */
