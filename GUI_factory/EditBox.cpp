#include "EditBox.h"

EditBox::EditBox(HWND hParent, int control_id) : Control(hParent, control_id) {
	txt = NULL;
}


// �������� ����� ������� ���������� � EditBox
char* EditBox::GetText(){
	// ���� ���� ����� �� ����� � ������ �� �� ��� �������
	if (txt) {
		delete txt;
		txt = NULL;
	}

	int len = SendMessage(m_hwnd, EM_LINELENGTH, 0, 0);	// ��������� ��������� �������� �� ���������� ����� �����
	// ���� ����� �� ������ �� �������� ������ ��� �����
	if (len) {
		txt = new char[len + 1];
		txt[len] = 0;

		SendMessage(m_hwnd, EM_GETLINE, 0, (LPARAM)txt);
		return txt;
	}
	return NULL;
}

char* EditBox::GetMultiText() {
	// ���� ���� ����� �� ����� � ������ �� �� ��� �������
	if (txt) {
		delete txt;
		txt = NULL;
	}
	int count = SendMessage(m_hwnd, EM_GETLINECOUNT, 0, 0);	// ��������� ��������� �������� �� ���������� ���������� �����

	if (count) {
		int len = count;	// �� �� ������� �������� �� ����� ������
		for (int i = 0; i < count; i++) {
			len += SendMessage(m_hwnd, EM_LINELENGTH, SendMessage(m_hwnd, EM_LINEINDEX, i, 0), 0); // ����������� ����� ���������� ������ �� ����� ������
		}

		txt = new char[len + 1]; // �������� ������ ��� �����
		txt[len] = 0;

		for (int i = 0; i < count; i++) {
			int currentLen = SendMessage(m_hwnd, EM_LINELENGTH, SendMessage(m_hwnd, EM_LINEINDEX, i, 0), 0); // �������� ����� �������� � ������

			SendMessage(m_hwnd, EM_GETLINE, i, (LPARAM)txt);	// �������� ����� � ����� �����

			txt[currentLen] = '\n'; // � ����� ����� ������ ������� �� ����� �����
			txt += currentLen + 1;	// �������� �����
		}
		txt -= len;	// ���������� � ������
		return txt;
	}
	return NULL;
}

void EditBox::SetText(char* text) {
	SendMessage(m_hwnd, WM_SETTEXT, 0, (LPARAM)text);
}

void EditBox::AppendText(char* text) {
	DWORD startPos, endPos = 0;
	SendMessage(m_hwnd, EM_GETSEL, (WPARAM)&startPos, (LPARAM)&endPos);

	int outLenght = GetWindowTextLength(m_hwnd);
	SendMessage(m_hwnd, EM_SETSEL, outLenght, outLenght);

	SendMessage(m_hwnd, EM_REPLACESEL, TRUE, (LPARAM)text);

	SendMessage(m_hwnd, EM_SETSEL, startPos, endPos);
}

EditBox::~EditBox(void) {
	if (txt) {
		delete txt;
	}
};