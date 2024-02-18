#include "UsingListboxDlg.h"
#include <iostream>
#include <vector>	
#include <string>	

UsingListboxDlg* UsingListboxDlg::ptr = NULL;

UsingListboxDlg::UsingListboxDlg(void)
{
    ptr = this;

}

void UsingListboxDlg::Cls_OnClose(HWND hwnd)
{
    EndDialog(hwnd, 0);

}

BOOL UsingListboxDlg::Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
{
    //std::vector<std::wstring> clubVector;	
    clubs.push_back(TEXT("����� ������"));
    clubs.push_back(TEXT("��������� ������"));
    clubs.push_back(TEXT("������� ��������"));
    clubs.push_back(TEXT("��������� �������"));
    clubs.push_back(TEXT("������� ������"));
    clubs.push_back(TEXT("���� �������"));
    clubs.push_back(TEXT("����� ������"));
    clubs.push_back(TEXT("���� �������"));

    // ������� ����������� ��������� ����������
    hList1 = GetDlgItem(hwnd, IDC_LIST1);
    hList2 = GetDlgItem(hwnd, IDC_LIST2);
    hEdit1 = GetDlgItem(hwnd, IDC_EDIT1);
    hEdit2 = GetDlgItem(hwnd, IDC_EDIT2);
    hEdit3 = GetDlgItem(hwnd, IDC_EDIT3);

    for (const auto& club : clubs) {
        SendMessage(hList1, LB_ADDSTRING, 0, reinterpret_cast<LPARAM>(club.c_str()));
    }

    // ������� 8 ��������� � ������ � ��������� �������
    /*SendMessage(hList1, LB_ADDSTRING, 0, LPARAM(TEXT("����� ������")));
    SendMessage(hList1, LB_ADDSTRING, 0, LPARAM(TEXT("��������� ������")));
    SendMessage(hList1, LB_ADDSTRING, 0, LPARAM(TEXT("������� ��������")));
    SendMessage(hList1, LB_ADDSTRING, 0, LPARAM(TEXT("��������� �������")));
    SendMessage(hList1, LB_ADDSTRING, 0, LPARAM(TEXT("������� ������")));
    SendMessage(hList1, LB_ADDSTRING, 0, LPARAM(TEXT("���� �������")));
    SendMessage(hList1, LB_ADDSTRING, 0, LPARAM(TEXT("����� ������")));
    SendMessage(hList1, LB_ADDSTRING, 0, LPARAM(TEXT("���� �������")));*/

    // ��������� ������ ������� ��� ������ � ������������� �������
    SendMessage(hList2, LB_SETCOLUMNWIDTH, 170, 0);

    // ������� 8 ��������� � ������ � ������������� �������
    SendMessage(hList2, LB_ADDSTRING, 0, LPARAM(TEXT("���� ������")));
    SendMessage(hList2, LB_ADDSTRING, 0, LPARAM(TEXT("��������� ������� ������")));
    SendMessage(hList2, LB_ADDSTRING, 0, LPARAM(TEXT("������ ��������")));
    SendMessage(hList2, LB_ADDSTRING, 0, LPARAM(TEXT("�������� �������")));
    SendMessage(hList2, LB_ADDSTRING, 0, LPARAM(TEXT("����� ������")));
    SendMessage(hList2, LB_ADDSTRING, 0, LPARAM(TEXT("������� �������")));
    SendMessage(hList2, LB_ADDSTRING, 0, LPARAM(TEXT("������� ������")));
    SendMessage(hList2, LB_ADDSTRING, 0, LPARAM(TEXT("�������� �������")));
    return TRUE;
}

