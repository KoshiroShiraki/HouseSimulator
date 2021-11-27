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
	RECT m_rc_paintArea = {}; //描画領域
	int m_paintArea_width;
	int m_paintArea_height;

	RECT m_rc_editArea1 = {}; //編集領域1
	int m_editArea1_width;
	int m_editArea1_height;
	
	RECT m_rc_editArea2 = {}; //編集領域2
	int m_editArea2_width;
	int m_editArea2_height;
	
	RECT m_rc_transformArea = {}; //トランスフォーム領域
	
	HWND m_hCb; //階数選択用コンボボックス
	HWND m_hBtn[2]; //階数増減用ボタン([0]:増加, [1]:減少)
	HWND m_hLb[3];

	Camera2D m_camera; //カメラ

public:
	Create2DFloorWindow();
	Create2DFloorWindow(HINSTANCE hInstance, int window_width, int window_height);
	~Create2DFloorWindow();

public:
	LRESULT WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) override; //ウィンドウプロシージャ
	HRESULT InitWindow() override;
	void SetArea();
	HRESULT CreateChildWindow() override;
	void DrawArea(HDC hdc, PAINTSTRUCT ps); //ウィンドウプロシージャで実際に領域の描画を行う
	void DrawPolygon(HDC hdc, PAINTSTRUCT ps, Polygon2D& polygon);
};