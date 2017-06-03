#pragma once
#ifndef _INFO_DIALOG_H_
#define _INFO_DIALOG_H_

#include "precompiler.h"
#include "BASIC_DIALOG.h"

class INFO_DIALOG;
extern INFO_DIALOG* pInfoDlg;

class INFO_DIALOG:public BASIC_DIALOG
{
public:
	INFO_DIALOG();
	~INFO_DIALOG();
public:
	static INT_PTR CALLBACK DlgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

public:	//控件
};

INFO_DIALOG::INFO_DIALOG()
{
	RECT rect;

	pageWnd[_info_page] = CreateDialogParam(g_hInstance,MAKEINTRESOURCE(IDD_DIALOG_GENEINFO),hTab,DlgProc,NULL);
	if(NULL == pageWnd[_info_page])
		LastError();
	
	//根据page的大小来调整tab的大小
	GetWindowRect(pageWnd[_info_page],&rect);
	rect.bottom += 38;
	TabCtrl_AdjustRect(hTab,true,&rect);
	//MoveWindow(pageWnd[_info_page],7,rect.top+21,rect.right-tabRect.left-7,tabRect.bottom-tabRect.top-7,true);
	//ShowWindow(pageWnd[_info_page],SW_SHOW);


	//计算窗口的大小，并调节main窗口大小
	width = rect.right - rect.left;
	height = rect.bottom - rect.top;
	SetWindowPos(hMain,NULL,0,0,width,height,SWP_NOMOVE|SWP_NOZORDER);
	MoveWindow(hTab,0,0,width,height,TRUE);
	MoveWindow(pageWnd[_info_page],0,25,width,height,TRUE);
	ShowWindow(pageWnd[_info_page],SW_SHOW);
}

INT_PTR CALLBACK INFO_DIALOG::DlgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	RECT pageRect;
	HDC hdc;
	HBRUSH hBrush;
	switch (uMsg)
	{
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		GetClientRect(hWnd, &pageRect);
		hBrush = WHITE_BRUSH;
		FillRect(hdc,&pageRect,hBrush);
		SetBkColor(hdc,0x000000);
		EndPaint(hWnd,&ps);
		break;
	case WM_INITDIALOG:
		//初始化page1页面中的控件
		//----调整groupbox的大小
		break;
	default:
		return false;
	}
	return true;
}
#endif
