#pragma once
#ifndef _BASIC_DIALOG_H_
#define _BASIC_DIALOG_H_

#include "precompiler.h"

//抽象出所有窗口的共同点，作为一个接口
class BASIC_DIALOG
{
	//定义接口（纯虚函数）
public:
	BASIC_DIALOG():hWndCtrl(NULL){x = GetSystemMetrics(SM_CXSCREEN);y = GetSystemMetrics(SM_CYSCREEN);};
	~BASIC_DIALOG(){};
public:
	int x,y,width,height;	//窗口大小，坐标
	HWND hWndCtrl;	//窗口句柄
	//RECT rect;		//保存每个窗口的rect
};

#endif