#include "MainDlg.h"
#include <commctrl.h>

#pragma comment(lib, "Comctl32.lib")

#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	INITCOMMONCONTROLSEX init = { sizeof(INITCOMMONCONTROLSEX), ICC_WIN95_CLASSES };
	if (!InitCommonControlsEx(&init)) {
		MessageBox(NULL, "Initialization of controls has been failed!", "FATAL ERROR", MB_OK | MB_ICONERROR);
	}
	
	MSG msg;

	MainDlg* Main = new MainDlg(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL);
	Main->Show(SW_SHOW);

	while (FALSE != GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}