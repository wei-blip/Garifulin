#include "Control.h"

Control::Control(HWND hParent, int control_id) {
	m_hwnd = GetDlgItem(hParent, control_id);	// ��������� �� ������� � �������
	m_hParent = hParent;
}

Control::~Control(){}

HWND Control::getHandle() { return  this->m_hwnd; }
HWND Control::getParent() { return this->m_hParent; }
int Control::getID() { return this->m_id; }
void Control::SetFont(HFONT hFont) { SendMessage(m_hwnd, WM_SETFONT, (WPARAM)hFont, true); }
HFONT Control::GetFont() { HFONT hFont = (HFONT)SendMessage(m_hwnd, WM_GETFONT, 0, 0); return hFont; }

RECT Control::GetPositionRect() {
	RECT ctrlRect = { 0 };				// ������������� � ������������ ��������
	GetWindowRect(m_hwnd, &ctrlRect);	// �������� ���������� ���������� �������� ������������ �������� ����

	POINT p1 = { ctrlRect.left, ctrlRect.top };		//	���������� (����������) ����� ������� ����� ��������
	POINT p2 = { ctrlRect.right, ctrlRect.bottom};	//	���������� (����������) ������ ������ ����� ��������
	
	ScreenToClient(m_hParent, &p1);		// ��������� ���������� (����������) ����� � ���������� ����� ������������ ������ �������
	ScreenToClient(m_hParent, &p2);		// ��������� ���������� (����������) ����� � ���������� ����� ������������ ������ �������

	ctrlRect.left = p1.x;
	ctrlRect.right = p2.x;
	ctrlRect.top = p1.y;
	ctrlRect.bottom = p2.y;
	
	return ctrlRect;
}
