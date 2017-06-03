#include "precompiler.h"
#include "MAIN_DIALOG.h"
#include "INFO_DIALOG.h"
#include "ADD_DIALOG.h"

HINSTANCE g_hInstance = NULL;
MAIN_DIALOG* pMainDlg = NULL;
INFO_DIALOG* pInfoDlg = NULL;
ADD_DIALOG* pAddDlg = NULL;

HWND hMain = NULL;
HWND hTab;
HWND pageWnd[7];
WCHAR tabName[7][24]={L"人员概况",L"新添信息",L"人员查找"};


/************************************************************************
*选项卡1上的空间初始化和按钮响应 
************************************************************************
INT_PTR CALLBACK Page1Proc(HWND hWnd,UINT uMsg, WPARAM wParam, LPARAM lParam)
{	
	
}

/************************************************************************
*选项卡2上的空间初始化和按钮响应 
************************************************************************
INT_PTR CALLBACK Page2Proc(HWND hWnd,UINT uMsg, WPARAM wParam, LPARAM lParam)
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
		//UpdateWindow(hWnd);
		EndPaint(hWnd,&ps);
		break;
	case WM_INITDIALOG:
		//初始化page1页面中的控件
		break;
	default:
		return false;
	}
	return true;
}

/************************************************************************
*选项卡3上的空间初始化和按钮响应 
************************************************************************
INT_PTR CALLBACK Page3Proc(HWND hWnd,UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	RECT pageRect;
	HDC hdc;
	HBRUSH hBrush;
	switch (uMsg)
	{
	case WM_PAINT:
		hdc = BeginPaint(hWnd,&ps);
		GetClientRect(hWnd, &pageRect);
		hBrush = CreateSolidBrush(0xC7EDCC);
		FillRect(hdc,&pageRect,hBrush);
		SetBkColor(hdc,0xC7EDCC);
		DeleteObject(hBrush);
		//UpdateWindow(hWnd);
		EndPaint(hWnd,&ps);
		break;
	case WM_INITDIALOG:
		//初始化page1页面中的控件
		break;
	default:
		return false;
	}
	return true;
}

/************************************************************************
* 为每一个tab创建一个page
************************************************************************
void AddPage(int index, DLGPROC pageProc,DWORD id)
{
	RECT tabRect;
	
	pageWnd[index] = CreateDialogParam(g_hInstance,MAKEINTRESOURCE(id),hTab,(DLGPROC)pageProc,NULL);
	if(NULL == pageWnd[index])
		LastError();
	//UpdateWindow(pageWnd[index]);
	//ShowWindow(pageWnd[index],SW_SHOW);
	GetWindowRect(hTab,&tabRect);
	TabCtrl_AdjustRect(hTab,true,&tabRect);
	MoveWindow(pageWnd[index],2,tabRect.top+2,tabRect.right,tabRect.bottom ,true);
}


INT_PTR CALLBACK DlgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
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
			//hbr = (HBRUSH)COLOR_WINDOW;
			//hdc = GetDC(hTab);
			//TabCtrl_GetItemRect(hTab,nIndex,&tabRect);
			//FillRect(hdc,&tabRect,hbr);
			//SetBkColor(hdc,RGB(GetRValue(COLOR_WINDOW),GetGValue(COLOR_WINDOW),GetBValue(COLOR_WINDOW)));
			ShowWindow(pageWnd[nIndex],SW_HIDE);
			break;
		case TCN_SELCHANGE:
			nIndex = TabCtrl_GetCurSel(hTab);
			//---更改第一个tab的背景颜色
			//TabCtrl_GetItemRect(hTab,nIndex,&tabRect);
			//hdc = GetDC(hTab);
			//hbr = (HBRUSH)BLACK_BRUSH;
			//FillRect(hdc,&tabRect,hbr);
			//SetBkColor(hdc,0xffffff);

			ShowWindow(pageWnd[nIndex],SW_SHOW);
			break;
		}
		break;
	//case WM_ERASEBKGND:
	//	if(hWnd == hTab)
	//	{
	//		GetClientRect(hWnd,&tabRect);
	//		FillRect((HDC)wParam,&tabRect,WHITE_BRUSH);
	//		UpdateWindow(hWnd);
	//		return true;
	//	}
	//	return false;
	case WM_SIZE:	//调整大小
		MoveWindow(hTab,0,0,LOWORD(lParam),HIWORD(lParam),TRUE);
		GetClientRect(hTab,&tabRect);
		TabCtrl_AdjustRect(hTab,false,&tabRect);
		for(int i = 0; i < TabCtrl_GetItemCount(hTab); i++)
			MoveWindow(pageWnd[i],2,tabRect.top+2,tabRect.right,tabRect.bottom,true);
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
*/

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd )
{
	MSG msg;

	g_hInstance = hInstance;

	//主窗口 及 tabcontrol
	pMainDlg = new MAIN_DIALOG();
	hMain = pMainDlg->hWndCtrl;
	
	//信息页面
	pInfoDlg = new INFO_DIALOG;

	//添加人员页面
	pAddDlg = new ADD_DIALOG;

	while(GetMessage(&msg,NULL,NULL,NULL))
	{
		//if(!IsDialogMessage(g_hWnd,&msg))
		//{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		//}
	}

	return 0;
}