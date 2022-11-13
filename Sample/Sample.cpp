#include <windows.h>
#include <windowsX.h>
#include <tchar.h>
#include <commctrl.h>
#include "resource.h"
#include <time.h>


#pragma comment(lib,"comctl32")

#pragma warning(disable : 4996)

BOOL CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPTSTR lpszCmdLine, int nCmdShow)
{
	return DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, (DLGPROC)DlgProc);
}

HWND hList;
HWND hButton;
HWND hRadioButton[3];
HWND hEditControl;

const int ELEMENTS = 20;


BOOL CALLBACK DlgProc(HWND hWnd, UINT message, WPARAM wp, LPARAM lp)
{
	srand(time(NULL));
	switch (message)
	{
	case WM_CLOSE:
		EndDialog(hWnd, 0);
		return TRUE;

	case  WM_INITDIALOG: {
		//Getting descriptors
		hList = GetDlgItem(hWnd, IDC_LIST1);
		hButton = GetDlgItem(hWnd, IDC_BUTTON1);
		hEditControl = GetDlgItem(hWnd, IDC_EDIT1);
		for (int i = 0; i < 3; i++)
			hRadioButton[i] = GetDlgItem(hWnd, IDC_RADIO1+i);
		return TRUE;
	}

	case WM_COMMAND: {
		
		if (LOWORD(wp) == IDCLOSE) {
			SendMessage(hWnd, WM_CLOSE, 0, 0);
		}
		if (LOWORD(wp) == IDC_BUTTON1) {
			SendMessage(hList, LB_RESETCONTENT, 0, 0);					//Clear the list before generating a new one.
			SetWindowText(hEditControl, TEXT(" "));
			int random;
			TCHAR buffer[5];
			for (int i = 0; i < ELEMENTS; i++)
			{
				random = rand() % (-21 - 21) + -21;
				if (random == 0) {
					i--;
				}
				else {
					wsprintf(buffer, TEXT("%d"),random);
					SendMessage(hList,LB_ADDSTRING, 0, LPARAM(buffer));
				}
					
			}
		}
		if (LOWORD(wp) == IDC_RADIO1) { // Sum of numbers
			int sum = 0;
			TCHAR tchar[5];
			for (int i = 0; i < ELEMENTS; i++)
			{
				SendMessage(hList, LB_GETTEXT, i, (LPARAM)(LPCTSTR)(tchar));
				sum += _wtoi(tchar);
			}
			wsprintf(tchar, TEXT("%d"), sum);
			SetWindowText(hEditControl,tchar);
		}

		if (LOWORD(wp) == IDC_RADIO2) { // Product number
			long long product = 1;
			TCHAR tchar[16];
			for (int i = 0; i < ELEMENTS; i++)
			{
				SendMessage(hList, LB_GETTEXT, i, (LPARAM)(LPCTSTR)(tchar));
				product *= _wtoi(tchar);
			}
			wsprintf(tchar, TEXT("%d"), product);
			SetWindowText(hEditControl, tchar);
		} 

		if (LOWORD(wp) == IDC_RADIO3) { // Average
			double sum = 0;
			TCHAR tchar[16];
			for (int i = 0; i < ELEMENTS; i++)
			{
				SendMessage(hList, LB_GETTEXT, i, (LPARAM)(LPCTSTR)(tchar));
				sum += _wtoi(tchar);
			}
			swprintf(tchar, TEXT("%.2f"), (sum/ELEMENTS));
			SetWindowText(hEditControl, tchar);
		}
		return TRUE;
	}

		return TRUE;

	}


	return FALSE;
}