#pragma once
#include "MyColor.h"
#include "Shape.h"

static COLORREF currentBackgroundColor, currentBorderColor1, currentBorderColor2;//biến lưu các màu đang chọn

/// Vẽ màu background trong toolbox
void PaintBackgroundToolBox(HDC hdc, HBRUSH hBrush) { //HBrush để vẽ màu nền
	hBrush = CreateSolidBrush(currentBackgroundColor);
	SelectObject(hdc, hBrush);  //Phải có dòng này mới  dùng hBrush ở trên để tô màu
	Rectangle(hdc, 865, 15, 955, 85); //Hàm tạo hình chữ nhật: các số trong hàm là vị trí left top,  right, buttom
}

/// Vẽ màu color1 trong toolbox
void PaintColor1ToolBox(HDC hdc, HBRUSH hBrush) {
	hBrush = CreateSolidBrush(currentBorderColor1);
	SelectObject(hdc, hBrush);
	Rectangle(hdc, 465, 15, 515, 60);
}

/// Vẽ màu color1 trong toolbox
void PaintColor2ToolBox(HDC hdc, HBRUSH hBrush) {
	hBrush = CreateSolidBrush(currentBorderColor2);
	SelectObject(hdc, hBrush);
	Rectangle(hdc, 520, 15, 570, 60);
}

