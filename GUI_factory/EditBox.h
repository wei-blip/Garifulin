#pragma once
#include "Control.h"

class EditBox
	: public Control
{
public:
	EditBox(HWND hParent, int control_id);
	~EditBox(void);

	char* GetText();
	char* GetMultiText();
	void SetText(char* text);
	void AppendText(char* text);

private:
	char* txt;
};

