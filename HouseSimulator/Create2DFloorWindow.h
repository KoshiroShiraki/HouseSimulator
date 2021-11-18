#pragma once
#include"BaseWindowController.h"

class Create2DFloorWindow : public BaseWindowController {
public:
	Create2DFloorWindow();
	Create2DFloorWindow(HINSTANCE hInstance, int window_width, int window_height);
	~Create2DFloorWindow();

private:
	RECT rc_paintArea = {}; //�`��̈�

public:
	virtual LRESULT WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) override; //�E�B���h�E�v���V�[�W��
	HRESULT InitWindow() override;
};