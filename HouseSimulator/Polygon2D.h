#pragma once
#include<string>
#include<vector>
#include<Windows.h>

static std::vector<std::wstring> DefaultPolygons = { //���X�g�񋓗p������
	L"room1",
	L"room2",
	L"room3",
	L"room4",
	L"hall",
};

class Polygon2D {
public:
	std::wstring name;
private:
	std::vector<POINT> m_localVertices; //���p�`���_�ʒu(���[�J��)
	const double PI = 3.14159265359;//�~����
public:
	std::vector<POINT> m_worldVertices; //���p�`���_�ʒu(���[���h) �� m_localVertices��[��]���ړ�]�̏��ŕϊ���������
	long m_centerX, m_centerY; //�I�u�W�F�N�g���S�ʒu �� ��]�ϊ���m_worldVertices�ɂ���2�̕ϐ���offset�Ƃ��đ������Ƃňړ�
	double m_sizeX, m_sizeY; //�g��/�k����
	double m_rotation; //��](degree)

	enum PolygonType {
		room1,
		room2,
		room3,
		room4,
		hall,
	};

public:
	Polygon2D(); 
	Polygon2D(int type); //�f�t�H���g�ł������}�`��p�ӂ���
	Polygon2D(std::vector<POINT>* vertices); //���[�U��`�̐}�`
	~Polygon2D();

public:
	void initParam();
	void move(long dx, long dy); //�ړ��֐�, dx = x�ω���, dy = y�ω���
	void rotate(double deg); //��]�֐�, deg = ��]��
	void setPolygon(int type); //�|���S�����W�����肷��
};