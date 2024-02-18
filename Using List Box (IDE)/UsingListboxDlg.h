#pragma once
#include "header.h"
#include <vector>	
#include <string>	

class UsingListboxDlg
{
private:
	std::vector<std::wstring> clubs;
public:
	UsingListboxDlg(void);


	static BOOL CALLBACK DlgProc(HWND hWnd, UINT mes, WPARAM wp, LPARAM lp);

	static UsingListboxDlg* ptr;
	HWND hDialog, hEdit1, hEdit2, hEdit3, hList1, hList2;

	BOOL Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam);
	void Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);
	void Cls_OnClose(HWND hwnd);
};
