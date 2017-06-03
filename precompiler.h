#pragma once
#ifndef _PRECOMPILER_H_
#define _PRECOMPILER_H_

#include <windows.h>
#include <CommCtrl.h>
#include <string>

#include "resource.h"

#define _info_page 0
#define _add_page 1
#define _search_page 2

//����ȫ�ֱ���
extern HINSTANCE g_hInstance;		//������
extern HWND pageWnd[7];
extern WCHAR tabName[7][24];
extern HWND hMain;				//�������Ӵ������и����Ӵ��ڴ�С����main���ڵĴ�С
extern HWND hTab;


//debug
void LastError()
{
	WCHAR _error[256] = {0};
	int errCode;
	errCode = GetLastError();
	FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM,NULL,errCode,0,_error,256,NULL);
	OutputDebugString(_error);
	return;
}
#endif