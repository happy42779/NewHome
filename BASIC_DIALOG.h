#pragma once
#ifndef _BASIC_DIALOG_H_
#define _BASIC_DIALOG_H_

#include "precompiler.h"

//��������д��ڵĹ�ͬ�㣬��Ϊһ���ӿ�
class BASIC_DIALOG
{
	//����ӿڣ����麯����
public:
	BASIC_DIALOG():hWndCtrl(NULL){x = GetSystemMetrics(SM_CXSCREEN);y = GetSystemMetrics(SM_CYSCREEN);};
	~BASIC_DIALOG(){};
public:
	int x,y,width,height;	//���ڴ�С������
	HWND hWndCtrl;	//���ھ��
	//RECT rect;		//����ÿ�����ڵ�rect
};

#endif