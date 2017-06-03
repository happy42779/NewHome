#pragma once
#ifndef _MAIN_DIALOG_H_
#define _MAIN_DIALOG_H_

#include "precompiler.h"
#include "BASIC_DIALOG.h"
#include "ADD_DIALOG.h"
#include "INFO_DIALOG.h"

class MAIN_DIALOG;
extern MAIN_DIALOG* pMainDlg;

class MAIN_DIALOG:public BASIC_DIALOG
{
public:
	MAIN_DIALOG();
	~MAIN_DIALOG();
public:
	//回调函数
	static INT_PTR CALLBACK DlgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	//初始化tab
	static BOOL InitTab(HWND hParent);
	//切换tab的时候，调整窗口大小
	VOID AdjustWindow(int& index);

public:	//控件句柄
	//static HWND hTab;	//WM_Init中需要用到，因为此时指针还没有指向构造函数返回的对象 -- 已经作为全局变量
};

MAIN_DIALOG::MAIN_DIALOG()
{
	RECT rect;
	hWndCtrl = CreateDialogParam(g_hInstance,MAKEINTRESOURCE(IDD_DIALOG_MAIN),NULL,DlgProc,NULL);
	if(NULL == hWndCtrl)
	{
		LastError();
		ExitProcess(0);
	}
	GetClientRect(hWndCtrl,&rect);
	width = rect.right - rect.left;
	height = rect.bottom - rect.top+38;
	MoveWindow(hWndCtrl,(x-width)>>1,(y-height)>>1,width,height,TRUE);
	UpdateWindow(hWndCtrl);
	ShowWindow(hWndCtrl,SW_SHOW);
}

INT_PTR CALLBACK MAIN_DIALOG::DlgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int nIndex;
	RECT tabRect;
	HDC hdc;
	HBRUSH hbr;

	switch(uMsg)
	{
	case WM_NOTIFY:
		switch(((LPNMHDR)lParam)->code)
		{
		case TCN_SELCHANGING:
 			nIndex = TabCtrl_GetCurSel(hTab);
			ShowWindow(pageWnd[nIndex],SW_HIDE);
			break;
		case TCN_SELCHANGE:
			nIndex = TabCtrl_GetCurSel(hTab);
			pMainDlg->AdjustWindow(nIndex);
			ShowWindow(pageWnd[nIndex],SW_SHOW);
			break;
		}
		break;
	case WM_COMMAND:
		break;
	case WM_INITDIALOG:
		InitTab(hWnd);
		break;
	case WM_CLOSE:
		if(!DestroyWindow(hWnd))
			LastError();
		break;
	case WM_DESTROY:	//必须加上这里
		PostQuitMessage(0);
	default:
		return false;
	}
	return true;
}


BOOL MAIN_DIALOG::InitTab(HWND hParent)
{
	TC_ITEM tci;
	tci.mask = TCIF_TEXT;
	//-----保存tab句柄--------
	hTab = GetDlgItem(hParent,IDC_TAB);
	if(hTab == NULL)
	{
		LastError();
		return false;	
	}
	//-------插入tab选项，并创建page----------
	for(int i = 0; i < 3; i++)
	{
		tci.pszText = tabName[i];
		TabCtrl_InsertItem(hTab,i,&tci);
	}
	//AddPage(0,Page1Proc,IDD_DIALOG_GENEINFO);
	//AddPage(1,Page2Proc,IDD_DIALOG_ADD);
	//AddPage(2,Page3Proc,IDD_DIALOG_SEARCH);

	//---显示第一个页面---
	TabCtrl_SetCurSel(hTab,0);
	ShowWindow(pageWnd[0],SW_SHOW);

	return true;
}

VOID MAIN_DIALOG::AdjustWindow(int& index)
{
	BASIC_DIALOG* pWnd = NULL;
	RECT rect;

	//计算被选中的窗口
	if(0 == index)
	{
		pWnd = pInfoDlg;
	}
	else if (1 == index)
	{
		pWnd = pAddDlg;
	}

	//调整tab的大小
	GetWindowRect(pageWnd[index],&rect);
	rect.bottom+=40;
	TabCtrl_AdjustRect(hTab,TRUE,&rect);
	
	//调整main窗口的大小
 	SetWindowPos(hMain,NULL,0,0,pWnd->width,pWnd->height,SWP_NOMOVE|SWP_NOZORDER);
	MoveWindow(hTab,0,0,pWnd->width,pWnd->height,TRUE);	//调整完大小还需要移动tab的位置
	MoveWindow(pageWnd[index],0,24,pWnd->width,pWnd->height,TRUE);
}

#endif
