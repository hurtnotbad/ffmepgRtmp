#include "Encode264.h"
#include "FFmpegManager.h"

Encode264::Encode264()
{
	
}
Encode264::~Encode264()
{
}

bool Encode264::Init(int width, int height ,int fps)
{
	cout << "OpenCodec .................!" << endl;
	VideoEncoder = avcodec_find_encoder(AV_CODEC_ID_H264);
	if (!VideoEncoder)
	{
		throw exception("Can`t find h264 encoder!");
		return false;
	}

	//b ����������������
	VideoEncodeContext = avcodec_alloc_context3(VideoEncoder);
	if (!VideoEncodeContext)
	{
		throw exception("avcodec_alloc_context3 failed!");
	}
	//c ���ñ���������
	VideoEncodeContext->flags |= AV_CODEC_FLAG_GLOBAL_HEADER; //ȫ�ֲ���
	VideoEncodeContext->codec_id = VideoEncoder->id;
	VideoEncodeContext->thread_count = 8;

	VideoEncodeContext->bit_rate = 50 * 1024 * 8;//ѹ����ÿ����Ƶ��bitλ��С 50kB
	VideoEncodeContext->width = width;
	VideoEncodeContext->height = height;
	VideoEncodeContext->time_base = { 1,fps };
	VideoEncodeContext->framerate = { fps,1 };

	//������Ĵ�С������֡һ���ؼ�֡
	VideoEncodeContext->gop_size = 50;
	VideoEncodeContext->max_b_frames = 0;
	VideoEncodeContext->pix_fmt = AV_PIX_FMT_YUV420P;
	//d �򿪱�����������
	int ret = avcodec_open2(VideoEncodeContext, 0, 0);
	if (ret != 0)
	{
		char buf[1024] = { 0 };
		av_strerror(ret, buf, sizeof(buf) - 1);
		throw exception(buf);
	}
	cout << "avcodec_open2 success!" << endl;

	av_log(NULL, 0, "Encode264 Init success\n");
	return true;
}



void Encode264::EnCodeFrame(AVFrame * avframe, int pts)
{
	avframe->pts = pts;
	int ret = avcodec_send_frame(VideoEncodeContext, avframe);
	if (ret != 0)
	{
		av_log(NULL, 0, "send frame failed ! \n");
	}
	else
	{
		av_log(NULL, 0, "receive frame success ! \n");
	}

	ret = avcodec_receive_packet(VideoEncodeContext, outPacket);
	if (ret != 0 )//|| outPacket->size > 0
	{
		av_log(NULL, 0, "receive frame failed ! \n");
	}
	else
	{
		av_log(NULL, 0, "receive frame success ! \n");
	}
	
}
