#include "FFmpegManager.h"


FFmpegManager::FFmpegManager()
{
	//注册所有的编解码器
	avcodec_register_all();
	//注册所有的封装器
	av_register_all();
	//注册所有网络协议
	avformat_network_init();

	avfilter_register_all();

	av_log_set_level(AV_LOG_ERROR);
}


FFmpegManager::~FFmpegManager()
{
}
