#pragma once
#include <Windows.h>
#include "resource.h"
// hwnd - указатель на диалог
// Класс диалогового окна от которого наследуюьтся все остальные классы
class DlgBoxTempalate
{
public:
	DlgBoxTempalate(HINSTANCE hInstance, LPCSTR dlgResName, HWND hwndParent);
	virtual ~DlgBoxTempalate();
	void Show(int nCmdShow);

private:
	void CreateDlg(HINSTANCE hInstance, LPCSTR dlgResName, HWND parent); // статическая процедура диалога
	virtual void OnCreate() = 0;	//	метод который будет вызываться при создании нашего диалога
	static LRESULT WINAPI StDlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

protected:
	virtual LRESULT RealDlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam); // настоящая процедура диалога 
	HWND m_hwnd;
};

