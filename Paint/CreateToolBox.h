#pragma once
#include <Windows.h>
#include "Identified.h"
/////////////////////////////// xong phần này thì c xem các phần: WM_CREATE, WM_SIZE nhé


static HWND hwndToolBox, hwndShape[17], hwndGroup[6], hwndPenSize[5];
static HWND hwndLable[6], hwndSelectColor[2], hwndColor[20], hwndButton[3], hwndBackground;
static HWND hwndStatus, hwndPenStyle[4];

static HWND hwndDrawArea;

static int width = 1250, height = 700;

HWND CreateGroupBox(HMENU hmenu) {
	return CreateWindow(TEXT("button"), NULL, WS_VISIBLE | WS_CHILD | BS_GROUPBOX, 0, 0, 0, 0, hwndToolBox, hmenu, NULL, NULL);
}

HWND CreateCheckBox(LPCWSTR str, HWND hWnd, HMENU hmenu) {
	return CreateWindow(TEXT("button"), str, WS_VISIBLE | WS_CHILD | BS_AUTOCHECKBOX, 0, 0, 0, 0, hWnd, hmenu, NULL, NULL);
}

HWND CreateRadioButton(HWND hWnd, HMENU hmenu) {
	return CreateWindow(TEXT("button"), TEXT(""), WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON, 0, 0, 0, 0, hWnd, hmenu, NULL, NULL);
}
///////////////////////////////////////////////////////// CREATE TOOLBOX
void CreateControl(HWND hWnd) {
	hwndToolBox = CreateWindow(TEXT("static"), NULL, WS_VISIBLE | WS_CHILD | BS_GROUPBOX, 0, 0, 0, 0, hWnd, (HMENU)ID_TOOLBOX, NULL, NULL);
	hwndDrawArea = CreateWindow(TEXT("static"), NULL, WS_VISIBLE | WS_CHILD | SS_GRAYFRAME, 0, 0, 0, 0, hWnd, (HMENU)ID_DRAW_AREA, NULL, NULL);
	//Group
	hwndGroup[0] = CreateGroupBox((HMENU)ID_GROUP1);//hàm ở trên
	hwndGroup[1] = CreateGroupBox((HMENU)ID_GROUP2);
	hwndGroup[2] = CreateGroupBox((HMENU)ID_GROUP3);
	hwndGroup[3] = CreateGroupBox((HMENU)ID_GROUP4);
	hwndGroup[4] = CreateGroupBox((HMENU)ID_GROUP5);
	hwndGroup[5] = CreateGroupBox((HMENU)ID_GROUP6);

	//Shape
	hwndShape[0] = CreateCheckBox(TEXT(""), hWnd, (HMENU)ID_LINE);

	hwndShape[1] = CreateCheckBox(TEXT(""), hWnd, (HMENU)ID_SHAPE_CIRCLE);
	hwndShape[2] = CreateCheckBox(TEXT(""), hWnd, (HMENU)ID_SHAPE_RECTANGLE);
	hwndShape[3] = CreateCheckBox(TEXT(""), hWnd, (HMENU)ID_SHAPE_ISOSCELES_TRIANGLE);
	hwndShape[4] = CreateCheckBox(TEXT(""), hWnd, (HMENU)ID_SHAPE_TRIANGLE);

	hwndShape[5] = CreateCheckBox(TEXT(""), hWnd, (HMENU)ID_SHAPE_QUADRILATERAL);
	hwndShape[6] = CreateCheckBox(TEXT(""), hWnd, (HMENU)ID_SHAPE_PENTAGON);
	hwndShape[7] = CreateCheckBox(TEXT(""), hWnd, (HMENU)ID_SHAPE_HEXAGON);
	hwndShape[8] = CreateCheckBox(TEXT(""), hWnd, (HMENU)ID_SHAPE_FORWARD_ARROW);
	hwndShape[9] = CreateCheckBox(TEXT(""), hWnd, (HMENU)ID_SHAPE_BACK_ARROW);

	hwndShape[10] = CreateCheckBox(TEXT(""), hWnd, (HMENU)ID_SHAPE_UP_ARROW);
	hwndShape[11] = CreateCheckBox(TEXT(""), hWnd, (HMENU)ID_SHAPE_DOWN_ARROW);
	hwndShape[12] = CreateCheckBox(TEXT(""), hWnd, (HMENU)ID_SHAPE_FOUR_POINT_STAR);
	hwndShape[13] = CreateCheckBox(TEXT(""), hWnd, (HMENU)ID_SHAPE_FIVE_POINT_STAR);
	hwndShape[14] = CreateCheckBox(TEXT(""), hWnd, (HMENU)ID_SHAPE_SIX_POINT_STAR);

	hwndShape[15] = CreateCheckBox(TEXT(""), hWnd, (HMENU)ID_SHAPE_LIGHTNING);
	hwndShape[16] = CreateCheckBox(TEXT(""), hWnd, (HMENU)ID_SHAPE_ROUND_RECT);
	//PenSize
	hwndPenSize[0] = CreateCheckBox(NULL, hWnd, (HMENU)ID_PENSIZE1);
	hwndPenSize[1] = CreateCheckBox(NULL, hWnd, (HMENU)ID_PENSIZE2);
	hwndPenSize[2] = CreateCheckBox(NULL, hWnd, (HMENU)ID_PENSIZE3);
	hwndPenSize[3] = CreateCheckBox(NULL, hWnd, (HMENU)ID_PENSIZE4);
	hwndPenSize[4] = CreateCheckBox(NULL, hWnd, (HMENU)ID_PENSIZE5);
	//Group 3
	hwndLable[0] = CreateWindow(TEXT("static"), TEXT("Color"), WS_VISIBLE | WS_CHILD | SS_CENTER, 0, 0, 0, 0, hWnd, (HMENU)ID_COLOR1, NULL, NULL);
	hwndLable[1] = CreateWindow(TEXT("static"), TEXT("1"), WS_VISIBLE | WS_CHILD | SS_CENTER, 0, 0, 0, 0, hWnd, (HMENU)ID_COLOR_NUMBER1, NULL, NULL);
	hwndSelectColor[0] = CreateWindow(TEXT("button"), TEXT(""), WS_VISIBLE | WS_CHILD | BS_AUTOCHECKBOX, 0, 0, 0, 0, hWnd, (HMENU)ID_COLOR_NUMBER_SELECT1, NULL, NULL);
	hwndLable[2] = CreateWindow(TEXT("static"), TEXT("Color"), WS_VISIBLE | WS_CHILD | SS_CENTER, 0, 0, 0, 0, hWnd, (HMENU)ID_COLOR2, NULL, NULL);
	hwndLable[3] = CreateWindow(TEXT("static"), TEXT("2"), WS_VISIBLE | WS_CHILD | SS_CENTER, 0, 0, 0, 0, hWnd, (HMENU)ID_COLOR_NUMBER2, NULL, NULL);
	hwndSelectColor[1] = CreateWindow(TEXT("button"), TEXT(""), WS_VISIBLE | WS_CHILD | BS_AUTOCHECKBOX, 0, 0, 0, 0, hWnd, (HMENU)ID_COLOR_NUMBER_SELECT2, NULL, NULL);
	//Group 4 - Color
	hwndColor[0] = CreateRadioButton(hWnd, (HMENU)ID_COLOR_BLACK);
	hwndColor[1] = CreateRadioButton(hWnd, (HMENU)ID_COLOR_DARKGRAY);
	hwndColor[2] = CreateRadioButton(hWnd, (HMENU)ID_COLOR_DARKBROWN);
	hwndColor[3] = CreateRadioButton(hWnd, (HMENU)ID_COLOR_RED);
	hwndColor[4] = CreateRadioButton(hWnd, (HMENU)ID_COLOR_DARKORANGE);
	hwndColor[5] = CreateRadioButton(hWnd, (HMENU)ID_COLOR_DARKYELLOW);
	hwndColor[6] = CreateRadioButton(hWnd, (HMENU)ID_COLOR_DARKGREEN);
	hwndColor[7] = CreateRadioButton(hWnd, (HMENU)ID_COLOR_DARKAQUA);
	hwndColor[8] = CreateRadioButton(hWnd, (HMENU)ID_COLOR_DARKBLUE);
	hwndColor[9] = CreateRadioButton(hWnd, (HMENU)ID_COLOR_DARKPURPLE);

	hwndColor[10] = CreateRadioButton(hWnd, (HMENU)ID_COLOR_WHITE);
	hwndColor[11] = CreateRadioButton(hWnd, (HMENU)ID_COLOR_LIGHTGRAY);
	hwndColor[12] = CreateRadioButton(hWnd, (HMENU)ID_COLOR_LIGHTBROWN);
	hwndColor[13] = CreateRadioButton(hWnd, (HMENU)ID_COLOR_PINK);
	hwndColor[14] = CreateRadioButton(hWnd, (HMENU)ID_COLOR_LIGHTORANGE);
	hwndColor[15] = CreateRadioButton(hWnd, (HMENU)ID_COLOR_LIGHTYELLOW);
	hwndColor[16] = CreateRadioButton(hWnd, (HMENU)ID_COLOR_LIGHTGREEN);
	hwndColor[17] = CreateRadioButton(hWnd, (HMENU)ID_COLOR_LIGHTAQUA);
	hwndColor[18] = CreateRadioButton(hWnd, (HMENU)ID_COLOR_LIGHTBLUE);
	hwndColor[19] = CreateRadioButton(hWnd, (HMENU)ID_COLOR_LIGHTPURPLE);
	//Group 4
	hwndBackground = CreateWindow(TEXT("static"), TEXT("Background"), WS_VISIBLE | WS_CHILD | SS_CENTER, 0, 0, 0, 0, hWnd, (HMENU)ID_BACKGROUND, NULL, NULL);
	hwndButton[0] = CreateWindow(TEXT("button"), TEXT("Set Color Pen"), WS_VISIBLE | WS_CHILD | SS_CENTER, 0, 0, 0, 0, hWnd, (HMENU)ID_SETCOLORPEN, NULL, NULL);
	hwndButton[1] = CreateWindow(TEXT("button"), TEXT("Set Background"), WS_VISIBLE | WS_CHILD | SS_CENTER, 0, 0, 0, 0, hWnd, (HMENU)ID_SETBACKGROUND, NULL, NULL);
	hwndButton[2] = CreateWindow(TEXT("button"), TEXT("Choose Color"), WS_VISIBLE | WS_CHILD | SS_CENTER, 0, 0, 0, 0, hWnd, (HMENU)ID_CHOOSE_COLOR, NULL, NULL);
	//Group 5
	hwndLable[4] = CreateWindow(TEXT("static"), TEXT("Choose"), WS_VISIBLE | WS_CHILD | SS_CENTER, 0, 0, 0, 0, hWnd, (HMENU)ID_LABLE_CHOOSE, NULL, NULL);
	hwndLable[5] = CreateWindow(TEXT("static"), TEXT("Color"), WS_VISIBLE | WS_CHILD | SS_CENTER, 0, 0, 0, 0, hWnd, (HMENU)ID_LABLE_COLOR, NULL, NULL);
	//Group 6
	hwndPenStyle[0] = CreateCheckBox(NULL, hWnd, (HMENU)ID_PEN_STYLE1);
	hwndPenStyle[1] = CreateCheckBox(NULL, hWnd, (HMENU)ID_PEN_STYLE2);
	hwndPenStyle[2] = CreateCheckBox(NULL, hWnd, (HMENU)ID_PEN_STYLE3);
	hwndPenStyle[3] = CreateCheckBox(NULL, hWnd, (HMENU)ID_PEN_STYLE4);
	//
	HFONT hFont = CreateFont(20, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, L"Tahoma");
	hwndStatus = CreateWindowEx(0, STATUSCLASSNAME, L"Status:", WS_CHILD | WS_VISIBLE | SBARS_SIZEGRIP, 0, height - 20, width, 20, hWnd, (HMENU)ID_STATUS_BAR, NULL, NULL);
	SendMessage(hwndStatus, WM_SETFONT, WPARAM(hFont), TRUE);
}

