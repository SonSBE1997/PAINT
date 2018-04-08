#include "stdafx.h"
#include "Paint.h"
#include <stack>
#include <commctrl.h>
#include <string>
#include <fstream>
#include <Commdlg.h>
#include <windowsx.h>
#include <shellapi.h>
#include <commdlg.h>
#include <stdio.h>
#include <vector>
// for export image
//#include <atlstr.h>
//#include <atlimage.h>
#include "SaveBitmap.h"
#include "ReadBitmapFile.h"
////
#include  "PaintToolBox.h"
#include "MyColor.h"
#include "Identified.h"
#include "Shape.h"
#include "CreateToolBox.h"
using namespace std;


#pragma warning(disable:4996)
// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

////////////////////////////

static HDC hdc;
static HPEN hPen;
static HBRUSH hBrush;

static int positionShape = 1; //vị trí shape đang lựa chon -- dùng để thay đổi shape ( checkbox)
static int penSize = 1, currentSelectedPenStyle = PS_SOLID;

static RECT  currentWindowPosition; //vị trí cửa sổ window trc khi reload lại 
static ShapeMode selectedShapeMode = ShapeMode::LINE; // kiểu hình đang chọn
static POINT p[2]; // tọa độ khi mouse down và mouse up
static COLORREF currentSelectColor;			//màu đang lựa chọn -- radio button color

static int positionColor = 0; //vị trí lựa chọn radio button color trc khi an hien thanh toolbar
static HMENU hMenu;

static bool  isShowToolBox = true, isMouseDown = false;
vector<Shape*> shapes; // chứa các hình vẽ
stack<Shape*> redoShapes; // dùng cho redo
int lastSizeShape = 0; // dùng cho undo & redo
////////////////////////////
CHOOSECOLOR choosecolor;
DWORD rgbCurrent;
static COLORREF acrCustClr[16];
COLORREF lastChooseColor = NULL;
static HWND hwndMain;
// Check open file
static int orderOpen = 0;
static bool isOpenFile = false;
static wstring openFilename;
///////////////////////////////////////////////////////////////
// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
void ExportImage();
void OpenImage();
void OpenBitmapByFileName(wstring openFilename);
void SaveImage();

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: Place code here.

	// Initialize global strings
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_PAINT, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(ID_MyACCEL));

	MSG msg;

	// Main message loop:
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int)msg.wParam;
}


//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MYPAINT));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_PAINT);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_MYPAINT));
	hMenu = LoadMenu(hInstance, MAKEINTRESOURCE(IDC_PAINT));

	return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // Store instance handle in our global variable
	//(WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX)
	HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW | ES_AUTOHSCROLL | ES_AUTOVSCROLL,
		0, 0, width, height, nullptr, nullptr, hInstance, nullptr);
	hwndMain = hWnd;
	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

void ClickCheckBoxShape(int pos, ShapeMode mode) {
	if (positionShape == pos) {
		SendMessage(hwndShape[pos - 1], BM_SETCHECK, 1, 0);
		return;
	}
	positionShape = pos;
	for (int i = 0; i < 17; i++) {
		if (i != positionShape - 1) SendMessage(hwndShape[i], BM_SETCHECK, 0, 0);
	}
	selectedShapeMode = mode;
}


void ReDrawShapes(HWND hWnd) {
	MoveWindow(hWnd, currentWindowPosition.left, currentWindowPosition.top, 0, 0, TRUE);
	MoveWindow(hWnd, currentWindowPosition.left, currentWindowPosition.top, 1250, 700, TRUE);

	for (int i = 0; i < shapes.size(); i++) {
		shapes[i]->Draw(GetDC(hwndDrawArea), isShowToolBox);
		if (i == orderOpen && isOpenFile) {
			OpenBitmapByFileName(openFilename);
		}
	}
}


void SetPenStyle(int penStyle, int pos) {
	if (currentSelectedPenStyle == penStyle) {
		SendMessage(hwndPenStyle[pos], BM_SETCHECK, 1, 0);
		return;
	}
	currentSelectedPenStyle = penStyle;
	for (int i = 0; i < 4; i++) {
		if (i == pos) continue;
		SendMessage(hwndPenStyle[i], BM_SETCHECK, 0, 0);
	}
}

