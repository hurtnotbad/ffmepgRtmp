#pragma once
#include "pch.h"
extern "C"
{
#include "libavfilter/avfilter.h"

}

class FFmpegManager
{
public:
	int InWidht = 0;
	int InHeight = 0;
	int OutWidht = 0;
	int OutHeight = 0;
	
	Mat frame;
	int VideoStreamIndex = -1;
	int AudioStreamIndex = -1;

	/*****************解封装************************************/
	AVFormatContext* FormatInputContext = NULL;


	/****************封装************************************/
	AVFormatContext* FormatOutputContext = NULL;


	/*****************解码************************************/
	
	AVCodecContext * VideoDecodeContext = NULL;
	AVCodecContext * AudioDecodeContext = NULL;
	AVCodec *VideoDecoder = NULL;
	AVCodec *AudioDecoder = NULL;

	/*****************编码************************************/
	AVCodecContext * VideoEncodeContext = NULL;
	AVCodecContext * AudioEncodeContext = NULL;
	AVCodec *VideoEncoder = NULL;
	AVCodec *AudioEncoder = NULL;




public:
	FFmpegManager();
	~FFmpegManager();
};

