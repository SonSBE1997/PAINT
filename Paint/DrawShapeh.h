#pragma once
#include <Windows.h>

void DrawLine(HDC hdc, int left, int top, int right, int bottom) {
	POINT p[2];
	p[0].x = left;
	p[0].y = top;
	p[1].x = right;
	p[1].y = bottom;
	Polyline(hdc, p, 2);
}

void DrawIsosceleTriangle(HDC hdc, int left, int top, int right, int bottom) {
	POINT p[4];
	p[3].x = p[0].x = left + (right - left) / 2;
	p[3].y = p[0].y = top;
	p[1].x = left;
	p[1].y = p[2].y = bottom;
	p[2].x = right;
	Polygon(hdc, p, 4);
}

void DrawTriangle(HDC hdc, int left, int top, int right, int bottom) {
	POINT p[4];
	p[3].x = p[0].x = left;
	p[3].y = p[0].y = top;
	p[1].x = left;
	p[1].y = p[2].y = bottom;
	p[2].x = right;
	Polygon(hdc, p, 4);
}

void DrawQuadrilateral(HDC hdc, int left, int top, int right, int bottom) {
	POINT p[5];
	p[4].x = p[0].x = left + (right - left) / 2;
	p[4].y = p[0].y = top;

	p[1].y = p[3].y = top + (bottom - top) / 2;
	p[1].x = right;

	p[2].x = left + (right - left) / 2;
	p[2].y = bottom;

	p[3].x = left;
	Polygon(hdc, p, 5);
}

void DrawPentagon(HDC hdc, int left, int top, int right, int bottom) {
	POINT p[6];
	p[5].x = p[0].x = left + (right - left) / 2;
	p[5].y = p[0].y = top;

	p[1].x = left;
	p[1].y = p[4].y = top + 2 * (bottom - top) / 5;

	p[2].x = left + (right - left) / 5;
	p[2].y = p[3].y = bottom;

	p[3].x = left + 4 * (right - left) / 5;

	p[4].x = right;
	Polygon(hdc, p, 6);
}

void DrawHexagon(HDC hdc, int left, int top, int right, int bottom) {
	POINT p[7];
	p[6].x = p[0].x = p[3].x = left + (right - left) / 2;
	p[6].y = p[0].y = top;

	p[2].x = p[1].x = left;
	p[1].y = p[5].y = top + (bottom - top) / 4;
	p[4].x = p[5].x = right;

	p[2].y = p[4].y = top + 3 * (bottom - top) / 4;

	p[3].y = bottom;
	Polygon(hdc, p, 7);
}

void DrawForwardArrow(HDC hdc, int left, int top, int right, int bottom) {
	if (right < left) {
		int t = left;
		left = right;
		right = t;
	}
	POINT p[8];
	p[7].x = p[0].x = p[1].x = p[4].x = p[5].x = left + (right - left) / 2;
	p[7].y = p[0].y = top;

	p[1].y = p[2].y = top + (bottom - top) / 4;
	p[2].x = p[3].x = left;

	p[3].y = p[4].y = top + 3 * (bottom - top) / 4;
	p[5].y = bottom;

	p[6].x = right;
	p[6].y = top + (bottom - top) / 2;
	Polygon(hdc, p, 8);
}

void DrawBackArrow(HDC hdc, int left, int top, int right, int bottom) {
	if (right < left) {
		int t = left;
		left = right;
		right = t;
	}
	POINT p[8];
	p[7].x = p[0].x = p[1].x = p[4].x = p[5].x = left + (right - left) / 2;
	p[7].y = p[0].y = top;

	p[1].y = p[2].y = top + (bottom - top) / 4;
	p[2].x = p[3].x = right;

	p[3].y = p[4].y = top + 3 * (bottom - top) / 4;
	p[5].y = bottom;

	p[6].x = left;
	p[6].y = top + (bottom - top) / 2;
	Polygon(hdc, p, 8);
}

void DrawDownArrow(HDC hdc, int left, int top, int right, int bottom) {
	if (bottom < top) {
		int t = top;
		top = bottom;
		bottom = t;
	}
	POINT p[8];
	p[0].x = p[7].x = p[1].x = left + (right - left) / 4;
	p[0].y = p[7].y = p[6].y = top;
	p[1].y = p[2].y = p[4].y = p[5].y = top + (bottom - top) / 2;
	p[2].x = left;

	p[3].x = left + (right - left) / 2;
	p[3].y = bottom;

	p[4].x = right;
	p[5].x = p[6].x = left + 3 * (right - left) / 4;
	Polygon(hdc, p, 8);
}

void DrawUpArrow(HDC hdc, int left, int top, int right, int bottom) {
	if (bottom < top) {
		int t = top;
		top = bottom;
		bottom = t;
	}
	POINT p[8];
	p[0].x = p[7].x = p[1].x = left + (right - left) / 4;
	p[0].y = p[7].y = p[6].y = bottom;
	p[1].y = p[2].y = p[4].y = p[5].y = top + (bottom - top) / 2;
	p[2].x = left;

	p[3].x = left + (right - left) / 2;
	p[3].y = top;

	p[4].x = right;
	p[5].x = p[6].x = left + 3 * (right - left) / 4;
	Polygon(hdc, p, 8);
}

