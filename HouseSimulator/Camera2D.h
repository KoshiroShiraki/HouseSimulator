#pragma once
#include<Windows.h>

class Camera2D {
public:
	POINT pos; //ˆÊ’u
	int zoom; //ƒY[ƒ€”{—¦

public:
	Camera2D();
	~Camera2D();
};