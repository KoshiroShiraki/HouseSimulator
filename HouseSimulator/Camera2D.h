#pragma once
#include<Windows.h>

class Camera2D {
public:
	POINT pos; //�ʒu
	int zoom; //�Y�[���{��

public:
	Camera2D();
	~Camera2D();
};