bool MouseUP(HWND hWnd, LPARAM lParam, COLORREF colorBorder) {
	if (!isMouseDown) return false;
	if (isShowToolBox && HIWORD(lParam) < 125) {
		isMouseDown = false;
		return false;
	}
	hdc = GetDC(hwndDrawArea);
	p[1].x = LOWORD(lParam);
	p[1].y = HIWORD(lParam);
	Shape* newShape = new Shape();
	newShape->setPosition(p[0], p[1]);
	newShape->setShapeMode(selectedShapeMode);
	newShape->setStyle(colorBorder, currentBackgroundColor, penSize, currentSelectedPenStyle);
	newShape->setIsShowTool(isShowToolBox);
	newShape->Draw(hdc, isShowToolBox);
	shapes.push_back(newShape);
	return true;
}
//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

	switch (message)
	{
	case WM_CREATE:
	{
		CreateControl(hWnd);
		//SetWindowLong(hwndButton[0], GCLP_HBRBACKGROUND, COLOR_BTNHILIGHT);
		SendMessage(hwndShape[0], BM_SETCHECK, 1, 0); //Đặt trạng thái đã check cho cửa sổ (chỉ dùng cho loại button)
		SendMessage(hwndPenSize[0], BM_SETCHECK, 1, 0);
		SendMessage(hwndSelectColor[0], BM_SETCHECK, 1, 0);
		SendMessage(hwndColor[0], BM_SETCHECK, 1, 0);
		SendMessage(hwndPenStyle[0], BM_SETCHECK, 1, 0);
		currentSelectColor = Black(); //Đặt màu mặc định: hàm black(),... trong file MyColor.h ở thư mục header file
		currentBorderColor1 = Black();
		currentBorderColor2 = White();
		currentBackgroundColor = White();
		CheckMenuItem(hMenu, ID_VIEW_TOOLBOX, MF_CHECKED);  //Đặt trạng thái check trong menu View-> ToolBox
		ShowToolBox(); // hiển thị toolbox lên
		break;
	}
	case WM_SIZE: //khi kích thước cửa sổ chính của chương trình thay đổi mới chạy vào phần này, khi mới chạy chương trình cũng nhảy vào đây
	{
		width = LOWORD(lParam);
		height = HIWORD(lParam);
		MoveWindow(hwndStatus, 0, height - 20, width, 20, TRUE);
		if (isShowToolBox) {  //nếu toolbox đc hiển thị thì vẽ các ô màu trong toolbox
			MoveWindow(hwndToolBox, 0, 0, width, 125, TRUE);
			MoveWindow(hwndDrawArea, 0, 125, width, height - 151, TRUE);
			setToolBoxColor(hdc, hWnd, hPen, hBrush); //Xem trong file PaintToolBox.h
			if (lastChooseColor != NULL) {
				hdc = GetDC(hWnd);
				hPen = CreatePen(PS_SOLID, 1, Black());
				SelectObject(hdc, hPen);
				hBrush = CreateSolidBrush(currentSelectColor);
				SelectObject(hdc, hBrush);
				Rectangle(hdc, 1100, 20, 1135, 55);
				ReleaseDC(hWnd, hdc);
			}
		}
		else {
			MoveWindow(hwndDrawArea, 0, 0, width, height - 26, TRUE);
			MoveWindow(hwndToolBox, 0, 0, 0, 0, TRUE);
		}
		break;
	}
	case WM_CTLCOLORBTN:
	{
		hBrush = CreateSolidBrush(GetSysColor(COLOR_BTNHIGHLIGHT));
		SetBkMode(GetDC(hwndShape[0]), TRANSPARENT);
		SetBkColor(GetDC(hwndShape[0]), GetSysColor(COLOR_BTNHIGHLIGHT));
		return (LRESULT)hBrush;
	}
	case WM_SYSCOLORCHANGE:
		DeleteObject(hBrush);
		hBrush = CreateSolidBrush(GetSysColor(COLOR_BTNHIGHLIGHT));
		return 0;
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		switch (wmId)
		{
		case ID_COLOR_NUMBER_SELECT1:
		{
			SendMessage(hwndSelectColor[1], BM_SETCHECK, 0, 0);
			break;
		}
		case ID_COLOR_NUMBER_SELECT2:
		{
			SendMessage(hwndSelectColor[0], BM_SETCHECK, 0, 0);
			break;
		}
		case ID_SETCOLORPEN:
		{
			hdc = GetDC(hWnd);
			hPen = CreatePen(PS_SOLID, 1, Black());
			SelectObject(hdc, hPen);
			int colorSelected = SendMessage(hwndSelectColor[0], BM_GETCHECK, 0, 0);

			if (colorSelected == 0) {
				currentBorderColor2 = currentSelectColor;
				PaintColor2ToolBox(hdc, hBrush);
			}
			else {
				currentBorderColor1 = currentSelectColor;
				PaintColor1ToolBox(hdc, hBrush);
			}
			break;
		}
		case ID_SETBACKGROUND:
		{
			currentBackgroundColor = currentSelectColor;
			hdc = GetDC(hWnd);
			hPen = CreatePen(PS_SOLID, 1, Black());
			SelectObject(hdc, hPen);
			PaintBackgroundToolBox(hdc, hBrush);
			ReleaseDC(hWnd, hdc);
			break;
		}
		case ID_CHOOSE_COLOR:
		{

			memset(&choosecolor, 0, sizeof(CHOOSECOLOR));
			choosecolor.lStructSize = sizeof(CHOOSECOLOR);
			choosecolor.hwndOwner = hWnd;
			choosecolor.Flags = CC_FULLOPEN | CC_RGBINIT;
			choosecolor.lpCustColors = acrCustClr;
			choosecolor.rgbResult = rgbCurrent;
			if (ChooseColor(&choosecolor)) {
				rgbCurrent = choosecolor.rgbResult;
				lastChooseColor = currentSelectColor = rgbCurrent;

				hdc = GetDC(hWnd);
				hPen = CreatePen(PS_SOLID, 1, Black());
				SelectObject(hdc, hPen);
				hBrush = CreateSolidBrush(currentSelectColor);
				SelectObject(hdc, hBrush);
				Rectangle(hdc, 1100, 20, 1135, 55);
				ReleaseDC(hWnd, hdc);
				SendMessage(hwndColor[positionColor], BM_SETCHECK, 0, 0);
			}
			break;
		}

		case ID_COLOR_WHITE:
			positionColor = 10;
			currentSelectColor = White();
			break;
		case ID_COLOR_LIGHTGRAY:
			positionColor = 11;
			currentSelectColor = LightGray();
			break;
		case ID_COLOR_LIGHTBROWN:
			positionColor = 12;
			currentSelectColor = LightBrown();
			break;
		case ID_COLOR_PINK:
			positionColor = 13;
			currentSelectColor = Pink();
			break;
		case ID_COLOR_LIGHTORANGE:
			positionColor = 14;
			currentSelectColor = LightOrange();
			break;
		case ID_COLOR_LIGHTYELLOW:
			positionColor = 15;
			currentSelectColor = LightYellow();
			break;
		case ID_COLOR_LIGHTGREEN:
			positionColor = 16;
			currentSelectColor = LightGreen();
			break;
		case ID_COLOR_LIGHTAQUA:
			positionColor = 17;
			currentSelectColor = LightAqua();
			break;
		case ID_COLOR_LIGHTBLUE:
			positionColor = 18;
			currentSelectColor = LightBlue();
			break;
		case ID_COLOR_LIGHTPURPLE:
			positionColor = 19;
			currentSelectColor = LightPurple();
			break;
		case ID_COLOR_BLACK:
			positionColor = 0;
			currentSelectColor = Black();
			break;
		case ID_COLOR_DARKGRAY:
			positionColor = 1;
			currentSelectColor = DarkGray();
			break;
		case ID_COLOR_DARKBROWN:
			positionColor = 2;
			currentSelectColor = DarkBrown();
			break;
		case ID_COLOR_RED:
			positionColor = 3;
			currentSelectColor = Red();
			break;
		case ID_COLOR_DARKORANGE:
			positionColor = 4;
			currentSelectColor = DarkOrange();
			break;
		case ID_COLOR_DARKYELLOW:
			positionColor = 5;
			currentSelectColor = DarkYellow();
			break;
		case ID_COLOR_DARKGREEN:
			positionColor = 6;
			currentSelectColor = DarkGreen();
			break;
		case ID_COLOR_DARKAQUA:
			positionColor = 7;
			currentSelectColor = DarkAqua();
			break;
		case ID_COLOR_DARKBLUE:
			positionColor = 8;
			currentSelectColor = DarkBlue();
			break;
		case ID_COLOR_DARKPURPLE:
			positionColor = 9;
			currentSelectColor = DarkPurple();
			break;
			/////
		case ID_LINE:
			ClickCheckBoxShape(1, ShapeMode::LINE);
			break;
		case ID_SHAPE_CIRCLE:
			ClickCheckBoxShape(2, ShapeMode::CIRCLE);
			break;
		case ID_SHAPE_RECTANGLE:
			ClickCheckBoxShape(3, ShapeMode::RECTANGLE);
			break;
		case ID_SHAPE_ISOSCELES_TRIANGLE:
			ClickCheckBoxShape(4, ShapeMode::ISOSCELES_TRIANGLE);
			break;
		case ID_SHAPE_TRIANGLE:
			ClickCheckBoxShape(5, ShapeMode::TRIANGLE);
			break;
		case ID_SHAPE_QUADRILATERAL:
			ClickCheckBoxShape(6, ShapeMode::QUADRILATERAL);
			break;
		case ID_SHAPE_PENTAGON:
			ClickCheckBoxShape(7, ShapeMode::PENTAGON);
			break;
		case ID_SHAPE_HEXAGON:
			ClickCheckBoxShape(8, ShapeMode::HEXAGON);
			break;
		case ID_SHAPE_FORWARD_ARROW:
			ClickCheckBoxShape(9, ShapeMode::FORWARD_ARROW);
			break;
		case ID_SHAPE_BACK_ARROW:
			ClickCheckBoxShape(10, ShapeMode::BACK_ARROW);
			break;
		case ID_SHAPE_UP_ARROW:
			ClickCheckBoxShape(11, ShapeMode::UP_ARROW);
			break;
		case ID_SHAPE_DOWN_ARROW:
			ClickCheckBoxShape(12, ShapeMode::DOWN_ARROW);
			break;
		case ID_SHAPE_FOUR_POINT_STAR:
			ClickCheckBoxShape(13, ShapeMode::FOUR_POINT_STAR);
			break;
		case ID_SHAPE_FIVE_POINT_STAR:
			ClickCheckBoxShape(14, ShapeMode::FIVE_POINT_STAR);
			break;
		case ID_SHAPE_SIX_POINT_STAR:
			ClickCheckBoxShape(15, ShapeMode::SIX_POINT_STAR);
			break;
		case ID_SHAPE_LIGHTNING:
			ClickCheckBoxShape(16, ShapeMode::LIGHTNING);
			break;
		case ID_SHAPE_ROUND_RECT:
			ClickCheckBoxShape(17, ShapeMode::ROUND_RECT);
			break;
		case IDM_ABOUT:
		{
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		}
		case IDM_EXIT:
			SaveImage();
			DestroyWindow(hWnd);
			break;
			//////
		case ID_PENSIZE1:
			if (penSize != 1) SendMessage(hwndPenSize[penSize - 1], BM_SETCHECK, 0, 0);
			penSize = 1;
			break;
		case ID_PENSIZE2:
			SendMessage(hwndPenSize[penSize - 1], BM_SETCHECK, 0, 0); penSize = 2;
			break;
		case ID_PENSIZE3:
			SendMessage(hwndPenSize[penSize - 1], BM_SETCHECK, 0, 0); penSize = 3;
			break;
		case ID_PENSIZE4:
			SendMessage(hwndPenSize[penSize - 1], BM_SETCHECK, 0, 0); penSize = 4;
			break;
		case ID_PENSIZE5:
			SendMessage(hwndPenSize[penSize - 1], BM_SETCHECK, 0, 0); penSize = 5;
			break;
			/////
			/////
		case ID_PEN_STYLE1:
			SetPenStyle(PS_SOLID, 0);
			break;
		case ID_PEN_STYLE2:
			SetPenStyle(PS_DOT, 1);
			break;
		case ID_PEN_STYLE3:
			SetPenStyle(PS_DASHDOT, 2);
			break;
		case ID_PEN_STYLE4:
			SetPenStyle(PS_DASH, 3);
			break;
			//////

		case ID_VIEW_TOOLBOX:
		{
			isShowToolBox = GetMenuState(hMenu, ID_VIEW_TOOLBOX, MF_BYCOMMAND);
			if (isShowToolBox) {
				CheckMenuItem(hMenu, ID_VIEW_TOOLBOX, MF_UNCHECKED);
				isShowToolBox = false;
				HideToolBox();
				SetMenu(hWnd, hMenu);
			}
			else {
				CheckMenuItem(hMenu, ID_VIEW_TOOLBOX, MF_CHECKED);
				isShowToolBox = true;
				ShowToolBox();
				SetMenu(hWnd, hMenu);
				setToolBoxColor(hdc, hWnd, hPen, hBrush);
			}
			ReDrawShapes(hWnd);
			break;
		}
		case IDM_FILE_NEW: {
			SaveImage();
			shapes.clear();
			while (redoShapes.size() != 0) redoShapes.pop();
			ReDrawShapes(hWnd);
			break;
		}
		case ID_EDIT_REDO:
		{

			if (lastSizeShape != shapes.size()) {
				while (redoShapes.size() != 0) redoShapes.pop();
				break;
			}
			if (redoShapes.empty()) break;
			Shape* s = redoShapes.top();
			redoShapes.pop();
			shapes.push_back(s);
			lastSizeShape = shapes.size();
			ReDrawShapes(hWnd);
			break;
		}
		case IDM_EDIT_Undo:
		{
			if (shapes.size() == 0) break;
			Shape* s = shapes[shapes.size() - 1];
			shapes.pop_back();
			lastSizeShape = shapes.size();
			redoShapes.push(s);
			ReDrawShapes(hWnd);

			break;
		}
		case ID_FILE_EXPORTIMAGE:
		{
			ExportImage();
			break;
		}
		case ID_FILE_OPEN:
		{
			OpenImage();
			break;
		}
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	case WM_MOVE:
		GetWindowRect(hWnd, &currentWindowPosition);
		break;
	case WM_LBUTTONDOWN:
	case WM_RBUTTONDOWN:
		p[0].x = LOWORD(lParam);
		p[0].y = HIWORD(lParam);
		if (isShowToolBox && HIWORD(lParam) < 125) isMouseDown = false;
		else isMouseDown = true;
		break;
	case WM_LBUTTONUP:
	{
		MouseUP(hWnd, lParam, currentBorderColor1);
		break;
	}
	case WM_RBUTTONUP:
	{
		MouseUP(hWnd, lParam, currentBorderColor2);
		break;
	}
	case WM_MOUSEMOVE:
	{
		int x = GET_X_LPARAM(lParam);
		int y = GET_Y_LPARAM(lParam);

		//Status bar
		WCHAR buffer[128];
		if (isShowToolBox) {
			if (y < 125) x = y = 0;
		}
		wsprintf(buffer, L"%d x %d px", x, y);
		SetWindowText(hwndStatus, buffer);
		break;
	}

	case WM_PAINT:
	{
		SetBkColor(GetDC(hwndShape[0]), GetSysColor(COLOR_BTNHILIGHT));
		SetBkMode(GetDC(hwndShape[0]), TRANSPARENT);
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
	}
	break;
	case WM_CLOSE:
		SaveImage();
		PostQuitMessage(0);
		break;
	case WM_DESTROY:
		SetClassLong(hWnd, GCL_HBRBACKGROUND, (LONG)
			GetStockObject(WHITE_BRUSH));
		if (hPen != NULL) DeleteObject(hPen);
		if (hBrush != NULL) DeleteObject(hBrush);
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

void SaveImage() {
	if (shapes.size() <= 0) return;
	int result = MessageBox(hwndDrawArea, L"Do u wanna save file??", L"Save Image", MB_YESNO | MB_ICONQUESTION);
	if (result == 6) {
		ExportImage();
	}
}

void ExportImage() {
	OPENFILENAME ofn;
	WCHAR szFileName[MAX_PATH] = L"";

	ZeroMemory(&ofn, sizeof(ofn));

	ofn.lStructSize = sizeof(ofn); // SEE NOTE BELOW
	ofn.hwndOwner = hwndMain;
	ofn.lpstrFilter = L"Bitmap Files (*.bmp)\0*.bin\0PNG (*.png)\0*.png\0JPEG (*.jpg)\0*.jpg";
	ofn.lpstrFile = szFileName;
	ofn.nMaxFile = MAX_PATH;
	ofn.Flags = OFN_EXPLORER | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT;
	ofn.lpstrDefExt = L"bmp";

	if (GetSaveFileName(&ofn))
	{
		wstring ws(szFileName);
		/////////////////Handle Save Bmp
		//string fileName(ws.begin(), ws.end());
		//HDC -> HBitMap

		HDC hDC = GetDC(hwndDrawArea);
		HDC hTargetDC = CreateCompatibleDC(hDC);
		RECT rect = { 0 };
		GetWindowRect(hwndDrawArea, &rect);
		HBITMAP hBitmap = CreateCompatibleBitmap(hDC, rect.right - rect.left,
			rect.bottom - rect.top);
		SelectObject(hTargetDC, hBitmap);
		//PrintWindow(hwndDrawArea, hTargetDC, PW_CLIENTONLY);
		BitBlt(hTargetDC, 0, 0, rect.right, rect.bottom, hDC, 0, 0, SRCCOPY);
		PBITMAPINFO pbmi = CreateBitmapInfoStruct(hwndDrawArea, hBitmap);
		CreateBMPFile(hwndDrawArea, ws.c_str(), pbmi, hBitmap, hDC);
		DeleteObject(hBitmap);
		ReleaseDC(hwndDrawArea, hDC);
		DeleteDC(hTargetDC);
	}
}

void OpenImage() {
	OPENFILENAME ofn;
	WCHAR szFilePath[MAX_PATH] = L"";
	WCHAR szFileTitle[MAX_PATH] = L"";

	ZeroMemory(&ofn, sizeof(ofn));

	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = hwndMain;
	ofn.lpstrFilter = L"Bitmap Files (*.bmp)\0*.bin\0PNG (*.png)\0*.png\0JPEG (*.jpg)\0*.jpg";
	ofn.lpstrFile = szFilePath;
	ofn.lpstrFileTitle = szFileTitle;
	ofn.nMaxFile = MAX_PATH;
	ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
	ofn.lpstrDefExt = L"bmp";

	if (GetOpenFileName(&ofn))
	{
		wstring ws(szFilePath);
		//string fileName(ws.begin(), ws.end());
		openFilename = ws;
		isOpenFile = true;
		orderOpen = shapes.size() - 1;
		OpenBitmapByFileName(openFilename);
	}
}

void OpenBitmapByFileName(wstring openFilename) {
	HBITMAP       hBitmap, hOldBitmap;
	HPALETTE      hPalette, hOldPalette;
	HDC           hMemDC;
	BITMAP        bm;
	HDC hDC = GetDC(hwndDrawArea);

	if (LoadBitmapFromBMPFile(openFilename.c_str(), &hBitmap, &hPalette))
	{
		GetObject(hBitmap, sizeof(BITMAP), &bm);
		hMemDC = CreateCompatibleDC(hDC);
		hOldBitmap = (HBITMAP)SelectObject(hMemDC, hBitmap);
		hOldPalette = SelectPalette(hDC, hPalette, FALSE);
		RealizePalette(hDC); //nhan dang mau

							 // copy hMemDC to hdc
		BitBlt(hDC, 0, 0, bm.bmWidth, bm.bmHeight,
			hMemDC, 0, 0, SRCCOPY);

		SelectObject(hMemDC, hOldBitmap);
		DeleteObject(hBitmap);
		SelectPalette(hDC, hOldPalette, FALSE);
		DeleteObject(hPalette);
	}
}