#pragma once
#include "FFmpegManager.h"
class FormatTranslate
{
public:
	SwsContext *swsCtx = NULL;
	int inWidth; int inHeight;
	AVPixelFormat  inPixFormat;
	int outWidth; int outHeight;
	AVPixelFormat  outPixFormat;
	AVFrame * dstFrame = NULL;
public:
	FormatTranslate();
	~FormatTranslate();
	
	bool Translate(uint8_t **indata, int *linesize);
	void Init(int inWidth, int inHeight, AVPixelFormat  inPixFormat, int outWidth, int outHeight, AVPixelFormat  outPixFormat);
};

