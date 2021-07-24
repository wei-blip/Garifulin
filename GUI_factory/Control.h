#pragma once
#include <Windows.h>

// hParent диалог в котором контрол расположен

class Control
{
public:
	Control(HWND hParent, int control_id);
	virtual ~Control(void);

	void SetFont(HFONT hFont);	// устанавливаем шрифт контрола
	HFONT GetFont();			// Получаем шрифт контрола
	RECT GetPositionRect();		// Позиция контрола относительно окна диалога

	HWND getHandle();
	HWND getParent();
	int getID();

protected:
	HWND m_hwnd;		// указатель на контрол
	HWND m_hParent;		// родительский класс
	int  m_id;			// id контрола в файле ресурсов 
};

