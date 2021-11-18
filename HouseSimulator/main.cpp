#include<Windows.h>
#include<vector>
#include"AppWindowHeaders.h"

#define MAX_MONITORCNT 8
RECT monitors[MAX_MONITORCNT]; //モニター数(上限 : MAX_MONITORCNT)
int monitorCnt = 0; //モニターカウント

//モニタ情報を得るためのコールバック関数(EnumDisplayMonitorsで呼ばれる)
BOOL CALLBACK MonitorEnumProc(HMONITOR hmon, HDC hdc, LPRECT rect, LPARAM lParam) {
	if (monitorCnt < MAX_MONITORCNT) { //MAX_MONITORCNT以上に割り当てられるモニターは無視
		monitors[monitorCnt] = *rect;

		monitorCnt++;
	}
	return TRUE;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	//モニタ情報取得(ピクセル位置のみ)
	EnumDisplayMonitors(NULL, NULL, MonitorEnumProc, NULL);

	//タイトルウィンドウの生成と表示
	/*TitleWindowController* twc = new TitleWindowController(hInstance, monitors[0].right/2, monitors[0].bottom/5);
	if (FAILED(twc->InitWindow())) {
		delete twc;

		return -1;
	}
	ShowWindow(twc->m_hwnd, nCmdShow);*/

	//階数セットウィンドウの生成と表示
	Create2DFloorWindow* sfcw = new Create2DFloorWindow(hInstance, monitors[0].right * 9 / 10, monitors[0].bottom * 9 / 10);
	if (FAILED(sfcw->InitWindow())) {
		delete sfcw;

		return -1;
	}
	ShowWindow(sfcw->m_hwnd, nCmdShow);

	//メッセージループ
	MSG msg = {};
	while (true) {
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		if (msg.message == WM_QUIT) {
			break;
		}
	}

	//delete twc;
	delete sfcw;

	return 1;
}