#include "MainDlg.h"

OPENFILENAME ofn; // ��������� ������� �������� �����
char szFile[260]; // ����� ��� ����� �����
HWND hwnd; // ���� - ��������
HANDLE hf; // ���������� �����

MainDlg::MainDlg(HINSTANCE hInstance, LPCSTR dlgResName, HWND hwndParent) :
	DlgBoxTempalate(hInstance, dlgResName, hwndParent) {
	OnCreate();
}

void MainDlg::OnCreate() {
	pointA = new EditBox(m_hwnd, IDC_EDIT1);
	pointB = new EditBox(m_hwnd, IDC_EDIT2);
}

LRESULT MainDlg::RealDlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

	// ��������� OPENFILENAME
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = hwnd;
	ofn.lpstrFile = szFile;
	ofn.nMaxFile = sizeof(szFile);
	ofn.lpstrFilter = "All\0*.*\0Text\0*.TXT\0";
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = NULL;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	switch (uMsg)
	{
	case WM_COMMAND:
		if (wParam == IDCALC)
		{
			if (GetOpenFileName(&ofn) == TRUE)
				hf = CreateFile(ofn.lpstrFile, GENERIC_READ,
					0, (LPSECURITY_ATTRIBUTES)NULL,
					OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL,
					(HANDLE)NULL);

			if ((pointA->GetText() == NULL) || (pointB->GetText() == NULL)) {
				MessageBox(m_hwnd, "��������� ��� ����", "������", MB_ICONERROR);
			}
			else if (MessageBox(m_hwnd, "������ �����", "������", MB_OK) == IDOK) {
				std::string str = Run("C:\\Users\\user\\Desktop\\input_data.txt");
				const char* c1 = str.c_str();			//	��������������� � ��������� �� ������ �����
				MessageBox(m_hwnd, c1, "������", MB_OK);
			}
		}
		break;
	}
	return DlgBoxTempalate::RealDlgProc(hwnd, uMsg, wParam, lParam);
}

MainDlg::~MainDlg(void) {

}

