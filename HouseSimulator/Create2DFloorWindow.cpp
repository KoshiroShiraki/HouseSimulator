#pragma once
#include"Create2DFloorWindow.h"

Create2DFloorWindow::Create2DFloorWindow() {

}

Create2DFloorWindow::Create2DFloorWindow(HINSTANCE hInstance, int window_width, int window_height) : BaseWindowController(hInstance, window_width, window_height) {

}

Create2DFloorWindow::~Create2DFloorWindow() {

}

HRESULT Create2DFloorWindow::InitWindow() {
	if (FAILED(CreateMainWindow(L"SETFLOOR", L"SETFLOOR"))) {
		errorMessage(L"Failed to CreateMainWindow");
		return S_FALSE;
	}

	//クライアント領域の取得
	RECT rc_client;
	GetClientRect(m_hwnd, &rc_client);
	//描画領域の設定
	rc_paintArea.top = rc_client.bottom / 50;
	rc_paintArea.left = rc_client.right / 50;
	rc_paintArea.bottom = rc_client.bottom * 9 / 10;
	rc_paintArea.right = rc_client.right * 8 / 10;

	return S_OK;
}

LRESULT Create2DFloorWindow::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	//Windowsの描画インターフェース(GDI)
	HDC hdc;
	PAINTSTRUCT ps;
	//GDIオブジェクト
	HRGN; //リージョン : 描画クリップ領域の指定
	HPEN pen; //ペン
	
	switch (uMsg) {
	case WM_CREATE:

		return 0;
	case WM_PAINT:

		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}