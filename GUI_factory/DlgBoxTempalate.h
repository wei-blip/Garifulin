#pragma once
#include <Windows.h>
#include "resource.h"
// hwnd - ��������� �� ������
// ����� ����������� ���� �� �������� ������������ ��� ��������� ������
class DlgBoxTempalate
{
public:
	DlgBoxTempalate(HINSTANCE hInstance, LPCSTR dlgResName, HWND hwndParent);
	virtual ~DlgBoxTempalate();
	void Show(int nCmdShow);

private:
	void CreateDlg(HINSTANCE hInstance, LPCSTR dlgResName, HWND parent); // ����������� ��������� �������
	virtual void OnCreate() = 0;	//	����� ������� ����� ���������� ��� �������� ������ �������
	static LRESULT WINAPI StDlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

protected:
	virtual LRESULT RealDlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam); // ��������� ��������� ������� 
	HWND m_hwnd;
};

