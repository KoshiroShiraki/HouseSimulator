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

	//�N���C�A���g�̈�̎擾
	RECT rc_client;
	GetClientRect(m_hwnd, &rc_client);
	//�`��̈�̐ݒ�
	rc_paintArea.top = rc_client.bottom / 50;
	rc_paintArea.left = rc_client.right / 50;
	rc_paintArea.bottom = rc_client.bottom * 9 / 10;
	rc_paintArea.right = rc_client.right * 8 / 10;

	return S_OK;
}

LRESULT Create2DFloorWindow::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	//Windows�̕`��C���^�[�t�F�[�X(GDI)
	HDC hdc;
	PAINTSTRUCT ps;
	//GDI�I�u�W�F�N�g
	HRGN; //���[�W���� : �`��N���b�v�̈�̎w��
	HPEN pen; //�y��
	
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