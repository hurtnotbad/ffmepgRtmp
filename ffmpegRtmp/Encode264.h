#pragma once
#include "pch.h"
#include "FFmpegManager.h"
class Encode264
{
public:
	Encode264();
	~Encode264();
	
	bool Init(int widht, int height, int fps);
	void EnCodeFrame(AVFrame * avframe, int pts);

public:

	AVCodecContext * VideoEncodeContext = NULL;
	AVCodecContext * AudioEncodeContext = NULL;
	AVCodec *VideoEncoder = NULL;
	AVCodec *AudioEncoder = NULL;
	AVPacket *outPacket = av_packet_alloc();
};

