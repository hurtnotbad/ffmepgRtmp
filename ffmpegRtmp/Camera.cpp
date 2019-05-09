#include "Camera.h"

/*
	VideoCapture camera;
		camera.open(0);
		Mat frame;
		for (;;) {

			camera.read(frame);
			imshow("camera", frame);
			waitKey(30);
		}

*/

Camera::Camera()
{
	
}


Camera::~Camera()
{
	if (camera.isOpened())
		camera.release();
}


bool Camera::openCamera(const char * url)
{
	if (url == NULL) {
		camera.open(0);
		
	}
	else
	{
		camera.open(url);
	}
	
	if(camera.isOpened()) {
		this->width = camera.get(CAP_PROP_FRAME_WIDTH);
		this->height = camera.get(CAP_PROP_FRAME_HEIGHT);
		int fomrat = camera.get(CAP_PROP_XI_DATA_FORMAT);
		this-> fps = camera.get(CAP_PROP_FPS);
		printf("fomrat = %d\n", fomrat);
		return true;
	}
	if (camera.isOpened())
	{
		camera.release();
	}


	return false;
}

bool Camera::getCameraData()
{
//	camera.read(frame);
	
	//read  ������ grab  �� retrieve 2����
	///grab ��ȡ ���� ����
	/// retrieve �� ת��ͼ���ɫ��

	///��ȡrtsp��Ƶ֡��������Ƶ֡
	if (!camera.grab())
	{
		return false;
	}
	///yuvת��Ϊbgr24
	if (!camera.retrieve(frame))
	{
		return false;
	}
	return true;
}


