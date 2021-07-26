#pragma once
#include "DlgBoxTempalate.h"
#include "calc_param.h"
#include "EditBox.h"
#include "resource.h"

// ������ ������� �������� �������� �� DlgBoxTempalate
// � ���� ����������� ��� ��������

class MainDlg : 
	public DlgBoxTempalate
{
public:
	MainDlg(HINSTANCE hInstance, LPCSTR dlgResName, HWND hwndParent);
	~MainDlg(void);
	LRESULT RealDlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	void OnCreate(); 

private:
	EditBox* pointA;
	EditBox* pointB;
};

