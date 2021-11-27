#pragma once
#include"BaseWindowController.h"

class DebugWindowController : public BaseWindowController {
private:
	std::vector<std::wstring> m_writeStr; //�f�o�b�O������z��
	int max_line;
	int write_offset;

public:
	DebugWindowController();
	DebugWindowController(HINSTANCE hInstance, int window_width, int window_height);
	~DebugWindowController();

public:	
	virtual LRESULT WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) override; //�E�B���h�E�v���V�[�W��
	HRESULT InitWindow() override;
	HRESULT CreateChildWindow() override;
	//�f�o�b�O�E�B���h�E�Ƀf�[�^���o�͂���
	template<class T>
	void DebugLog(T data) { //���s�t�@�C���Ɏ����������ƎQ�Ƃ����܂�����������`�����ɂ����̂Ńw�b�_�t�@�C���ɋL�q
		//�v�f����max_line��葽���ꍇ��vector�̗v�f���폜���Ă���ǉ�(capasity�͂��̂܂�)
		if (m_writeStr.size() > max_line - 1) {
			m_writeStr.clear();
		}
		std::wstring tmp = std::to_wstring(data);

		m_writeStr.push_back(tmp.c_str());
	}
	void DebugLog(const WCHAR* data); //�}���`�o�C�g������ɂ͑Ή����Ȃ��̂Ń��j�R�[�h������ŃR���p�C������悤��
	
};