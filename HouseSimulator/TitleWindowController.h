/*
�^�C�g���E�B���h�E(�ŏ�)����N���X
*/

#pragma once
#include"BaseWindowController.h"

//�{�^��ID
#define BTNID_START 0
#define BTNID_LOAD 1
#define BTNID_END 2

class TitleWindowController : public BaseWindowController {
private:
	HWND m_hbtn[3]; //�{�^���n���h�� : [0]�Ɛ���, [1]�Ɠǂݍ���, [2]�I��

public :
	TitleWindowController();
	TitleWindowController(HINSTANCE hInstance, int window_width, int window_height);
	~TitleWindowController();

public:
	virtual LRESULT WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) override; //�E�B���h�E�v���V�[�W��
	HRESULT InitWindow() override;
	HRESULT CreateChildWindow() override;
};