#include "pch.h"
#include "Camera.h"
#include "Encode264.h"
#include "Mux.h"
#include "FormatTranslate.h"
#include "FFmpegManager.h"
int main()
{

	//海康相机的rtsp url
	const char *inUrl = "rtsp://test:test123456@192.168.1.64";
	//nginx-rtmp 直播服务器rtmp推流URL
	const char *outUrl = "rtmp://192.168.32.129/live";

	FFmpegManager* ffmpegManager = new FFmpegManager;
	Camera camera;
	camera.openCamera(0);
	printf("width = %d， height= %d \n", camera.width, camera.height);
	Encode264 encode264;
	encode264.Init(camera.width,camera.height,40 );//camera.fps
	FormatTranslate formatTranslate;
	formatTranslate.Init(camera.width, camera.height, AV_PIX_FMT_RGB24, camera.width, camera.height, AV_PIX_FMT_YUV420P);
	Mux mux;
	mux.Init(outUrl,encode264.VideoEncodeContext);

	int cPts = 0;
	for (;;)
	{
		bool re = camera.getCameraData(); 
		if (re)
		{
			//imshow("camera", camera.frame);
		}
		else {
			continue;
		}
		uint8_t *indata[AV_NUM_DATA_POINTERS] = { 0 };
		indata[0] = camera.frame.data; 
		int insize[AV_NUM_DATA_POINTERS] = { 0 };
		insize[0] = camera.width * camera.frame.elemSize();
	//	printf("insize= %d \n",  insize[0]);		
		if (!formatTranslate.Translate(indata, insize))
			continue;

		encode264.EnCodeFrame(formatTranslate.dstFrame, cPts);
		cPts++;
		mux.muxPacket(encode264.outPacket, encode264.VideoEncodeContext);
		mux.rtmp(encode264.outPacket);
		//waitKey(10);
	}
		
	
getchar();
return 0;

}
