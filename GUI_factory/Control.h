#pragma once
#include <Windows.h>

// hParent ������ � ������� ������� ����������

class Control
{
public:
	Control(HWND hParent, int control_id);
	virtual ~Control(void);

	void SetFont(HFONT hFont);	// ������������� ����� ��������
	HFONT GetFont();			// �������� ����� ��������
	RECT GetPositionRect();		// ������� �������� ������������ ���� �������

	HWND getHandle();
	HWND getParent();
	int getID();

protected:
	HWND m_hwnd;		// ��������� �� �������
	HWND m_hParent;		// ������������ �����
	int  m_id;			// id �������� � ����� �������� 
};

