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
	//�ص�����
	static INT_PTR CALLBACK DlgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	//��ʼ��tab
	static BOOL InitTab(HWND hParent);
	//�л�tab��ʱ�򣬵������ڴ�С
	VOID AdjustWindow(int& index);

public:	//�ؼ����
	//static HWND hTab;	//WM_Init����Ҫ�õ�����Ϊ��ʱָ�뻹û��ָ���캯�����صĶ��� -- �Ѿ���Ϊȫ�ֱ���
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
	case WM_DESTROY:	//�����������
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
	//-----����tab���--------
	hTab = GetDlgItem(hParent,IDC_TAB);
	if(hTab == NULL)
	{
		LastError();
		return false;	
	}
	//-------����tabѡ�������page----------
	for(int i = 0; i < 3; i++)
	{
		tci.pszText = tabName[i];
		TabCtrl_InsertItem(hTab,i,&tci);
	}
	//AddPage(0,Page1Proc,IDD_DIALOG_GENEINFO);
	//AddPage(1,Page2Proc,IDD_DIALOG_ADD);
	//AddPage(2,Page3Proc,IDD_DIALOG_SEARCH);

	//---��ʾ��һ��ҳ��---
	TabCtrl_SetCurSel(hTab,0);
	ShowWindow(pageWnd[0],SW_SHOW);

	return true;
}

VOID MAIN_DIALOG::AdjustWindow(int& index)
{
	BASIC_DIALOG* pWnd = NULL;
	RECT rect;

	//���㱻ѡ�еĴ���
	if(0 == index)
	{
		pWnd = pInfoDlg;
	}
	else if (1 == index)
	{
		pWnd = pAddDlg;
	}

	//����tab�Ĵ�С
	GetWindowRect(pageWnd[index],&rect);
	rect.bottom+=40;
	TabCtrl_AdjustRect(hTab,TRUE,&rect);
	
	//����main���ڵĴ�С
 	SetWindowPos(hMain,NULL,0,0,pWnd->width,pWnd->height,SWP_NOMOVE|SWP_NOZORDER);
	MoveWindow(hTab,0,0,pWnd->width,pWnd->height,TRUE);	//�������С����Ҫ�ƶ�tab��λ��
	MoveWindow(pageWnd[index],0,24,pWnd->width,pWnd->height,TRUE);
}

#endif