///////////////////////////////////////////////////////// SHOW TOOLBOX
/////////////////// Hàm move window: đăt lại vị trí và kích thước cửa sổ: parameter1: cửa sổ cần thay đổi
////////////////// parameter 2,3: vị trí left,top
////////////////// parameter 4,5: kích thước cửa sổ width,height
void ShowToolBox() {
	MoveWindow(hwndToolBox, 0, 0, width, 125, TRUE);
	MoveWindow(hwndGroup[0], 10, 0, 350, 120, TRUE);
	MoveWindow(hwndGroup[1], 370, 0, 75, 120, TRUE);
	MoveWindow(hwndGroup[2], 455, 0, 130, 120, TRUE);
	MoveWindow(hwndGroup[3], 595, 0, 250, 120, TRUE);
	MoveWindow(hwndGroup[4], 855, 0, 225, 120, TRUE);
	MoveWindow(hwndGroup[5], 1090, 0, 135, 120, TRUE);

	//Shape
	MoveWindow(hwndShape[0], 15, 15, 18, 20, TRUE);
	MoveWindow(hwndShape[1], 15, 35, 18, 20, TRUE);
	MoveWindow(hwndShape[2], 15, 55, 18, 20, TRUE);
	MoveWindow(hwndShape[3], 15, 75, 18, 20, TRUE);
	MoveWindow(hwndShape[4], 15, 95, 18, 20, TRUE);

	MoveWindow(hwndShape[5], 95, 15, 18, 20, TRUE);
	MoveWindow(hwndShape[6], 95, 35, 18, 20, TRUE);
	MoveWindow(hwndShape[7], 95, 55, 18, 20, TRUE);
	MoveWindow(hwndShape[8], 95, 75, 18, 20, TRUE);
	MoveWindow(hwndShape[9], 95, 95, 18, 20, TRUE);

	MoveWindow(hwndShape[10], 190, 15, 18, 20, TRUE);
	MoveWindow(hwndShape[11], 190, 35, 18, 20, TRUE);
	MoveWindow(hwndShape[12], 190, 55, 18, 20, TRUE);
	MoveWindow(hwndShape[13], 190, 75, 18, 20, TRUE);
	MoveWindow(hwndShape[14], 190, 95, 18, 20, TRUE);

	MoveWindow(hwndShape[15], 285, 35, 18, 20, TRUE);
	MoveWindow(hwndShape[16], 285, 75, 18, 20, TRUE);
	//PenSize
	MoveWindow(hwndPenSize[0], 375, 15, 15, 20, TRUE);
	MoveWindow(hwndPenSize[1], 375, 35, 15, 20, TRUE);
	MoveWindow(hwndPenSize[2], 375, 55, 15, 20, TRUE);
	MoveWindow(hwndPenSize[3], 375, 75, 15, 20, TRUE);
	MoveWindow(hwndPenSize[4], 375, 95, 15, 20, TRUE);
	//Group 3
	MoveWindow(hwndLable[0], 465, 75, 50, 20, TRUE);
	MoveWindow(hwndLable[1], 465, 95, 50, 20, TRUE);
	MoveWindow(hwndSelectColor[0], 465, 95, 20, 20, TRUE);
	MoveWindow(hwndLable[2], 520, 75, 50, 20, TRUE);
	MoveWindow(hwndLable[3], 520, 95, 50, 20, TRUE);
	MoveWindow(hwndSelectColor[1], 520, 95, 20, 20, TRUE);
	//Group 4 - Color
	MoveWindow(hwndColor[0], 600, 45, 15, 15, TRUE);
	MoveWindow(hwndColor[1], 625, 45, 15, 15, TRUE);
	MoveWindow(hwndColor[2], 650, 45, 15, 15, TRUE);
	MoveWindow(hwndColor[3], 675, 45, 15, 15, TRUE);
	MoveWindow(hwndColor[4], 700, 45, 15, 15, TRUE);
	MoveWindow(hwndColor[5], 725, 45, 15, 15, TRUE);
	MoveWindow(hwndColor[6], 750, 45, 15, 15, TRUE);
	MoveWindow(hwndColor[7], 775, 45, 15, 15, TRUE);
	MoveWindow(hwndColor[8], 800, 45, 15, 15, TRUE);
	MoveWindow(hwndColor[9], 825, 45, 15, 15, TRUE);

	MoveWindow(hwndColor[10], 600, 95, 15, 15, TRUE);
	MoveWindow(hwndColor[11], 625, 95, 15, 15, TRUE);
	MoveWindow(hwndColor[12], 650, 95, 15, 15, TRUE);
	MoveWindow(hwndColor[13], 675, 95, 15, 15, TRUE);
	MoveWindow(hwndColor[14], 700, 95, 15, 15, TRUE);
	MoveWindow(hwndColor[15], 725, 95, 15, 15, TRUE);
	MoveWindow(hwndColor[16], 750, 95, 15, 15, TRUE);
	MoveWindow(hwndColor[17], 775, 95, 15, 15, TRUE);
	MoveWindow(hwndColor[18], 800, 95, 15, 15, TRUE);
	MoveWindow(hwndColor[19], 825, 95, 15, 15, TRUE);
	//Group 4
	MoveWindow(hwndBackground, 865, 90, 90, 20, TRUE);
	MoveWindow(hwndButton[0], 960, 15, 110, 30, TRUE);
	MoveWindow(hwndButton[1], 960, 50, 110, 30, TRUE);
	MoveWindow(hwndButton[2], 960, 85, 110, 30, TRUE);
	//Group 5
	MoveWindow(hwndLable[4], 1095, 65, 50, 20, TRUE);
	MoveWindow(hwndLable[5], 1095, 85, 50, 20, TRUE);
	//Group 6
	MoveWindow(hwndPenStyle[0], 1150, 15, 15, 20, TRUE);
	MoveWindow(hwndPenStyle[1], 1150, 40, 15, 20, TRUE);
	MoveWindow(hwndPenStyle[2], 1150, 65, 15, 20, TRUE);
	MoveWindow(hwndPenStyle[3], 1150, 90, 15, 20, TRUE);

}


