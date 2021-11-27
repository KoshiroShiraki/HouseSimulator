#pragma once
#include<string>
#include<vector>
#include<Windows.h>

#define PI 3.14159265359 //円周率

class Polygon2D {
public:
	std::wstring m_objName; //オブジェクト名
private:
	std::vector<POINT> m_localVertices; //多角形頂点位置(ローカル)
public:
	std::vector<POINT> m_worldVertices; //多角形長点位置(ワールド) ← m_localVerticesを[回転→移動]の順で変換したもの
	double m_centerX, m_centerY; //オブジェクト中心位置 ← 回転変換済m_worldVerticesにこの2つの変数をoffsetとして足すことで移動
	double m_sizeX, m_sizeY; //拡大/縮小率
	double m_rotation; //回転(degree)

public:
	Polygon2D(); 
	Polygon2D(int type); //デフォルトでいくつか図形を用意する
	Polygon2D(std::vector<POINT>* vertices); //ユーザ定義の図形
	~Polygon2D();

public:
	void initParam();
	void move(double dx, double dy); //移動関数, dx = x変化量, dy = y変化量
	void rotate(double deg); //回転関数, deg = 回転量
};