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

	SetArea(); //領域設定

	if (FAILED(CreateChildWindow())) { //子ウィンドウ(ボタンとかドロップダウンボックスとか)作成
		return S_FALSE;
	}

	if (FAILED(SetDefaultPolygonsText())) { //テキストの設定
		return S_FALSE;
	}
	return S_OK;
}

void Create2DFloorWindow::SetArea() {
	//描画領域の設定
	m_rc_paintArea.top = m_client_height / 50;
	m_rc_paintArea.left = m_client_width / 50;
	m_rc_paintArea.bottom = m_client_height * 9 / 10;
	m_rc_paintArea.right = m_client_width * 7 / 10;
	//描画領域の幅/高さ
	m_paintArea_width = m_rc_paintArea.right - m_rc_paintArea.left;
	m_paintArea_height = m_rc_paintArea.bottom - m_rc_paintArea.top;
	//編集領域1の設定
	m_rc_editArea1.top = m_rc_paintArea.top;
	m_rc_editArea1.left = m_rc_paintArea.right + m_client_width / 50;
	m_rc_editArea1.bottom = m_rc_paintArea.bottom;
	m_rc_editArea1.right = m_client_width * 49 / 50;
	//編集領域1の幅/高さ
	m_editArea1_width = m_rc_editArea1.right - m_rc_editArea1.left;
	m_editArea1_height = m_rc_editArea1.bottom - m_rc_editArea1.top;
	//編集領域2の設定
	m_rc_editArea2.top = m_rc_paintArea.bottom + m_client_height / 100;
	m_rc_editArea2.left = m_rc_paintArea.left;
	m_rc_editArea2.bottom = m_client_height * 49 / 50;
	m_rc_editArea2.right = m_rc_editArea1.right;
	//編集領域2の幅/高さ
	m_editArea2_width = m_rc_editArea2.right - m_rc_editArea2.left;
	m_editArea2_height = m_rc_editArea2.bottom - m_rc_editArea2.top;
	//トランスフォーム編集領域の設定
}

HRESULT Create2DFloorWindow::CreateChildWindow() {
	//階数ドロップダウンボックスの配置
	if (FAILED(CreateComboBox(m_hCb, NULL, m_rc_editArea1.left + m_editArea1_width / 100, m_rc_editArea1.top + m_editArea1_height / 100, m_editArea1_width / 7, m_editArea1_height / 7, CB_FLOOR))) {
		return S_FALSE;
	}
	int CBoffsetX = m_rc_editArea1.left + m_editArea1_width / 100 + m_editArea1_width / 7;
	int CBoffsetY = m_rc_editArea1.top + m_editArea1_height / 100 + m_editArea1_height / 20;
	//階数増減ボタンの配置
	if (FAILED(CreateButton(m_hBtn[0], L"+", CBoffsetX + m_editArea1_width / 50, m_rc_editArea1.top + m_editArea1_height / 100, m_editArea1_width / 10, m_editArea1_height / 50, BTN_FLOOR_ADD))) {
		return S_FALSE;
	}
	if (FAILED(CreateButton(m_hBtn[1], L"-", CBoffsetX + m_editArea1_width / 50 + m_editArea1_width / 10, m_rc_editArea1.top + m_editArea1_height / 100, m_editArea1_width / 10, m_editArea1_height / 50, BTN_FLOOR_ADD))) {
		return S_FALSE;
	}
	//配置済みオブジェクトリストボックスの配置
	if (FAILED(CreateListBox(m_hLb[0], NULL, m_rc_editArea1.left + m_editArea1_width / 110, CBoffsetY, (m_editArea1_width - 2 * (m_editArea1_width / 100)) / 2, m_editArea1_height / 2, LB_FLOOR_OBJLIST))) {
		return S_FALSE;
	}
	int LBoffsetX = m_rc_editArea1.left + m_editArea1_width / 110 + (m_editArea1_width - 2 * (m_editArea1_width / 100)) / 2;
	//配置可能オブジェクトリストボックスの配置
	if (FAILED(CreateListBox(m_hLb[1], NULL, LBoffsetX + m_editArea1_width / 220, CBoffsetY, (m_editArea1_width - 2 * (m_editArea1_width / 100)) / 2, m_editArea1_height / 2, LB_FLOOR_OBJS))) {
		return S_FALSE;
	}
	int LBoffsetY = CBoffsetY + m_editArea1_height / 2;
	//ポリゴン作成/消去ボタンの配置
	if (FAILED(CreateButton(m_hBtnND[0], L"add", m_rc_editArea1.left + m_editArea1_width / 2, LBoffsetY, m_editArea1_width / 5, m_editArea1_height / 50, BTN_POLYGON_ADD))) {
		return S_FALSE;
	}if (FAILED(CreateButton(m_hBtnND[0], L"delete", m_rc_editArea1.left + m_editArea1_width / 2 + m_editArea1_width / 5, LBoffsetY, m_editArea1_width / 5, m_editArea1_height / 50, BTN_POLYGON_ADD))) {
		return S_FALSE;
	}
	return S_OK;
}

