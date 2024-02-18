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
    clubs.push_back(TEXT("Милан Италия"));
    clubs.push_back(TEXT("Ливерпуль Англия"));
    clubs.push_back(TEXT("Бавария Германия"));
    clubs.push_back(TEXT("Барселона Испания"));
    clubs.push_back(TEXT("Арсенал Англия"));
    clubs.push_back(TEXT("Лион Франция"));
    clubs.push_back(TEXT("Интер Италия"));
    clubs.push_back(TEXT("Реал Испания"));

    // получим дескрипторы элементов управления
    hList1 = GetDlgItem(hwnd, IDC_LIST1);
    hList2 = GetDlgItem(hwnd, IDC_LIST2);
    hEdit1 = GetDlgItem(hwnd, IDC_EDIT1);
    hEdit2 = GetDlgItem(hwnd, IDC_EDIT2);
    hEdit3 = GetDlgItem(hwnd, IDC_EDIT3);

    for (const auto& club : clubs) {
        SendMessage(hList1, LB_ADDSTRING, 0, reinterpret_cast<LPARAM>(club.c_str()));
    }

    // добавим 8 элементов в список с единичным выбором
    /*SendMessage(hList1, LB_ADDSTRING, 0, LPARAM(TEXT("Милан Италия")));
    SendMessage(hList1, LB_ADDSTRING, 0, LPARAM(TEXT("Ливерпуль Англия")));
    SendMessage(hList1, LB_ADDSTRING, 0, LPARAM(TEXT("Бавария Германия")));
    SendMessage(hList1, LB_ADDSTRING, 0, LPARAM(TEXT("Барселона Испания")));
    SendMessage(hList1, LB_ADDSTRING, 0, LPARAM(TEXT("Арсенал Англия")));
    SendMessage(hList1, LB_ADDSTRING, 0, LPARAM(TEXT("Лион Франция")));
    SendMessage(hList1, LB_ADDSTRING, 0, LPARAM(TEXT("Интер Италия")));
    SendMessage(hList1, LB_ADDSTRING, 0, LPARAM(TEXT("Реал Испания")));*/

    // установим ширину колонки для списка с множественным выбором
    SendMessage(hList2, LB_SETCOLUMNWIDTH, 170, 0);

    // добавим 8 элементов в список с множественным выбором
    SendMessage(hList2, LB_ADDSTRING, 0, LPARAM(TEXT("Рома Италия")));
    SendMessage(hList2, LB_ADDSTRING, 0, LPARAM(TEXT("Манчестер Юнайтед Англия")));
    SendMessage(hList2, LB_ADDSTRING, 0, LPARAM(TEXT("Вердер Германия")));
    SendMessage(hList2, LB_ADDSTRING, 0, LPARAM(TEXT("Валенсия Испания")));
    SendMessage(hList2, LB_ADDSTRING, 0, LPARAM(TEXT("Челси Англия")));
    SendMessage(hList2, LB_ADDSTRING, 0, LPARAM(TEXT("Марсель Франция")));
    SendMessage(hList2, LB_ADDSTRING, 0, LPARAM(TEXT("Ювентус Италия")));
    SendMessage(hList2, LB_ADDSTRING, 0, LPARAM(TEXT("Атлетико Испания")));
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
                MessageBox(hwnd, TEXT("Такой клуб уже существует!"), TEXT("Добавление клуба"), MB_OK | MB_ICONSTOP);
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
            MessageBox(hwnd, buffer.data(), TEXT("Удаление клуба"), MB_OK | MB_ICONINFORMATION);
            SendMessage(hList1, LB_DELETESTRING, index, 0);
        }
        else
            MessageBox(hwnd, TEXT("Клуб не выбран!"), TEXT("Удаление клуба"), MB_OK | MB_ICONSTOP);
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
                MessageBox(hwnd, TEXT("Клуб не найден!"), TEXT("Поиск клуба"), MB_OK | MB_ICONSTOP);
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
            MessageBox(hwnd, buffer.data(), TEXT("Список с множественным выбором"), MB_OK | MB_ICONINFORMATION);
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
            MessageBox(hwnd, TEXT("Клуб не выбран!"), TEXT("Редактирование клуба"), MB_OK | MB_ICONSTOP);
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
