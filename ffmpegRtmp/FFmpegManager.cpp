#include "FFmpegManager.h"


FFmpegManager::FFmpegManager()
{
	//ע�����еı������
	avcodec_register_all();
	//ע�����еķ�װ��
	av_register_all();
	//ע����������Э��
	avformat_network_init();

	avfilter_register_all();

	av_log_set_level(AV_LOG_ERROR);
}


FFmpegManager::~FFmpegManager()
{
}
