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

//共享全局变量
extern HINSTANCE g_hInstance;		//程序句柄
extern HWND pageWnd[7];
extern WCHAR tabName[7][24];
extern HWND hMain;				//用来在子窗口类中根据子窗口大小调整main窗口的大小
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