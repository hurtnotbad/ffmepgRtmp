#include "FormatTranslate.h"



FormatTranslate::FormatTranslate()
{

}

FormatTranslate::~FormatTranslate()
{
	//av_closes(swsCtx);
	if (swsCtx != NULL)
	{
		sws_freeContext(swsCtx);
		swsCtx = NULL;
	}
}


bool FormatTranslate::Translate(uint8_t **indata, int *linesize)
{
	if (outPixFormat == AV_PIX_FMT_YUV420P)
	{
		int h = sws_scale(swsCtx, indata, linesize, 0, inHeight, //Դ����
			dstFrame->data, dstFrame->linesize);
		if (h <= 0)
		{
			return false;
		}


		return true;

	}
	
}

// һ������ֻ�ܳ�ʼ��һ�Ρ�
void FormatTranslate::Init(int inWidth, int inHeight, AVPixelFormat  inPixFormat,   int outWidth , int outHeight ,AVPixelFormat  outPixFormat)
{
	if (swsCtx != NULL)
		return;

	this->inWidth = inWidth;
	this->inHeight = inHeight;
	this->inPixFormat = inPixFormat;
	this->outWidth = outWidth;
	this->outHeight = outHeight;
	this->outPixFormat = outPixFormat;
	///2 ��ʼ����ʽת��������
	swsCtx = sws_getCachedContext(swsCtx,
		inWidth, inHeight, inPixFormat,	 //Դ���ߡ����ظ�ʽAV_PIX_FMT_BGR24
		outWidth, outHeight, outPixFormat,//Ŀ����ߡ����ظ�ʽAV_PIX_FMT_YUV420P
		SWS_BICUBIC,  // �ߴ�仯ʹ���㷨
		0, 0, 0
	);
	if (!swsCtx)
	{
		throw exception("sws_getCachedContext failed!");
	}
	else
	{
		av_log(NULL, 0, "sws_getCachedContext success!");
	}

	///3 ��ʼ����������ݽṹ
	dstFrame = av_frame_alloc();
	dstFrame->format = outPixFormat;
	dstFrame->width = outWidth;
	dstFrame->height = outHeight;
	//dstFrame->pts = 0;
	//����yuv�ռ�
	int ret = av_frame_get_buffer(dstFrame, 64);// 64 Ϊһ֡��ȵĶ��䷽ʽ
	if (ret != 0)
	{
		char buf[1024] = { 0 };
		av_strerror(ret, buf, sizeof(buf) - 1);
		throw exception(buf);
	}
	


}