HRESULT Create2DFloorWindow::SetDefaultPolygonsText() {
	for (int i = 0; i < DefaultPolygons.size(); i++) {
		if (SendMessage(m_hLb[1], LB_ADDSTRING, 0, (LPARAM)DefaultPolygons[i].data()) == LB_ERR) {
			return errorMessage(L"Failed to SetDefaultPolygonsText()");
		}
	}
}

void Create2DFloorWindow::DrawArea(HDC hdc, PAINTSTRUCT ps) {
	//背景色
	SelectObject(hdc, GetStockObject(DKGRAY_BRUSH));
	Rectangle(hdc, 0, 0, m_client_width, m_client_height);
	//描画領域
	SelectObject(hdc, GetStockObject(WHITE_BRUSH));
	Rectangle(hdc, m_rc_paintArea.left, m_rc_paintArea.top, m_rc_paintArea.right, m_rc_paintArea.bottom);
	//編集領域1
	Rectangle(hdc, m_rc_editArea1.left, m_rc_editArea1.top, m_rc_editArea1.right, m_rc_editArea1.bottom);
	//編集領域2
	Rectangle(hdc, m_rc_editArea2.left, m_rc_editArea2.top, m_rc_editArea2.right, m_rc_editArea2.bottom);
}

void Create2DFloorWindow::DrawPolygon(HDC hdc, PAINTSTRUCT ps, Polygon2D& polygon) {
	//カメラ座標に変換
	std::vector<POINT> dest;
	dest.resize(polygon.m_worldVertices.size());
	for (int i = 0; i < polygon.m_worldVertices.size(); i++) {
		dest[i].x = (polygon.m_worldVertices[i].x + (double)m_paintArea_width / 2.0 - m_camera.pos.x);
		dest[i].y = (-polygon.m_worldVertices[i].y + (double)m_paintArea_height / 2.0 + m_camera.pos.y);
	}
	Polygon(hdc, dest.data(), dest.size());
}

LRESULT Create2DFloorWindow::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	//Windowsの描画インターフェース(GDI)
	HDC hdc;
	PAINTSTRUCT ps;
	//GDIオブジェクト
	HRGN hrgn; //リージョン : 描画クリップ領域の指定
	hrgn = CreateRectRgnIndirect(&m_rc_paintArea);
	HPEN pen; //ペン

	Polygon2D unko;

	switch (uMsg) {
	case WM_CREATE:
		SetDefaultPolygonsText();
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);

		DrawArea(hdc, ps); //編集領域の描画
		
		SelectClipRgn(hdc, hrgn); //描画領域のみにポリゴン描画するため、リージョンでクリップ
		//DrawPolygon(hdc, ps); //ポリゴンの描画
		
		EndPaint(hwnd, &ps);
		return 0;

	case WM_KEYDOWN:

		//ウィンドウ再描画(WM_PAINTの強制呼び出し)
		InvalidateRect(hwnd, NULL, TRUE);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}