/*
ウィンドウ管理用ベースクラス
*/

#pragma once
#include<Windows.h>
#include<iostream>
#include<vector>
#include<string>

class BaseWindowController {
public:
	HWND m_hwnd; //ウィンドウハンドル
	WNDCLASSEX m_wcx; //ウィンドウクラス定義

protected:
	ATOM m_atom; //ウィンドウ登録チェック用
	HINSTANCE m_hinst; //アプリケーションインスタンスハンドル

public:
	int m_window_width; //ウィンドウ幅
	int m_window_height; //ウィンドウ高さ

	int m_client_width; //クライアント領域幅
	int m_client_height; //クライアント領域高さ

public:
	BaseWindowController();
	BaseWindowController(HINSTANCE hInstance, int window_width, int window_height);
	~BaseWindowController();
	
public:
	virtual HRESULT InitWindow() = 0; //ウィンドウ初期化(ウィンドウクラス登録 -> メインウィンドウ生成 -> 子ウィンドウ生成)
	virtual HRESULT CreateChildWindow() = 0;

	static HRESULT errorMessage(LPCWSTR message); //エラー内容(message)をMessageBox表示し、必ずS_FALSEを返す

protected:
	HRESULT CreateMainWindow(LPCWSTR className, LPCWSTR windowName); //継承クラスはそれぞれ必ずm_hwndハンドルに紐づいた一つのメインウィンドウを持つ
	HRESULT CreateButton(HWND hBtn, LPCWSTR text, int offsetX, int offsetY, int width, int height, int btnID); //ボタンを生成する
	HRESULT CreateComboBox(HWND hCb, LPCWSTR text, int offsetX, int offsetY, int width, int height, int cbID); //コンボボックスを生成する
	HRESULT CreateListBox(HWND hLb, LPCWSTR text, int offsetX, int offsetY, int width, int height, int lbID); //リストボックスを生成する
	void DeleteWindow(); //ウィンドウの削除とクラスの登録解除

public:
	virtual LRESULT WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam); //継承クラスごとの実装を実際に記述するウィンドウプロシージャ
	static LRESULT CALLBACK baseWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam); //ウィンドウクラスに設定する用のウィンドウプロシージャ
};