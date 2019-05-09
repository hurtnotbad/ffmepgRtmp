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

// 里面会释放 packet
bool Mux::rtmp(AVPacket * pack)
{
	// 里面会释放 packet
	int ret = av_interleaved_write_frame(avFmtCt, pack);
	if (ret == 0)
	{
		cout << "#" << flush;
	}
	return false;
}

void Mux::Init(const char *outUrl, AVCodecContext *videoCodecCondex)
{

	///5 输出封装器和视频流配置
		//a 创建输出封装器上下文
	int ret = avformat_alloc_output_context2(&avFmtCt, 0, "flv", outUrl);
	if (ret != 0)
	{
		char buf[1024] = { 0 };
		av_strerror(ret, buf, sizeof(buf) - 1);
		throw exception(buf);
	}
	//b 添加视频流 到avFmtCt
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
	//从编码器复制参数
	avcodec_parameters_from_context(vs->codecpar, videoCodecCondex);
	// 打印封装头
	av_dump_format(avFmtCt, 0, outUrl, 1);

	///打开rtmp 的网络输出IO
	ret = avio_open(&avFmtCt->pb, outUrl, AVIO_FLAG_WRITE);
	if (ret != 0)
	{
		char buf[1024] = { 0 };
		av_strerror(ret, buf, sizeof(buf) - 1);
		throw exception(buf);
	}
	else {

		av_log(NULL, 0, "打开rtmp 的网络输出IO 成功\n");
	}

	//写入封装头
	ret = avformat_write_header(avFmtCt, NULL);
	if (ret != 0)
	{
		char buf[1024] = { 0 };
		av_strerror(ret, buf, sizeof(buf) - 1);
		throw exception(buf);
	}
	av_log(NULL, 0,"写入封装头成功\n");

}
