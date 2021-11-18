#include<Windows.h>
#include<vector>
#include"AppWindowHeaders.h"

#define MAX_MONITORCNT 8
RECT monitors[MAX_MONITORCNT]; //���j�^�[��(��� : MAX_MONITORCNT)
int monitorCnt = 0; //���j�^�[�J�E���g

//���j�^���𓾂邽�߂̃R�[���o�b�N�֐�(EnumDisplayMonitors�ŌĂ΂��)
BOOL CALLBACK MonitorEnumProc(HMONITOR hmon, HDC hdc, LPRECT rect, LPARAM lParam) {
	if (monitorCnt < MAX_MONITORCNT) { //MAX_MONITORCNT�ȏ�Ɋ��蓖�Ă��郂�j�^�[�͖���
		monitors[monitorCnt] = *rect;

		monitorCnt++;
	}
	return TRUE;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	//���j�^���擾(�s�N�Z���ʒu�̂�)
	EnumDisplayMonitors(NULL, NULL, MonitorEnumProc, NULL);

	//�^�C�g���E�B���h�E�̐����ƕ\��
	/*TitleWindowController* twc = new TitleWindowController(hInstance, monitors[0].right/2, monitors[0].bottom/5);
	if (FAILED(twc->InitWindow())) {
		delete twc;

		return -1;
	}
	ShowWindow(twc->m_hwnd, nCmdShow);*/

	//�K���Z�b�g�E�B���h�E�̐����ƕ\��
	Create2DFloorWindow* sfcw = new Create2DFloorWindow(hInstance, monitors[0].right * 9 / 10, monitors[0].bottom * 9 / 10);
	if (FAILED(sfcw->InitWindow())) {
		delete sfcw;

		return -1;
	}
	ShowWindow(sfcw->m_hwnd, nCmdShow);

	//���b�Z�[�W���[�v
	MSG msg = {};
	while (true) {
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		if (msg.message == WM_QUIT) {
			break;
		}
	}

	//delete twc;
	delete sfcw;

	return 1;
}