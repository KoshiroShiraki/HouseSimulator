#pragma once
#include"BaseWindowController.h"

class DebugWindowController : public BaseWindowController {
private:
	std::vector<std::wstring> m_writeStr; //デバッグ文字列配列
	int max_line;
	int write_offset;

public:
	DebugWindowController();
	DebugWindowController(HINSTANCE hInstance, int window_width, int window_height);
	~DebugWindowController();

public:	
	virtual LRESULT WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) override; //ウィンドウプロシージャ
	HRESULT InitWindow() override;
	HRESULT CreateChildWindow() override;
	//デバッグウィンドウにデータを出力する
	template<class T>
	void DebugLog(T data) { //実行ファイルに実装を書くと参照がうまくいかず未定義扱いにあんるのでヘッダファイルに記述
		//要素数がmax_lineより多い場合はvectorの要素を削除してから追加(capasityはそのまま)
		if (m_writeStr.size() > max_line - 1) {
			m_writeStr.clear();
		}
		std::wstring tmp = std::to_wstring(data);

		m_writeStr.push_back(tmp.c_str());
	}
	void DebugLog(const WCHAR* data); //マルチバイト文字列には対応しないのでユニコード文字列でコンパイルするように
	
};