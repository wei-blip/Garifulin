#include "MainDlg.h"

MainDlg::MainDlg(HINSTANCE hInstance, LPCSTR dlgResName, HWND hwndParent) : 
	DlgBoxTempalate(hInstance, dlgResName, hwndParent){
	OnCreate();
}

void MainDlg::OnCreate() {
	pointA = new EditBox(m_hwnd, IDC_EDIT1);
	pointB = new EditBox(m_hwnd, IDC_EDIT2);
}

LRESULT MainDlg::RealDlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg)
	{
	case WM_COMMAND :
		if (wParam == IDCALC)
		{
			if ((pointA->GetText() == NULL) || (pointB->GetText() == NULL)) {
				MessageBox(m_hwnd, "Заполните все поля", "Ошибка", MB_ICONERROR);
			}
			else if (MessageBox(m_hwnd, "Расчёт начат", "Статус", MB_OK) == IDOK) {
				std::string str = Run( "C:\\Users\\user\\Desktop\\input_data.txt" );
				const char* c1 = str.c_str();			//	преобразовываем к указателю на массив строк
				MessageBox(m_hwnd, c1 , "Статус", MB_OK);
			}
		}
		break;
	}
	return DlgBoxTempalate::RealDlgProc(hwnd, uMsg, wParam, lParam);
}

MainDlg::~MainDlg(void) {

}