void DrawFourPointStar(HDC hdc, int left, int top, int right, int bottom) {
	POINT p[9];
	p[4].x = p[8].x = p[0].x = left + (right - left) / 2;
	p[8].y = p[0].y = top;

	p[1].x = p[3].x = left + 2 * (right - left) / 5;
	p[1].y = p[7].y = top + 2 * (bottom - top) / 5;

	p[2].x = left;
	p[2].y = p[6].y = top + (bottom - top) / 2;

	p[3].y = p[5].y = top + 3 * (bottom - top) / 5;
	p[4].y = bottom;

	p[5].x = p[7].x = left + 3 * (right - left) / 5;
	p[6].x = right;
	Polygon(hdc, p, 9);
}


void DrawFivePointStar(HDC hdc, int left, int top, int right, int bottom) {
	POINT p[11];
	p[10].x = p[0].x = left + (right - left) / 2;
	p[10].y = p[0].y = top;
	p[1].x = left + 10 * (right - left) / 16;
	p[1].y = top + 3 * (bottom - top) / 8;

	p[2].x = right;
	p[2].y = top + 3 * (bottom - top) / 8; //=p1

	p[3].x = left + 5 * (right - left) / 7;
	p[3].y = top + 5 * (bottom - top) / 8;

	p[4].x = left + 5 * (right - left) / 6;
	p[4].y = bottom;

	p[5].x = left + (right - left) / 2;
	p[5].y = top + 3 * (bottom - top) / 4;

	p[6].x = left + (right - left) / 6;
	p[6].y = bottom;

	p[7].x = left + 2 * (right - left) / 7;
	p[7].y = top + 5 * (bottom - top) / 8;

	p[8].x = left;
	p[8].y = top + 3 * (bottom - top) / 8;

	p[9].x = left + 6 * (right - left) / 16;
	p[9].y = top + 3 * (bottom - top) / 8;
	Polygon(hdc, p, 11);
}


void DrawSixPointStar(HDC hdc, int left, int top, int right, int bottom) {
	POINT p[13];
	p[6].x = p[12].x = p[0].x = left + (right - left) / 2;
	p[12].y = p[0].y = top;

	p[5].x = p[1].x = left + (right - left) / 3;
	p[10].y = p[11].y = p[2].y = p[1].y = top + (bottom - top) / 4;

	p[4].x = p[2].x = left;
	p[3].x = left + (right - left) / 6;
	p[9].y = p[3].y = top + (bottom - top) / 2;

	p[8].y = p[7].y = p[5].y = p[4].y = top + 3 * (bottom - top) / 4;
	p[6].y = bottom;

	p[11].x = p[7].x = left + 2 * (right - left) / 3;
	p[10].x = p[8].x = right;
	p[9].x = left + 5 * (right - left) / 6;

	Polygon(hdc, p, 13);
}


void DrawLightning(HDC hdc, int left, int top, int right, int bottom) {
	if (right < left) {
		int t = left;
		left = right;
		right = t;
	}

	if (bottom < top) {
		int t = top;
		top = bottom;
		bottom = t;
	}

	POINT p[12];
	p[11].x = p[0].x = left + 8 * (right - left) / 20;
	p[11].y = p[0].y = top;

	p[1].x = left;
	p[1].y = top + 4 * (bottom - top) / 20;

	p[2].x = left + 7 * (right - left) / 20;
	p[2].y = top + 8 * (bottom - top) / 20;

	p[3].x = left + 5 * (right - left) / 20;
	p[3].y = top + 9 * (bottom - top) / 20;

	p[4].x = left + 11 * (right - left) / 20;
	p[4].y = top + 13 * (bottom - top) / 20;

	p[5].x = left + 10 * (right - left) / 20;
	p[5].y = top + 14 * (bottom - top) / 20;

	p[6].x = right;
	p[6].y = bottom;

	p[7].x = left + 14 * (right - left) / 20;
	p[7].y = top + 12 * (bottom - top) / 20;

	p[8].x = left + 15 * (right - left) / 20;
	p[8].y = top + 11 * (bottom - top) / 20;

	p[9].x = left + 21 * (right - left) / 40;
	p[9].y = top + 7 * (bottom - top) / 20;

	p[10].x = left + 12 * (right - left) / 20;
	p[10].y = top + 6 * (bottom - top) / 20;
	Polygon(hdc, p, 12);
}

void DrawRoundRect(HDC hdc, int left, int top, int right, int bottom) {
	if (right < left) {
		int t = left;
		left = right;
		right = t;
	}

	if (bottom < top) {
		int t = top;
		top = bottom;
		bottom = t;
	}

	int width = (right - left) * 20 / 100;
	int height = (bottom - top) * 20 / 100;
	RoundRect(hdc, left, top, right, bottom, width, height);
}