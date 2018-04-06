#include "stdafx.h"
#include "Shape.h"
#include "DrawShapeh.h"


void Shape::Draw(HDC hdc, bool isShowTool) {
	int left, top, right, bottom;
	left = x1; right = x2;
	top = y1;
	bottom = y2;
	if (this->isShowToolBox != isShowTool) {
		if (!isShowTool) {
			top -= 125;
			bottom -= 125;
		}
		else {
			top += 125;
			bottom += 125;
		}
	}

	HPEN hPen = CreatePen(this->penStyle, this->penSize, this->borderColor);
	HBRUSH hBrush = CreateSolidBrush(this->backgroundColor);
	SelectObject(hdc, hPen);
	SelectObject(hdc, hBrush);

	switch (shapeMode)
	{
	case ShapeMode::LINE:
	{
		DrawLine(hdc, left, top, right, bottom);
		break;
	}
	case ShapeMode::CIRCLE:
		Ellipse(hdc, left, top, right, bottom);
		break;
	case ShapeMode::RECTANGLE:
		Rectangle(hdc, left, top, right, bottom);
		break;
	case ShapeMode::ISOSCELES_TRIANGLE:
		DrawIsosceleTriangle(hdc, left, top, right, bottom);
		break;
	case ShapeMode::QUADRILATERAL:
		DrawQuadrilateral(hdc, left, top, right, bottom);
		break;
	case ShapeMode::PENTAGON:
		DrawPentagon(hdc, left, top, right, bottom);
		break;
	case ShapeMode::HEXAGON:
		DrawHexagon(hdc, left, top, right, bottom);
		break;
	case ShapeMode::FORWARD_ARROW:
		DrawForwardArrow(hdc, left, top, right, bottom);
		break;
	case ShapeMode::BACK_ARROW:
		DrawBackArrow(hdc, left, top, right, bottom);
		break;
	case ShapeMode::UP_ARROW:
		DrawUpArrow(hdc, left, top, right, bottom);
		break;
	case ShapeMode::DOWN_ARROW:
		DrawDownArrow(hdc, left, top, right, bottom);
		break;
	case ShapeMode::TRIANGLE:
		DrawTriangle(hdc, left, top, right, bottom);
		break;
	case ShapeMode::FOUR_POINT_STAR:
		DrawFourPointStar(hdc, left, top, right, bottom);
		break;
	case ShapeMode::FIVE_POINT_STAR:
		DrawFivePointStar(hdc, left, top, right, bottom);
		break;
	case ShapeMode::SIX_POINT_STAR:
		DrawSixPointStar(hdc, left, top, right, bottom);
		break;
	case ShapeMode::LIGHTNING:
		DrawLightning(hdc, left, top, right, bottom);
		break;
	case ShapeMode::ROUND_RECT:
		DrawRoundRect(hdc, left, top, right, bottom);
		break;
	}

	DeleteObject(hPen);
	DeleteObject(hBrush);
}

void Shape::setIsShowTool(bool isShowTool) {
	this->isShowToolBox = isShowTool;
}

void Shape::setPosition(POINT p1, POINT p2) {
	this->x1 = p1.x;
	this->y1 = p1.y;
	this->x2 = p2.x;
	this->y2 = p2.y;
}
void Shape::setStyle(COLORREF borderColor, COLORREF backgroundColor, int penSize, int PenStyle) {
	this->borderColor = borderColor;
	this->backgroundColor = backgroundColor;
	this->penSize = penSize;
	this->penStyle = PenStyle;
}

COLORREF  Shape::getBorderColor() {
	return this->borderColor;
}

void  Shape::setBorderColor(COLORREF color) {
	this->borderColor = color;
}

COLORREF  Shape::getBackgroundColor() {
	return this->backgroundColor;
}

void  Shape::setBackgroundColor(COLORREF color) {
	this->backgroundColor = color;
}

void  Shape::setShapeMode(ShapeMode mode) {
	this->shapeMode = mode;
}

ShapeMode  Shape::getShapeMode() {
	return this->shapeMode;
}

void  Shape::setPenStyle(int style) {
	this->penStyle = style;
}

int  Shape::getPenStyle() {
	return this->penStyle;
}

void  Shape::setPenSize(int size) {
	this->penSize = size;
}

int  Shape::getPenSize() {
	return this->penSize;
}