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
		if (wParam == IDCALC) // если нажато ОК то начинается расчёт
		{
			if ((pointA->GetText() == NULL) || (pointB->GetText() == NULL)) { // это для того чтобы была информация о точках между которыми ведётся расчёт
				MessageBox(m_hwnd, "Заполните все поля", "Ошибка", MB_ICONERROR);
			}
			else if (MessageBox(m_hwnd, "Расчёт начат", "Статус", MB_OK) == IDOK) { 
				CalcParam Param("C:\\Users\\user\\Desktop\\input_data.txt",
					pointA->GetText(), pointB->GetText());
				 std::string str =  Param.PrintAngles();			//	преобразовываем к указателю на массив строк
				 const char* c1 = str.c_str();
				 MessageBox(m_hwnd, c1 , "Статус", MB_OK);
			}
		}
		break;
	}
	return DlgBoxTempalate::RealDlgProc(hwnd, uMsg, wParam, lParam);
}

MainDlg::~MainDlg(void) {

}

