#include "DlgBoxTempalate.h"


DlgBoxTempalate::DlgBoxTempalate(HINSTANCE hInstance, LPCSTR dlgResName, HWND hwndParent) {
	CreateDlg(hInstance, dlgResName, hwndParent);
}

DlgBoxTempalate::~DlgBoxTempalate(void) {

}

void DlgBoxTempalate::CreateDlg(HINSTANCE hInstance, LPCSTR dlgResName, HWND parent) {
	m_hwnd = CreateDialog(hInstance, dlgResName, parent, (DLGPROC)StDlgProc); // создали диалог
	SetWindowLongPtr(m_hwnd, GWLP_USERDATA, (LONG_PTR)this); // записали в его свойства адрес нашего класса диалога
}

LRESULT CALLBACK DlgBoxTempalate::StDlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	DlgBoxTempalate* pDlgTempalate = NULL;
	pDlgTempalate = (DlgBoxTempalate*)GetWindowLongPtr(hwnd, GWLP_USERDATA); // получаем из свойств диалога адрес класса диалога
	if (pDlgTempalate != NULL)
	{
		// если адрес был получен корректно то мы просто вызываем реальную диалоговую процедуру
		return pDlgTempalate->RealDlgProc(hwnd, uMsg, wParam, lParam);
	}
	return 0;
}

void DlgBoxTempalate::Show(int nCmdShow) {
	ShowWindow(m_hwnd, nCmdShow);
}

// описываем реальный диалоговый процесс
LRESULT DlgBoxTempalate::RealDlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg)
	{
	case WM_INITDIALOG:
		break;
	case WM_CLOSE:
		EndDialog(hwnd, wParam);
		PostQuitMessage(0);
		break;
	}
	return 0;
}