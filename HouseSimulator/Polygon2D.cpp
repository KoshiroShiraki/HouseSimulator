#pragma once
#include"Polygon2D.h"

Polygon2D::Polygon2D() {
	initParam();
	//éläpå`
	m_localVertices.resize(4);
	m_worldVertices.resize(4);
	
	m_worldVertices[0].x = m_localVertices[0].x = -50.0f; m_worldVertices[0].y = m_localVertices[0].y = 100.0f;
	m_worldVertices[1].x = m_localVertices[1].x = 50.0f; m_worldVertices[1].y = m_localVertices[1].y = 50.0f;
	m_worldVertices[2].x = m_localVertices[2].x = 100.0f; m_worldVertices[2].y = m_localVertices[2].y = -50.0f;
	m_worldVertices[3].x = m_localVertices[3].x = -50.0f; m_worldVertices[3].y = m_localVertices[3].y = -50.0f;
}

Polygon2D::Polygon2D(int type) {
	initParam();
}

Polygon2D::Polygon2D(std::vector<POINT>* vertices) {
	if(vertices != nullptr) initParam();
}

Polygon2D::~Polygon2D() {

}

void Polygon2D::initParam() {
	m_centerX = m_centerY = 0;
	m_sizeX = m_sizeY = 1.0;
	m_rotation = 0;
}

void Polygon2D::move(long dx, long dy) {
	m_centerX += dx;
	m_centerY += dy;
	for (int i = 0; i < m_localVertices.size(); i++) {
		m_worldVertices[i].x = m_localVertices[i].x + m_centerX;
		m_worldVertices[i].y = m_localVertices[i].y + m_centerY;
	}
}

void Polygon2D::rotate(double deg) {
	for (int i = 0; i < m_localVertices.size(); i++) {
		m_worldVertices[i].x = m_localVertices[i].x * cos(deg * PI / 180.0) - m_localVertices[i].y * sin(deg * PI / 180.0);
		m_worldVertices[i].x = m_localVertices[i].y * sin(deg * PI / 180.0) + m_localVertices[i].y * cos(deg * PI / 180.0);
	}
}