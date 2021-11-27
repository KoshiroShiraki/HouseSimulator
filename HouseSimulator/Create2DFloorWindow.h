#pragma once
#include"BaseWindowController.h"
#include"Polygon2D.h"
#include"Camera2D.h"

#define CB_FLOOR 0
#define BTN_FLOOR_ADD 1
#define BTN_FLOOR_SUB 2
#define LB_FLOOR_OBJLIST 3
#define LB_FLOOR_OBJS 4

class Create2DFloorWindow : public BaseWindowController {
public:
	

private:
	RECT m_rc_paintArea = {}; //�`��̈�
	int m_paintArea_width;
	int m_paintArea_height;

	RECT m_rc_editArea1 = {}; //�ҏW�̈�1
	int m_editArea1_width;
	int m_editArea1_height;
	
	RECT m_rc_editArea2 = {}; //�ҏW�̈�2
	int m_editArea2_width;
	int m_editArea2_height;
	
	RECT m_rc_transformArea = {}; //�g�����X�t�H�[���̈�
	
	HWND m_hCb; //�K���I��p�R���{�{�b�N�X
	HWND m_hBtn[2]; //�K�������p�{�^��([0]:����, [1]:����)
	HWND m_hLb[3];

	Camera2D m_camera; //�J����

public:
	Create2DFloorWindow();
	Create2DFloorWindow(HINSTANCE hInstance, int window_width, int window_height);
	~Create2DFloorWindow();

public:
	LRESULT WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) override; //�E�B���h�E�v���V�[�W��
	HRESULT InitWindow() override;
	void SetArea();
	HRESULT CreateChildWindow() override;
	void DrawArea(HDC hdc, PAINTSTRUCT ps); //�E�B���h�E�v���V�[�W���Ŏ��ۂɗ̈�̕`����s��
	void DrawPolygon(HDC hdc, PAINTSTRUCT ps, Polygon2D& polygon);
};