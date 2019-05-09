#pragma once
#include "pch.h"
#include "FFmpegManager.h"
class Camera
{
public:
	VideoCapture camera;
	int width;
	int height;
	Mat frame;
	int fps = 0;
public:
	Camera();
	~Camera();


	bool openCamera(const char* url);
	
	bool getCameraData();



};

