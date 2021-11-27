#pragma once
#include<string>
#include<vector>
#include<Windows.h>

#define PI 3.14159265359 //�~����

class Polygon2D {
public:
	std::wstring m_objName; //�I�u�W�F�N�g��
private:
	std::vector<POINT> m_localVertices; //���p�`���_�ʒu(���[�J��)
public:
	std::vector<POINT> m_worldVertices; //���p�`���_�ʒu(���[���h) �� m_localVertices��[��]���ړ�]�̏��ŕϊ���������
	double m_centerX, m_centerY; //�I�u�W�F�N�g���S�ʒu �� ��]�ϊ���m_worldVertices�ɂ���2�̕ϐ���offset�Ƃ��đ������Ƃňړ�
	double m_sizeX, m_sizeY; //�g��/�k����
	double m_rotation; //��](degree)

public:
	Polygon2D(); 
	Polygon2D(int type); //�f�t�H���g�ł������}�`��p�ӂ���
	Polygon2D(std::vector<POINT>* vertices); //���[�U��`�̐}�`
	~Polygon2D();

public:
	void initParam();
	void move(double dx, double dy); //�ړ��֐�, dx = x�ω���, dy = y�ω���
	void rotate(double deg); //��]�֐�, deg = ��]��
};