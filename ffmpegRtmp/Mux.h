#pragma once
#include "pch.h"
class Mux
{
public:
	Mux();
	~Mux();
	void Init(const char *outUrl, AVCodecContext *videoCodecCondex);
	void muxPacket(AVPacket * pack, AVCodecContext *videoCodecCondex);
	bool rtmp(AVPacket * pack);
public:
	AVFormatContext *avFmtCt;
	int videoStreamIndex= 0;
	
};

