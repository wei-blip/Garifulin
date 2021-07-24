#include "EditBox.h"

EditBox::EditBox(HWND hParent, int control_id) : Control(hParent, control_id) {
	txt = NULL;
}


// ѕолучаем текст который содержитс€ в EditBox
char* EditBox::GetText(){
	// ≈сли есть какой то текст в буфере то мы его удал€ем
	if (txt) {
		delete txt;
		txt = NULL;
	}

	int len = SendMessage(m_hwnd, EM_LINELENGTH, 0, 0);	// отслылаем сообщение контролу он возвращает длину линии
	// ≈сли буфер не пустой то выдел€ем пам€ть под текст
	if (len) {
		txt = new char[len + 1];
		txt[len] = 0;

		SendMessage(m_hwnd, EM_GETLINE, 0, (LPARAM)txt);
		return txt;
	}
	return NULL;
}

char* EditBox::GetMultiText() {
	// ≈сли есть какой то текст в буфере то мы его удал€ем
	if (txt) {
		delete txt;
		txt = NULL;
	}
	int count = SendMessage(m_hwnd, EM_GETLINECOUNT, 0, 0);	// отслылаем сообщение контролу он возвращает количество строк

	if (count) {
		int len = count;	// из за символа перехода на новую строку
		for (int i = 0; i < count; i++) {
			len += SendMessage(m_hwnd, EM_LINELENGTH, SendMessage(m_hwnd, EM_LINEINDEX, i, 0), 0); // увеличиваем длину требуемого буфера на длину строки
		}

		txt = new char[len + 1]; // выдел€ем пам€ть под буфер
		txt[len] = 0;

		for (int i = 0; i < count; i++) {
			int currentLen = SendMessage(m_hwnd, EM_LINELENGTH, SendMessage(m_hwnd, EM_LINEINDEX, i, 0), 0); // получаем число символов в строке

			SendMessage(m_hwnd, EM_GETLINE, i, (LPARAM)txt);	// получаем текст с одной линии

			txt[currentLen] = '\n'; // в конце линии делаем переход на новую линию
			txt += currentLen + 1;	// сдвигаем буфер
		}
		txt -= len;	// возвращаем в начало
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