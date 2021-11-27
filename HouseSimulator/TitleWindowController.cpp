#pragma once
#include"TitleWindowController.h"
#include"Create2DFloorWindow.h"

TitleWindowController::TitleWindowController() {

}

TitleWindowController::TitleWindowController(HINSTANCE hInstance, int window_width, int window_height) : BaseWindowController(hInstance, window_width, window_height) {

}

TitleWindowController::~TitleWindowController() {
	for (int i = 0; i < sizeof(m_hbtn) / sizeof(HWND); i++) {
		if (m_hbtn) {
			DestroyWindow(m_hbtn[i]);
			m_hbtn[i] = 0;
		}
	}
}

HRESULT TitleWindowController::InitWindow() {
	//���C���E�B���h�E����
	if (FAILED(CreateMainWindow(L"TITLE", L"TITLE"))) {
		return errorMessage(L"Failed to CreateMainWindow : TITLE");
	}

	CreateChildWindow();
}

HRESULT TitleWindowController::CreateChildWindow() {
	//�{�^������
	if (FAILED(CreateButton(m_hbtn[0], L"�쐬", 0, 0, m_client_width / 3, m_client_height, BTNID_START))) {
		return errorMessage(L"Failed to CreateWindow : Button 1");
	}
	if (FAILED(CreateButton(m_hbtn[1], L"�ǂݍ���", m_client_width / 3, 0, m_client_width / 3, m_client_height, BTNID_LOAD))) {
		return errorMessage(L"Failed to CreateWindow : Button 2");
	}
	if (FAILED(CreateButton(m_hbtn[2], L"�I��", m_client_width * 2 / 3, 0, m_client_width / 3, m_client_height, BTNID_END))) {
		return errorMessage(L"Failed to CreateWindow : Button 3");
	}
	return S_OK;
}

LRESULT TitleWindowController::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg) {
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case BTNID_START: //�쐬

			break;
		case BTNID_LOAD: //�ǂݍ���

			break;
		case BTNID_END: //�I��
			PostQuitMessage(0);
			break;
		}
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}