#include "Mux.h"



Mux::Mux()
{
}


Mux::~Mux()
{
}

void Mux::muxPacket(AVPacket * pack, AVCodecContext *videoCodecCondex)
{
	pack->pts = av_rescale_q(pack->pts, videoCodecCondex->time_base, avFmtCt->streams[videoStreamIndex]->time_base);
	pack->dts = av_rescale_q(pack->dts, videoCodecCondex->time_base, avFmtCt->streams[videoStreamIndex]->time_base);
	pack->duration = av_rescale_q(pack->duration, videoCodecCondex->time_base, avFmtCt->streams[videoStreamIndex]->time_base);
}

// ������ͷ� packet
bool Mux::rtmp(AVPacket * pack)
{
	// ������ͷ� packet
	int ret = av_interleaved_write_frame(avFmtCt, pack);
	if (ret == 0)
	{
		cout << "#" << flush;
	}
	return false;
}

void Mux::Init(const char *outUrl, AVCodecContext *videoCodecCondex)
{

	///5 �����װ������Ƶ������
		//a ���������װ��������
	int ret = avformat_alloc_output_context2(&avFmtCt, 0, "flv", outUrl);
	if (ret != 0)
	{
		char buf[1024] = { 0 };
		av_strerror(ret, buf, sizeof(buf) - 1);
		throw exception(buf);
	}
	//b �����Ƶ�� ��avFmtCt
	AVStream *vs = avformat_new_stream(avFmtCt, NULL);
	if (!vs)
	{
		throw exception("avformat_new_stream failed");
	}
	for (int i = 0; i < avFmtCt->nb_streams; i++)
	{
		AVStream *avStream = avFmtCt->streams[i];
		if (avStream->codecpar->codec_type == AVMEDIA_TYPE_VIDEO)
		{
			videoStreamIndex = i;
		}
	}
	vs->codecpar->codec_tag = 0;
	//�ӱ��������Ʋ���
	avcodec_parameters_from_context(vs->codecpar, videoCodecCondex);
	// ��ӡ��װͷ
	av_dump_format(avFmtCt, 0, outUrl, 1);

	///��rtmp ���������IO
	ret = avio_open(&avFmtCt->pb, outUrl, AVIO_FLAG_WRITE);
	if (ret != 0)
	{
		char buf[1024] = { 0 };
		av_strerror(ret, buf, sizeof(buf) - 1);
		throw exception(buf);
	}
	else {

		av_log(NULL, 0, "��rtmp ���������IO �ɹ�\n");
	}

	//д���װͷ
	ret = avformat_write_header(avFmtCt, NULL);
	if (ret != 0)
	{
		char buf[1024] = { 0 };
		av_strerror(ret, buf, sizeof(buf) - 1);
		throw exception(buf);
	}
	av_log(NULL, 0,"д���װͷ�ɹ�\n");

}
