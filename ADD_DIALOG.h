#pragma once

#ifndef _ADD_DIALOG_H_
#define _ADD_DIALOG_H_

#include "precompiler.h"

class ADD_DIALOG;
extern ADD_DIALOG* pAddDlg;

class ADD_DIALOG: public BASIC_DIALOG
{
public:
	ADD_DIALOG();
	~ADD_DIALOG();
public:
	static INT_PTR CALLBACK DlgProc(HWND hDlg, UINT uMsg, WPARAM wParma, LPARAM lParam);
public:	//控件
	HWND hEdit_name;
	HWND hEdit_age;
	HWND hCombo_gender;
	HWND hEdit_nation;
	HWND hDtp_DOB;
	HWND hEdit_Ethnic;
	HWND hEdit_addr;
	HWND hEdit_profn;
	HWND hEdit_pro_note;
	HWND hEdit_specialty;
	HWND hEdit_tel;
	HWND hEdit_mob;
	HWND hEdit_QQ;
	HWND hEdit_wechat;
	HWND hEdit_email;
	HWND hEdit_need_cont;
	HWND hEdit_need_type;
	HWND hEdit_serv_cont;
	HWND hEdit_serv_type;
	HWND hDtp_need_from;
	HWND hDtp_need_to;
	HWND hDtp_serv_from;
	HWND hDtp_serv_to;
	HWND hBtn_add_need;
	HWND hBtn_add_serv;
	HWND hChk_type_party;
	HWND hChk_type_resi;
	HWND hChk_type_vol;
	HWND hChk_type_donor;
	HWND hChk_type_partner;
	HWND hChk_type_officer;
	HWND hChk_type_worker;
};

//创建窗口，并记录好窗口的大小，在切换tab的时候进行大小调整
ADD_DIALOG::ADD_DIALOG()
	:hEdit_name(NULL),
	hEdit_age(NULL),
	hCombo_gender(NULL),
	hEdit_nation(NULL),
	hDtp_DOB(NULL),
	hEdit_Ethnic(NULL),
	hEdit_addr(NULL),
	hEdit_profn(NULL),
	hEdit_pro_note(NULL),
	hEdit_specialty(NULL),
	hEdit_tel(NULL),
	hEdit_mob(NULL),
	hEdit_QQ(NULL),
	hEdit_wechat(NULL),
	hEdit_email(NULL),
	hEdit_need_cont(NULL),
	hEdit_need_type(NULL),
	hEdit_serv_cont(NULL),
	hEdit_serv_type(NULL),
	hDtp_need_from(NULL),
	hDtp_need_to(NULL),
	hDtp_serv_from(NULL),
	hDtp_serv_to(NULL),
	hBtn_add_need(NULL),
	hBtn_add_serv(NULL),
	hChk_type_party(NULL),
	hChk_type_resi(NULL),
	hChk_type_vol(NULL),
	hChk_type_donor(NULL),
	hChk_type_partner(NULL),
	hChk_type_officer(NULL),
	hChk_type_worker(NULL)
{
	RECT rect;
	//创建窗口
	pageWnd[_add_page] = CreateDialogParam(g_hInstance,MAKEINTRESOURCE(IDD_DIALOG_ADD),hTab,DlgProc,NULL);
	if(NULL == pageWnd[_add_page])
	{
		LastError();
	}
	
	//获取page大小并记录下来
	GetWindowRect(pageWnd[_add_page],&rect);
	width = rect.right - rect.left;
	height = rect.bottom - rect.top+40;
}

INT_PTR CALLBACK ADD_DIALOG::DlgProc(HWND hDlg, UINT uMsg, WPARAM wParma, LPARAM lParam)
{
	PAINTSTRUCT ps;
	switch (uMsg)
	{
	case WM_PAINT:
		BeginPaint(hDlg,&ps);
		EndPaint(hDlg,&ps);
		break;
	case WM_COMMAND:
		break;
	case WM_INITDIALOG:
		break;
	default:
		return false;
	}
	return true;
}

#endif
