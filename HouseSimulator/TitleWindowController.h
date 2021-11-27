/*
タイトルウィンドウ(最初)制御クラス
*/

#pragma once
#include"BaseWindowController.h"

//ボタンID
#define BTNID_START 0
#define BTNID_LOAD 1
#define BTNID_END 2

class TitleWindowController : public BaseWindowController {
private:
	HWND m_hbtn[3]; //ボタンハンドル : [0]家生成, [1]家読み込み, [2]終了

public :
	TitleWindowController();
	TitleWindowController(HINSTANCE hInstance, int window_width, int window_height);
	~TitleWindowController();

public:
	virtual LRESULT WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) override; //ウィンドウプロシージャ
	HRESULT InitWindow() override;
	HRESULT CreateChildWindow() override;
};