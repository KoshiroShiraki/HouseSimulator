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

	SetArea(); //�̈�ݒ�

	if (FAILED(CreateChildWindow())) { //�q�E�B���h�E(�{�^���Ƃ��h���b�v�_�E���{�b�N�X�Ƃ�)�쐬
		return S_FALSE;
	}

	if (FAILED(SetDefaultPolygonsText())) { //�e�L�X�g�̐ݒ�
		return S_FALSE;
	}
	return S_OK;
}

void Create2DFloorWindow::SetArea() {
	//�`��̈�̐ݒ�
	m_rc_paintArea.top = m_client_height / 50;
	m_rc_paintArea.left = m_client_width / 50;
	m_rc_paintArea.bottom = m_client_height * 9 / 10;
	m_rc_paintArea.right = m_client_width * 7 / 10;
	//�`��̈�̕�/����
	m_paintArea_width = m_rc_paintArea.right - m_rc_paintArea.left;
	m_paintArea_height = m_rc_paintArea.bottom - m_rc_paintArea.top;
	//�ҏW�̈�1�̐ݒ�
	m_rc_editArea1.top = m_rc_paintArea.top;
	m_rc_editArea1.left = m_rc_paintArea.right + m_client_width / 50;
	m_rc_editArea1.bottom = m_rc_paintArea.bottom;
	m_rc_editArea1.right = m_client_width * 49 / 50;
	//�ҏW�̈�1�̕�/����
	m_editArea1_width = m_rc_editArea1.right - m_rc_editArea1.left;
	m_editArea1_height = m_rc_editArea1.bottom - m_rc_editArea1.top;
	//�ҏW�̈�2�̐ݒ�
	m_rc_editArea2.top = m_rc_paintArea.bottom + m_client_height / 100;
	m_rc_editArea2.left = m_rc_paintArea.left;
	m_rc_editArea2.bottom = m_client_height * 49 / 50;
	m_rc_editArea2.right = m_rc_editArea1.right;
	//�ҏW�̈�2�̕�/����
	m_editArea2_width = m_rc_editArea2.right - m_rc_editArea2.left;
	m_editArea2_height = m_rc_editArea2.bottom - m_rc_editArea2.top;
	//�g�����X�t�H�[���ҏW�̈�̐ݒ�
}

HRESULT Create2DFloorWindow::CreateChildWindow() {
	//�K���h���b�v�_�E���{�b�N�X�̔z�u
	if (FAILED(CreateComboBox(m_hCb, NULL, m_rc_editArea1.left + m_editArea1_width / 100, m_rc_editArea1.top + m_editArea1_height / 100, m_editArea1_width / 7, m_editArea1_height / 7, CB_FLOOR))) {
		return S_FALSE;
	}
	int CBoffsetX = m_rc_editArea1.left + m_editArea1_width / 100 + m_editArea1_width / 7;
	int CBoffsetY = m_rc_editArea1.top + m_editArea1_height / 100 + m_editArea1_height / 20;
	//�K�������{�^���̔z�u
	if (FAILED(CreateButton(m_hBtn[0], L"+", CBoffsetX + m_editArea1_width / 50, m_rc_editArea1.top + m_editArea1_height / 100, m_editArea1_width / 10, m_editArea1_height / 50, BTN_FLOOR_ADD))) {
		return S_FALSE;
	}
	if (FAILED(CreateButton(m_hBtn[1], L"-", CBoffsetX + m_editArea1_width / 50 + m_editArea1_width / 10, m_rc_editArea1.top + m_editArea1_height / 100, m_editArea1_width / 10, m_editArea1_height / 50, BTN_FLOOR_ADD))) {
		return S_FALSE;
	}
	//�z�u�ς݃I�u�W�F�N�g���X�g�{�b�N�X�̔z�u
	if (FAILED(CreateListBox(m_hLb[0], NULL, m_rc_editArea1.left + m_editArea1_width / 110, CBoffsetY, (m_editArea1_width - 2 * (m_editArea1_width / 100)) / 2, m_editArea1_height / 2, LB_FLOOR_OBJLIST))) {
		return S_FALSE;
	}
	int LBoffsetX = m_rc_editArea1.left + m_editArea1_width / 110 + (m_editArea1_width - 2 * (m_editArea1_width / 100)) / 2;
	//�z�u�\�I�u�W�F�N�g���X�g�{�b�N�X�̔z�u
	if (FAILED(CreateListBox(m_hLb[1], NULL, LBoffsetX + m_editArea1_width / 220, CBoffsetY, (m_editArea1_width - 2 * (m_editArea1_width / 100)) / 2, m_editArea1_height / 2, LB_FLOOR_OBJS))) {
		return S_FALSE;
	}
	int LBoffsetY = CBoffsetY + m_editArea1_height / 2;
	//�|���S���쐬/�����{�^���̔z�u
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
	//�w�i�F
	SelectObject(hdc, GetStockObject(DKGRAY_BRUSH));
	Rectangle(hdc, 0, 0, m_client_width, m_client_height);
	//�`��̈�
	SelectObject(hdc, GetStockObject(WHITE_BRUSH));
	Rectangle(hdc, m_rc_paintArea.left, m_rc_paintArea.top, m_rc_paintArea.right, m_rc_paintArea.bottom);
	//�ҏW�̈�1
	Rectangle(hdc, m_rc_editArea1.left, m_rc_editArea1.top, m_rc_editArea1.right, m_rc_editArea1.bottom);
	//�ҏW�̈�2
	Rectangle(hdc, m_rc_editArea2.left, m_rc_editArea2.top, m_rc_editArea2.right, m_rc_editArea2.bottom);
}

void Create2DFloorWindow::DrawPolygon(HDC hdc, PAINTSTRUCT ps, Polygon2D& polygon) {
	//�J�������W�ɕϊ�
	std::vector<POINT> dest;
	dest.resize(polygon.m_worldVertices.size());
	for (int i = 0; i < polygon.m_worldVertices.size(); i++) {
		dest[i].x = (polygon.m_worldVertices[i].x + (double)m_paintArea_width / 2.0 - m_camera.pos.x);
		dest[i].y = (-polygon.m_worldVertices[i].y + (double)m_paintArea_height / 2.0 + m_camera.pos.y);
	}
	Polygon(hdc, dest.data(), dest.size());
}

LRESULT Create2DFloorWindow::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	//Windows�̕`��C���^�[�t�F�[�X(GDI)
	HDC hdc;
	PAINTSTRUCT ps;
	//GDI�I�u�W�F�N�g
	HRGN hrgn; //���[�W���� : �`��N���b�v�̈�̎w��
	hrgn = CreateRectRgnIndirect(&m_rc_paintArea);
	HPEN pen; //�y��

	Polygon2D unko;

	switch (uMsg) {
	case WM_CREATE:
		SetDefaultPolygonsText();
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);

		DrawArea(hdc, ps); //�ҏW�̈�̕`��
		
		SelectClipRgn(hdc, hrgn); //�`��̈�݂̂Ƀ|���S���`�悷�邽�߁A���[�W�����ŃN���b�v
		//DrawPolygon(hdc, ps); //�|���S���̕`��
		
		EndPaint(hwnd, &ps);
		return 0;

	case WM_KEYDOWN:

		//�E�B���h�E�ĕ`��(WM_PAINT�̋����Ăяo��)
		InvalidateRect(hwnd, NULL, TRUE);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}