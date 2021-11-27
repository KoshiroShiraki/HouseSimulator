#pragma once
#include"Polygon2D.h"

Polygon2D::Polygon2D() {
	initParam();
}

Polygon2D::Polygon2D(int type) {
	initParam();
	setPolygon(type);
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

void Polygon2D::setPolygon(int type) {
	switch (type) {
	case room1:
		break;
	case room2:
		break;
	case room3:
		break;
	case room4:
		break;
	case hall:
		break;
	}
}