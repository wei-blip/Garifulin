#include "MainDlg.h"

MainDlg::MainDlg(HINSTANCE hInstance, LPCSTR dlgResName, HWND hwndParent) : 
	DlgBoxTempalate(hInstance, dlgResName, hwndParent){
	OnCreate();
}

void MainDlg::OnCreate() {
	pointA = new EditBox(m_hwnd, IDC_EDIT1);
	pointB = new EditBox(m_hwnd, IDC_EDIT2);
	m_path = new EditBox(m_hwnd, IDC_EDIT3);
}

LRESULT MainDlg::RealDlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg)
	{
	case WM_COMMAND :
		if (wParam == IDCALC)
		{
			if ((pointA->GetText() == NULL) || (pointB->GetText() == NULL)) {
				MessageBox(m_hwnd, "Заполните все поля", "Error", MB_OK);
			}
			else if (MessageBox(m_hwnd, "Calculation started", "Calculation started", MB_OK) == IDOK) {
				std::string str = Run(m_path->GetText());
				const char* c1 = str.c_str();			//	преобразовываем к указателю на массив строк
				MessageBox(m_hwnd, c1 , "Calculation is over", MB_OK);
			}
		}
		break;
	}
	return DlgBoxTempalate::RealDlgProc(hwnd, uMsg, wParam, lParam);
}

MainDlg::~MainDlg(void) {

}