void UsingListboxDlg::Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
    switch (id)
    {
    case IDC_ADD:
        // add club name to the list
    {
        int length = GetWindowTextLength(hEdit1);
        std::vector<TCHAR> buffer(length + 1);
        GetWindowText(hEdit1, buffer.data(), length + 1);
        if (length > 0)
        {
            int index = SendMessage(hList1, LB_FINDSTRINGEXACT, -1, reinterpret_cast<LPARAM>(buffer.data()));
            if (index == LB_ERR)
                SendMessage(hList1, LB_ADDSTRING, 0, reinterpret_cast<LPARAM>(buffer.data()));
            else
                MessageBox(hwnd, TEXT("����� ���� ��� ����������!"), TEXT("���������� �����"), MB_OK | MB_ICONSTOP);
        }
    }
    break;
    case IDC_DEL:
        // delete selected club from the list
    {
        int index = SendMessage(hList1, LB_GETCURSEL, 0, 0);
        if (index != LB_ERR)
        {
            int length = SendMessage(hList1, LB_GETTEXTLEN, index, 0);
            std::vector<TCHAR> buffer(length + 1);
            SendMessage(hList1, LB_GETTEXT, index, reinterpret_cast<LPARAM>(buffer.data()));
            MessageBox(hwnd, buffer.data(), TEXT("�������� �����"), MB_OK | MB_ICONINFORMATION);
            SendMessage(hList1, LB_DELETESTRING, index, 0);
        }
        else
            MessageBox(hwnd, TEXT("���� �� ������!"), TEXT("�������� �����"), MB_OK | MB_ICONSTOP);
    }
    break;
    case IDC_FIND:
    {
        int length = GetWindowTextLength(hEdit2);
        std::vector<TCHAR> buffer(length + 1);
        GetWindowText(hEdit2, buffer.data(), length + 1);
        if (length > 0)
        {
            int index = SendMessage(hList1, LB_SELECTSTRING, -1, reinterpret_cast<LPARAM>(buffer.data()));
            if (index == LB_ERR)
                MessageBox(hwnd, TEXT("���� �� ������!"), TEXT("����� �����"), MB_OK | MB_ICONSTOP);
        }
    }
    break;
    case IDC_DELALL:
        SendMessage(hList1, LB_RESETCONTENT, 0, 0);
        break;
    case IDC_GETSELITEMS:
        // get selected items from the list with multiple selection
    {
        int nCount = SendMessage(hList2, LB_GETSELCOUNT, 0, 0);
        std::vector<int> selectedItems(nCount);
        SendMessage(hList2, LB_GETSELITEMS, nCount, reinterpret_cast<LPARAM>(selectedItems.data()));
        for (int i : selectedItems)
        {
            int length = SendMessage(hList2, LB_GETTEXTLEN, i, 0);
            std::vector<TCHAR> buffer(length + 1);
            SendMessage(hList2, LB_GETTEXT, i, reinterpret_cast<LPARAM>(buffer.data()));
            MessageBox(hwnd, buffer.data(), TEXT("������ � ������������� �������"), MB_OK | MB_ICONINFORMATION);
        }
    }
    break;
    case IDC_FIND2:
    {
        int ind2 = SendMessage(hList1, LB_GETCURSEL, 0, 0);
        if (ind2 != LB_ERR) {
            int length = GetWindowTextLength(hEdit3);
            std::vector<TCHAR> buffer(length + 1);
            GetWindowText(hEdit3, buffer.data(), length + 1);
            if (length > 0) {
                SendMessage(hList1, LB_DELETESTRING, ind2, 0);
                SendMessage(hList1, LB_INSERTSTRING, ind2, reinterpret_cast<LPARAM>(buffer.data()));
            }
        }
        else
            MessageBox(hwnd, TEXT("���� �� ������!"), TEXT("�������������� �����"), MB_OK | MB_ICONSTOP);
    }
    break;
    }
    if (id == IDC_LIST1 && codeNotify == LBN_SELCHANGE)
    {
        int index = SendMessage(hList1, LB_GETCURSEL, 0, 0);
        if (index != LB_ERR)
        {
            int length = SendMessage(hList1, LB_GETTEXTLEN, index, 0);
            std::vector<TCHAR> buffer(length + 1);
            SendMessage(hList1, LB_GETTEXT, index, reinterpret_cast<LPARAM>(buffer.data()));
            SetWindowText(hwnd, buffer.data());
        }
    }
}

void UsingListboxDlg::Cls_OnClose(HWND hwnd)    
{
    EndDialog(hwnd, 0);
}