void SetWindowHide(HWND hwnd) {
	MoveWindow(hwnd, 0, 0, 0, 0, TRUE);
}

//////////////////////////////////////// HIDE TOOLBOX 
void HideToolBox() {
	SetWindowHide(hwndToolBox); //Hàm ở trên
	SetWindowHide(hwndGroup[0]);
	SetWindowHide(hwndGroup[1]);
	SetWindowHide(hwndGroup[2]);
	SetWindowHide(hwndGroup[3]);
	SetWindowHide(hwndGroup[4]);
	SetWindowHide(hwndGroup[5]);

	//Shape
	SetWindowHide(hwndShape[0]);
	SetWindowHide(hwndShape[1]);
	SetWindowHide(hwndShape[2]);
	SetWindowHide(hwndShape[3]);
	SetWindowHide(hwndShape[4]);

	SetWindowHide(hwndShape[5]);
	SetWindowHide(hwndShape[6]);
	SetWindowHide(hwndShape[7]);
	SetWindowHide(hwndShape[8]);
	SetWindowHide(hwndShape[9]);

	SetWindowHide(hwndShape[10]);
	SetWindowHide(hwndShape[11]);
	SetWindowHide(hwndShape[12]);
	SetWindowHide(hwndShape[13]);
	SetWindowHide(hwndShape[14]);

	SetWindowHide(hwndShape[15]);
	SetWindowHide(hwndShape[16]);
	//PenSize
	SetWindowHide(hwndPenSize[0]);
	SetWindowHide(hwndPenSize[1]);
	SetWindowHide(hwndPenSize[2]);
	SetWindowHide(hwndPenSize[3]);
	SetWindowHide(hwndPenSize[4]);
	//Group 3
	SetWindowHide(hwndLable[0]);
	SetWindowHide(hwndLable[1]);
	SetWindowHide(hwndSelectColor[0]);
	SetWindowHide(hwndLable[2]);
	SetWindowHide(hwndLable[3]);
	SetWindowHide(hwndSelectColor[1]);
	//Group 4 - Color
	SetWindowHide(hwndColor[0]);
	SetWindowHide(hwndColor[1]);
	SetWindowHide(hwndColor[2]);
	SetWindowHide(hwndColor[3]);
	SetWindowHide(hwndColor[4]);
	SetWindowHide(hwndColor[5]);
	SetWindowHide(hwndColor[6]);
	SetWindowHide(hwndColor[7]);
	SetWindowHide(hwndColor[8]);
	SetWindowHide(hwndColor[9]);

	SetWindowHide(hwndColor[10]);
	SetWindowHide(hwndColor[11]);
	SetWindowHide(hwndColor[12]);
	SetWindowHide(hwndColor[13]);
	SetWindowHide(hwndColor[14]);
	SetWindowHide(hwndColor[15]);
	SetWindowHide(hwndColor[16]);
	SetWindowHide(hwndColor[17]);
	SetWindowHide(hwndColor[18]);
	SetWindowHide(hwndColor[19]);
	//Group 4
	SetWindowHide(hwndBackground);
	SetWindowHide(hwndButton[0]);
	SetWindowHide(hwndButton[1]);
	SetWindowHide(hwndButton[2]);
	//Group 5
	SetWindowHide(hwndLable[4]);
	SetWindowHide(hwndLable[5]);
	//Group 6
	SetWindowHide(hwndPenStyle[0]);
	SetWindowHide(hwndPenStyle[1]);
	SetWindowHide(hwndPenStyle[2]);
	SetWindowHide(hwndPenStyle[3]);
}