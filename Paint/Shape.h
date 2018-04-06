#pragma once
#include <Windows.h>
#include "stdafx.h"

enum ShapeMode
{
	LINE,
	CIRCLE,
	RECTANGLE,
	ISOSCELES_TRIANGLE,
	TRIANGLE,
	QUADRILATERAL,
	PENTAGON,
	HEXAGON,
	FORWARD_ARROW,
	BACK_ARROW,
	UP_ARROW,
	DOWN_ARROW,
	FOUR_POINT_STAR,
	FIVE_POINT_STAR,
	SIX_POINT_STAR,
	LIGHTNING,
	ROUND_RECT
};

class Point {
	int x, y;
public:
	Point(int x, int y) { this->x = x; this->y = y; }

	POINT getPoint() {
		POINT p;
		p.x = this->x;
		p.y = this->y;
		return p;
	}
};

class Shape
{
protected:
	COLORREF borderColor, backgroundColor;
	ShapeMode shapeMode;
	int x1, y1, x2, y2;
	int penStyle;
	int penSize;
	bool isShowToolBox = true;
public:

	void Draw(HDC hdc, bool isShowToolBox);

	COLORREF getBorderColor();
	void setBorderColor(COLORREF color);

	COLORREF getBackgroundColor();
	void setBackgroundColor(COLORREF color);

	void setShapeMode(ShapeMode mode);
	ShapeMode getShapeMode();

	void setPenStyle(int style);
	int getPenStyle();

	void setPenSize(int size);
	int getPenSize();

	void setPosition(POINT p1, POINT p2);


	void setIsShowTool(bool isShowTool);

	void setStyle(COLORREF borderColor, COLORREF backgroundColor, int penSize, int PenStyle);
};

