#pragma once
#include"BaseWindowController.h"

BaseWindowController::BaseWindowController() {

}

BaseWindowController::BaseWindowController(HINSTANCE hInstance, int window_width, int window_height) {
	m_hinst = hInstance;

	m_window_width = window_width;
	m_window_height = window_height;
}

BaseWindowController::~BaseWindowController() {
	DeleteWindow();
}

HRESULT BaseWindowController::errorMessage(LPCWSTR message) {
	MessageBox(NULL, message, NULL, MB_OK);
	return S_FALSE;
}

HRESULT BaseWindowController::CreateMainWindow(LPCWSTR className, LPCWSTR windowName) {
	//�E�B���h�E�o�^
	m_wcx.cbSize = sizeof(WNDCLASSEX);
	m_wcx.style = CS_HREDRAW | CS_VREDRAW;
	m_wcx.lpfnWndProc = BaseWindowController::baseWindowProc;
	m_wcx.cbClsExtra = 0;
	m_wcx.cbWndExtra = 0;
	m_wcx.hInstance = m_hinst;
	m_wcx.hIcon = NULL;
	m_wcx.hCursor = LoadCursor(NULL, IDC_ARROW);
	m_wcx.hbrBackground = NULL;
	m_wcx.lpszMenuName = NULL;
	m_wcx.lpszClassName = className;
	m_wcx.hIconSm = NULL;

	//�E�B���h�E�o�^
	m_atom = RegisterClassEx(&m_wcx);
	if (!m_atom) {
		return errorMessage(L"Failed to RegisterClassEX : TitleWindow");
	}

	//�E�B���h�E�쐬
	m_hwnd = CreateWindow(
		m_wcx.lpszClassName,
		windowName,
		WS_OVERLAPPED | WS_TILED,
		CW_USEDEFAULT, CW_USEDEFAULT,
		m_window_width, m_window_height,
		NULL,
		NULL,
		m_wcx.hInstance,
		this //�d�v : �����ɃN���X�I�u�W�F�N�g�|�C���^��n�����Ƃ�CREATESTRUCT����E�B���h�E�ƃN���X�I�u�W�F�N�g�̕R�Â����\�ɂȂ�
	); 
	
	if (!m_hwnd) {
		return errorMessage(L"Failed to CreateWindow : TitleWindow");
	}

	return S_OK;
}

HRESULT BaseWindowController::CreateButton(HWND hbtn, LPCTSTR text, int offsetX, int offsetY, int width,int height, int btnID) {
	hbtn = CreateWindow(
		L"BUTTON",
		text,
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		offsetX, offsetY,
		width, height,
		m_hwnd,
		(HMENU)btnID,
		m_hinst,
		NULL
	);
	if (!hbtn) return S_FALSE;

	return S_OK;
}

void BaseWindowController::DeleteWindow(){	
	//�E�B���h�E��j�����A�N���X�o�^����������

	if (m_hwnd) { //�E�B���h�E�����݂���ꍇ
		DestroyWindow(m_hwnd);
		m_hwnd = 0;
	}

	if (m_atom) { //�E�B���h�E�N���X���o�^����Ă���ꍇ
		UnregisterClass(m_wcx.lpszClassName, m_hinst);
		m_atom = 0;
	}
}

LRESULT BaseWindowController::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

//�Q�l -> https://suzulang.com/win32api%E3%81%A7%E3%82%A6%E3%82%A3%E3%83%B3%E3%83%89%E3%82%A6%E3%82%92%E3%82%AB%E3%83%97%E3%82%BB%E3%83%AB%E5%8C%96/
LRESULT CALLBACK BaseWindowController::baseWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	BaseWindowController* This = (BaseWindowController*)GetWindowLongPtr(hwnd, GWLP_USERDATA); //�E�B���h�E�ɕR�Â����Ă���I�u�W�F�N�g�|�C���^�̎擾

	if (!This) { //�擾���ł��Ȃ� -> �R�Â����Ă��Ȃ�
		if (uMsg == WM_CREATE) { //�E�B���h�E�������ɁA�N���X�I�u�W�F�N�g�ƃE�B���h�E�n���h����R�Â���
			This = (BaseWindowController*)((LPCREATESTRUCT)lParam)->lpCreateParams;
			if (This) {
				SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)This); //�E�B���h�E�̃��[�U�f�[�^�ɃI�u�W�F�N�g�|�C���^���Z�b�g����
				return This->WindowProc(hwnd, uMsg, wParam, lParam);
			}
			else { //lpCreateParams��0 -> CreateWindow�����s���Ă���A�E�B���h�E�v���V�[�W�����@�\���Ȃ��Ȃ�̂Ńv���O�������I��������
				errorMessage(L"Failed to Initialize WindowProc : CREATE");
				PostQuitMessage(0);
			}
		}
	}
	else { //�擾���ł��� -> �R�Â����ł��Ă���
		return This->WindowProc(hwnd, uMsg, wParam, lParam);
	}

	return DefWindowProc(hwnd, uMsg, wParam, lParam); //���ɂ��Ȃ��Ƃ��̓f�t�H���g�̃E�B���h�E�v���V�[�W����
}