void setToolBoxColor(HDC hdc, HWND hWnd, HPEN hPen, HBRUSH hBrush) {
	hdc = GetDC(hWnd);


	////Vẽ màu PenSize: mấy cái gạch đen ngang cạnh phần color1 
	POINT point[2];
	point[0].x = 395;
	point[1].x = 435;
	point[0].y = point[1].y = 0;

	for (int i = 0; i < 5; i++) {
		hPen = CreatePen(PS_SOLID, i + 1, Black()); //Tạo bút vé: param1: kiểu bút, param2 : kích  thước bút, param3: màu sắc
		SelectObject(hdc, hPen);
		point[0].y += 20;
		point[1].y += 20;
		Polyline(hdc, point, 2); //Hàm nối tọa độ các điểm: hàm này ko kín nên ko đổ màu vào trong đc. muốn đổ màu nền phải dùng polygon
	}
	///// tương tự cái trên nhưng vẽ phần group ngoài cùng bên phải
	hPen = CreatePen(PS_SOLID, 2, Black());
	SelectObject(hdc, hPen);

	point[0].x = 1160;
	point[0].y = 25;
	point[1].x = 1215;
	point[1].y = 25;
	Polyline(hdc, point, 2);

	hPen = CreatePen(PS_DOT, 1, Black());
	SelectObject(hdc, hPen);
	point[0].x = 1160;
	point[0].y = 50;
	point[1].x = 1215;
	point[1].y = 50;
	Polyline(hdc, point, 2);

	hPen = CreatePen(PS_DASHDOT, 1, Black());
	SelectObject(hdc, hPen);
	point[0].x = 1160;
	point[0].y = 75;
	point[1].x = 1215;
	point[1].y = 75;
	Polyline(hdc, point, 2);

	hPen = CreatePen(PS_DASH, 1, Black());
	SelectObject(hdc, hPen);
	point[0].x = 1160;
	point[0].y = 100;
	point[1].x = 1215;
	point[1].y = 100;
	Polyline(hdc, point, 2);


	//1150, 15,15, 20
	//1150, 40, 15, 20
	//Color1
	////////////////////////////////////////
	hPen = CreatePen(PS_SOLID, 1, Black());
	SelectObject(hdc, hPen);
	PaintColor1ToolBox(hdc, hBrush);
	//Color2
	PaintColor2ToolBox(hdc, hBrush);




	//////////////////////////////// Choose Color: Vẽ các màu phần chọn color
	////////////////////////////////////////
	hBrush = CreateSolidBrush(Black()); // dun
	SelectObject(hdc, hBrush);
	Rectangle(hdc, 600, 15, 615, 30);
	//
	hBrush = CreateSolidBrush(DarkGray());
	SelectObject(hdc, hBrush);
	Rectangle(hdc, 625, 15, 640, 30);
	//
	hBrush = CreateSolidBrush(DarkBrown());
	SelectObject(hdc, hBrush);
	Rectangle(hdc, 650, 15, 665, 30);
	//
	hBrush = CreateSolidBrush(Red());
	SelectObject(hdc, hBrush);
	Rectangle(hdc, 675, 15, 690, 30);
	//
	hBrush = CreateSolidBrush(DarkOrange());
	SelectObject(hdc, hBrush);
	Rectangle(hdc, 700, 15, 715, 30);
	//
	hBrush = CreateSolidBrush(DarkYellow());
	SelectObject(hdc, hBrush);
	Rectangle(hdc, 725, 15, 740, 30);
	//
	hBrush = CreateSolidBrush(DarkGreen());
	SelectObject(hdc, hBrush);
	Rectangle(hdc, 750, 15, 765, 30);
	//
	hBrush = CreateSolidBrush(DarkAqua());
	SelectObject(hdc, hBrush);
	Rectangle(hdc, 775, 15, 790, 30);
	//
	hBrush = CreateSolidBrush(DarkBlue());
	SelectObject(hdc, hBrush);
	Rectangle(hdc, 800, 15, 815, 30);
	//
	hBrush = CreateSolidBrush(DarkPurple());
	SelectObject(hdc, hBrush);
	Rectangle(hdc, 825, 15, 840, 30);


	///////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////
	hBrush = CreateSolidBrush(White());
	SelectObject(hdc, hBrush);
	Rectangle(hdc, 600, 70, 615, 85);
	//
	hBrush = CreateSolidBrush(LightGray());
	SelectObject(hdc, hBrush);
	Rectangle(hdc, 625, 70, 640, 85);
	//
	hBrush = CreateSolidBrush(LightBrown());
	SelectObject(hdc, hBrush);
	Rectangle(hdc, 650, 70, 665, 85);
	//
	hBrush = CreateSolidBrush(Pink());
	SelectObject(hdc, hBrush);
	Rectangle(hdc, 675, 70, 690, 85);
	//
	hBrush = CreateSolidBrush(LightOrange());
	SelectObject(hdc, hBrush);
	Rectangle(hdc, 700, 70, 715, 85);
	//
	hBrush = CreateSolidBrush(LightYellow());
	SelectObject(hdc, hBrush);
	Rectangle(hdc, 725, 70, 740, 85);
	//
	hBrush = CreateSolidBrush(LightGreen());
	SelectObject(hdc, hBrush);
	Rectangle(hdc, 750, 70, 765, 85);
	//
	hBrush = CreateSolidBrush(LightAqua());
	SelectObject(hdc, hBrush);
	Rectangle(hdc, 775, 70, 790, 85);
	//
	hBrush = CreateSolidBrush(LightBlue());
	SelectObject(hdc, hBrush);
	Rectangle(hdc, 800, 70, 815, 85);
	//
	hBrush = CreateSolidBrush(LightPurple());
	SelectObject(hdc, hBrush);
	Rectangle(hdc, 825, 70, 840, 85);

	//Current Background Color
	PaintBackgroundToolBox(hdc, hBrush);





	///////////////////////////////////////// PAINT SHAPES ////////////////////////////////////////////////////////////////////
	Shape* s = new Shape();
	s->setStyle(Black(), White(), 1, PS_SOLID);
	//line
	point[0].x = 45; point[0].y = 25;
	point[1].x = 65; point[1].y = 25;
	s->setPosition(point[0], point[1]);
	s->Draw(hdc, true);
	//ellipse
	point[0].x = 45; point[0].y = 35;
	point[1].x = 65; point[1].y = 50;
	s->setPosition(point[0], point[1]);
	s->setShapeMode(ShapeMode::CIRCLE);
	s->Draw(hdc, true);
	//Rectangle
	point[0].x = 45; point[0].y = 55;
	point[1].x = 65; point[1].y = 70;
	s->setPosition(point[0], point[1]);
	s->setShapeMode(ShapeMode::RECTANGLE);
	s->Draw(hdc, true);
	//isosceles triangle
	point[0].x = 45; point[0].y = 75;
	point[1].x = 65; point[1].y = 90;
	s->setPosition(point[0], point[1]);
	s->setShapeMode(ShapeMode::ISOSCELES_TRIANGLE);
	s->Draw(hdc, true);
	// triangle
	point[0].x = 45; point[0].y = 95;
	point[1].x = 65; point[1].y = 110;
	s->setPosition(point[0], point[1]);
	s->setShapeMode(ShapeMode::TRIANGLE);
	s->Draw(hdc, true);


	////////Quadrilateral
	point[0].x = 135; point[0].y = 15;
	point[1].x = 155; point[1].y = 30;
	s->setPosition(point[0], point[1]);
	s->setShapeMode(ShapeMode::QUADRILATERAL);
	s->Draw(hdc, true);
	//pentagon
	point[0].x = 135; point[0].y = 35;
	point[1].x = 155; point[1].y = 50;
	s->setPosition(point[0], point[1]);
	s->setShapeMode(ShapeMode::PENTAGON);
	s->Draw(hdc, true);
	//hexagon
	point[0].x = 135; point[0].y = 55;
	point[1].x = 150; point[1].y = 70;
	s->setPosition(point[0], point[1]);
	s->setShapeMode(ShapeMode::HEXAGON);
	s->Draw(hdc, true);
	//forward arrow
	point[0].x = 135; point[0].y = 75;
	point[1].x = 155; point[1].y = 90;
	s->setPosition(point[0], point[1]);
	s->setShapeMode(ShapeMode::FORWARD_ARROW);
	s->Draw(hdc, true);
	//back arrow
	point[0].x = 135; point[0].y = 95;
	point[1].x = 155; point[1].y = 110;
	s->setPosition(point[0], point[1]);
	s->setShapeMode(ShapeMode::BACK_ARROW);
	s->Draw(hdc, true);


	//////up arrow
	point[0].x = 230; point[0].y = 15;
	point[1].x = 250; point[1].y = 30;
	s->setPosition(point[0], point[1]);
	s->setShapeMode(ShapeMode::UP_ARROW);
	s->Draw(hdc, true);
	//down arrow
	point[0].x = 230; point[0].y = 35;
	point[1].x = 250; point[1].y = 50;
	s->setPosition(point[0], point[1]);
	s->setShapeMode(ShapeMode::DOWN_ARROW);
	s->Draw(hdc, true);
	// star four point
	point[0].x = 230; point[0].y = 55;
	point[1].x = 250; point[1].y = 70;
	s->setPosition(point[0], point[1]);
	s->setShapeMode(ShapeMode::FOUR_POINT_STAR);
	s->Draw(hdc, true);
	//star five point
	point[0].x = 230; point[0].y = 75;
	point[1].x = 250; point[1].y = 90;
	s->setPosition(point[0], point[1]);
	s->setShapeMode(ShapeMode::FIVE_POINT_STAR);
	s->Draw(hdc, true);
	//star six point
	point[0].x = 230; point[0].y = 95;
	point[1].x = 250; point[1].y = 110;
	s->setPosition(point[0], point[1]);
	s->setShapeMode(ShapeMode::SIX_POINT_STAR);
	s->Draw(hdc, true);

	//MoveWindow(hwndShape[15], 285, 35, 20, 20, TRUE);
	////LIGHTNING
	point[0].x = 325; point[0].y = 35;
	point[1].x = 345; point[1].y = 50;
	s->setPosition(point[0], point[1]);
	s->setShapeMode(ShapeMode::LIGHTNING);
	s->Draw(hdc, true);
	///ROUND RECT
	point[0].x = 325; point[0].y = 75;
	point[1].x = 345; point[1].y = 90;
	s->setPosition(point[0], point[1]);
	s->setShapeMode(ShapeMode::ROUND_RECT);
	s->Draw(hdc, true);


	// Giai phong HDC
	ReleaseDC(hWnd, hdc);
}