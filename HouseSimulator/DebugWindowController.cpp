#pragma once
#include"DebugWindowController.h"


DebugWindowController::DebugWindowController() {
}

DebugWindowController::DebugWindowController(HINSTANCE hInstance, int window_width, int window_height) : BaseWindowController(hInstance, window_width, window_height) {

}

DebugWindowController::~DebugWindowController() {
	//vectorの開放
	m_writeStr.clear();
	m_writeStr.shrink_to_fit();
}

HRESULT DebugWindowController::InitWindow() {
	if (FAILED(CreateMainWindow(L"DEBUG", L"DEBUG"))) {
		return errorMessage(L"Failed to CreateMainWindow : DEBUG");
	}
	return S_OK;
}

HRESULT DebugWindowController::CreateChildWindow() {
	return S_OK;
}

void DebugWindowController::DebugLog(const WCHAR* data) {
	//要素数がmax_lineより多い場合はvectorの要素を削除してから追加(capasityはそのまま)
	if (m_writeStr.size() > max_line - 1) {
		m_writeStr.clear();
	}

	m_writeStr.push_back(data);
}

LRESULT DebugWindowController::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	HDC hdc;
	PAINTSTRUCT ps;

	switch (uMsg) {
	case WM_CREATE:
		//
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		//文字大きさ取得
		TEXTMETRIC tm;
		GetTextMetrics(hdc, &tm);
		//文字高さから1行オフセットと表示可能限界の行数を求める
		write_offset = tm.tmHeight;
		max_line = (m_client_height / write_offset);

		SelectObject(hdc, GetStockObject(BLACK_BRUSH));
		//背景色は黒
		Rectangle(hdc, 0, 0, m_client_width, m_client_height);
		//文字色は白
		SetBkColor(hdc, 0x00000000);
		SetTextColor(hdc, 0x00ffffff);
		for (int i = 0; i < m_writeStr.size(); i++) {
			if (!TextOut(hdc, 0, write_offset * i, m_writeStr[i].c_str(), wcslen(m_writeStr[i].c_str()))) { //関数が失敗したときに通知
				errorMessage(L"Cannot output DebugLog");
			}

		}
		EndPaint(hwnd, &ps);

		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}