/*
�E�B���h�E�Ǘ��p�x�[�X�N���X
*/

#pragma once
#include<Windows.h>

class BaseWindowController {
public:
	HWND m_hwnd; //�E�B���h�E�n���h��
	WNDCLASSEX m_wcx; //�E�B���h�E�N���X��`

protected:
	ATOM m_atom; //�E�B���h�E�o�^�`�F�b�N�p
	HINSTANCE m_hinst; //�A�v���P�[�V�����C���X�^���X�n���h��

protected:
	int m_window_width; //�E�B���h�E��
	int m_window_height; //�E�B���h�E����

public:
	BaseWindowController();
	BaseWindowController(HINSTANCE hInstance, int window_width, int window_height);
	~BaseWindowController();

public:
	virtual HRESULT InitWindow() = 0; //�E�B���h�E������(�E�B���h�E�N���X�o�^ -> ���C���E�B���h�E���� -> �q�E�B���h�E����)
	
	static HRESULT errorMessage(LPCWSTR message); //�G���[���e(message)��MessageBox�\�����A�K��S_FALSE��Ԃ�

protected:
	HRESULT CreateMainWindow(LPCWSTR className, LPCWSTR windowName); //�p���N���X�͂��ꂼ��K��m_hwnd�n���h���ɕR�Â�����̃��C���E�B���h�E������
	HRESULT CreateButton(HWND hBtn, LPCTSTR text, int offsetX, int offsetY, int width, int height, int btnID); //�{�^���𐶐�����
	void DeleteWindow(); //�E�B���h�E�̍폜�ƃN���X�̓o�^����

public:
	virtual LRESULT WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam); //�p���N���X���Ƃ̎��������ۂɋL�q����E�B���h�E�v���V�[�W��
	static LRESULT CALLBACK baseWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam); //�E�B���h�E�N���X�ɐݒ肷��p�̃E�B���h�E�v���V�[�W��
};