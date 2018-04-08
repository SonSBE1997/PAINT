#pragma once
#include <Windows.h>
#include <stdio.h>
#include <string>
using namespace std;
#pragma warning(disable:4996)

void errhandler(LPCWSTR mess, HWND hwnd) {
	MessageBox(hwnd, mess, L"Error", MB_OK | MB_ICONERROR);
}

PBITMAPINFO CreateBitmapInfoStruct(HWND hwnd, HBITMAP hBmp)
{

	//Khai báo các variable
	BITMAP bmp;
	PBITMAPINFO pbmi;
	WORD    cClrBits;

	//Lấy format color, width, height từ hBitmap  
	if (!GetObject(hBmp, sizeof(BITMAP), (LPSTR)&bmp))
		errhandler(L"GetObject", hwnd);

	// Chuyển định dạng color về số bit theo pixel và theo hệ màu (bit per pixel)
	cClrBits = (WORD)(bmp.bmPlanes * bmp.bmBitsPixel);
	if (cClrBits == 1)
		cClrBits = 1;
	else if (cClrBits <= 4)
		cClrBits = 4;
	else if (cClrBits <= 8)
		cClrBits = 8;
	else if (cClrBits <= 16)
		cClrBits = 16;
	else if (cClrBits <= 24)
		cClrBits = 24;
	else cClrBits = 32;

	// cấp phát bộ nhớ cho cấu trúc BITMAPINFO . ( BITMAPINFO chứa cấu trúc BITMAPINFOHEADER và mảng cấu trúc dữ liệu RGBQUAD);
	// không có mảng dữ liệu RGBQUAD cho các định dạng color: 24-bit-per-pixel or 32-bit-per-pixel 
	if (cClrBits < 24)
		pbmi = (PBITMAPINFO)LocalAlloc(LPTR,
			sizeof(BITMAPINFOHEADER) +
			sizeof(RGBQUAD) * (1 << cClrBits));
	else
		pbmi = (PBITMAPINFO)LocalAlloc(LPTR,
			sizeof(BITMAPINFOHEADER));

	// Khởi tạo các attribute của cấu trúc BITMAPINFO.  
	pbmi->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	pbmi->bmiHeader.biWidth = bmp.bmWidth;
	pbmi->bmiHeader.biHeight = bmp.bmHeight;
	pbmi->bmiHeader.biPlanes = bmp.bmPlanes;
	pbmi->bmiHeader.biBitCount = bmp.bmBitsPixel;
	if (cClrBits < 24)
		pbmi->bmiHeader.biClrUsed = (1 << cClrBits); // dịch bit sang trai 1
	//đặt thuộc tính không nén file bitmap
	pbmi->bmiHeader.biCompression = BI_RGB;

	// Tính số byte trong mảng các màu 
	// lưu trữ kết quả tính được biSizeImage.  
	// Chiều rộng phải được canh lề là DWORD, trừ khi bitmap là RLE
	pbmi->bmiHeader.biSizeImage = ((pbmi->bmiHeader.biWidth * cClrBits + 31) & ~31) / 8
		* pbmi->bmiHeader.biHeight;

	// đặt biClrImportant về 0 để chỉ ra rằng tất cả các màu sắc thiết bị là quan trọng. 
	pbmi->bmiHeader.biClrImportant = 0;
	return pbmi;
}

void CreateBMPFile(HWND hwnd, LPCWSTR pszFile, PBITMAPINFO pbi, HBITMAP hBMP, HDC hDC)
{
	//variable
	HANDLE hf;                 // file xử lý: tạo mới 
	BITMAPFILEHEADER hdr;       // bitmap file-header  
	PBITMAPINFOHEADER pbih;     // bitmap info-header  
	LPBYTE lpBits;              // con trỏ bộ nhớ  
	DWORD dwTotal;              // tổng số lượng byte
	DWORD cb;                   // số byte tăng thêm 
	BYTE *hp;                   // con trỏ byte 
	DWORD dwTmp;				// biến tạm thời 

	pbih = (PBITMAPINFOHEADER)pbi; //header nằm trong cấu trúc info
	lpBits = (LPBYTE)GlobalAlloc(GMEM_FIXED, pbih->biSizeImage); //cấp phát bộ nhớ

	if (!lpBits) errhandler(L"GlobalAlloc", hwnd); // cấp phát lõi -> báo lỗi

	// Nhận bảng màu (mảng RGBQUAD) và số bits (mảng các chỉ số bảng màu) từ DIB //đọc pixel từ hbitmap
	if (!GetDIBits(hDC, hBMP, 0, (WORD)pbih->biHeight, lpBits, pbi, DIB_RGB_COLORS))
	{
		errhandler(L"GetDIBits", hwnd);
	}

	// Tạo file .bmp
	hf = CreateFile(pszFile, GENERIC_READ | GENERIC_WRITE, (DWORD)0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, (HANDLE)NULL);
	if (hf == INVALID_HANDLE_VALUE)
		errhandler(L"CreateFile", hwnd);
	hdr.bfType = 0x4d42;        // 0x42 = "B" 0x4d = "M"  

	//Tính toán kích thước của toàn bộ file.
	hdr.bfSize = (DWORD)(sizeof(BITMAPFILEHEADER) +
		pbih->biSize + pbih->biClrUsed
		* sizeof(RGBQUAD) + pbih->biSizeImage);
	hdr.bfReserved1 = 0;
	hdr.bfReserved2 = 0;

	// Tính offset cho mảng các chỉ số màu.
	hdr.bfOffBits = (DWORD) sizeof(BITMAPFILEHEADER) +
		pbih->biSize + pbih->biClrUsed
		* sizeof(RGBQUAD);

	// Copy  BITMAPFILEHEADER vào file .bmp
	if (!WriteFile(hf, (LPVOID)&hdr, sizeof(BITMAPFILEHEADER), (LPDWORD)&dwTmp, NULL))
	{
		errhandler(L"WriteFile", hwnd);
	}

	// Copy  BITMAPINFOHEADER và mảng RGBQUAD vào file .bmp 
	if (!WriteFile(hf, (LPVOID)pbih, sizeof(BITMAPINFOHEADER) + pbih->biClrUsed * sizeof(RGBQUAD), (LPDWORD)&dwTmp, (NULL)))
		errhandler(L"WriteFile", hwnd);

	// copy mảng màu vào file .bmp  
	dwTotal = cb = pbih->biSizeImage;
	hp = lpBits;
	if (!WriteFile(hf, (LPSTR)hp, (int)cb, (LPDWORD)&dwTmp, NULL))
		errhandler(L"WriteFile", hwnd);

	// Đóng file
	if (!CloseHandle(hf))
		errhandler(L"CloseHandle", hwnd);

	// Giải phóng memory
	GlobalFree((HGLOBAL)lpBits);
}

/////////////////////////////////////////////
//BOOL SaveBitmapFile(HWND hwnd, LPCTSTR p_pchFileName)
//{
//	HDC p_hDC = GetDC(hwnd);
//	//HBITMAP hBmp = (HBITMAP)GetCurrentObject(p_hDC, OBJ_BITMAP);
//
//
//	HDC hTargetDC = CreateCompatibleDC(p_hDC);
//	RECT rect = { 0 };
//
//	GetWindowRect(hwnd, &rect);
//
//	HBITMAP hBmp = CreateCompatibleBitmap(p_hDC, rect.right - rect.left,
//		rect.bottom - rect.top);
//	SelectObject(hTargetDC, hBmp);
//	BitBlt(hTargetDC, 0, 0, rect.right, rect.bottom, p_hDC, 0, 0, SRCCOPY);
//
//
//	//Khoi tao doi tuong bitmapinfo
//	BITMAPINFO stBmpInfo;
//	stBmpInfo.bmiHeader.biBitCount = 0;
//	stBmpInfo.bmiHeader.biSize = sizeof(stBmpInfo.bmiHeader);
//	GetDIBits(p_hDC, hBmp, 0, 0, NULL, &stBmpInfo, DIB_RGB_COLORS); //read pixel
//
//	//chuyen dinh dang color sang so bit  
//	ULONG iBmpInfoSize;
//	switch (stBmpInfo.bmiHeader.biBitCount)
//	{
//		//loai 24 color
//	case 24:
//		iBmpInfoSize = sizeof(BITMAPINFOHEADER);
//		break;
//	case 16:
//	case 32:
//		iBmpInfoSize = sizeof(BITMAPINFOHEADER) + sizeof(DWORD) * 3;
//		break;
//	default:
//		iBmpInfoSize = sizeof(BITMAPINFOHEADER) + sizeof(RGBQUAD) * (1 << stBmpInfo.bmiHeader.biBitCount);
//		break;
//	}
//	////
//	PBITMAPINFO pstBmpInfo = NULL;
//	if (iBmpInfoSize != sizeof(BITMAPINFOHEADER))
//	{
//		pstBmpInfo = (PBITMAPINFO)GlobalAlloc(GMEM_FIXED | GMEM_ZEROINIT, iBmpInfoSize);
//		PBYTE pbtBmpInfoDest = (PBYTE)pstBmpInfo;
//		PBYTE pbtBmpInfoSrc = (PBYTE)&stBmpInfo;
//		ULONG iSizeTmp = sizeof(BITMAPINFOHEADER);
//
//		while (iSizeTmp--)
//		{
//			*((pbtBmpInfoDest)++) = *((pbtBmpInfoSrc)++); //vi tri mang a[i] = b[i]
//		}
//	}
//	/// Tao file moi 
//	HANDLE hFile = CreateFile(p_pchFileName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_ARCHIVE, NULL);
//
//
//	//tao header cua file bitmap
//	BITMAPFILEHEADER stBmpFileHder;
//	stBmpFileHder.bfType = 0x4D42; // Dinh dang bimap //'BM' 
//	stBmpFileHder.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + iBmpInfoSize + pstBmpInfo->bmiHeader.biSizeImage;
//	stBmpFileHder.bfReserved1 = 0;
//	stBmpFileHder.bfReserved2 = 0;
//	stBmpFileHder.bfOffBits = sizeof(BITMAPFILEHEADER) + iBmpInfoSize;
//	//ghi header vao file
//	DWORD dRet;
//	WriteFile(hFile, (LPCVOID)&stBmpFileHder, sizeof(BITMAPFILEHEADER), &dRet, NULL);
//	//
//	PBYTE pBits = (PBYTE)GlobalAlloc(GMEM_FIXED | GMEM_ZEROINIT, stBmpInfo.bmiHeader.biSizeImage);
//
//	HBITMAP hTmpBmp = CreateCompatibleBitmap(p_hDC, pstBmpInfo->bmiHeader.biWidth, pstBmpInfo->bmiHeader.biHeight);
//	HBITMAP hBmpOld = (HBITMAP)SelectObject(p_hDC, hTmpBmp);
//
//	//ve theo kich thuoc DC
//	GetDIBits(p_hDC, hBmp, 0, pstBmpInfo->bmiHeader.biHeight, (LPSTR)pBits, pstBmpInfo, DIB_RGB_COLORS);//doc pixel tu hbitmap vao pBits
//
//	WriteFile(hFile, (LPCVOID)pstBmpInfo, iBmpInfoSize, &dRet, NULL);
//	WriteFile(hFile, (LPCVOID)pBits, pstBmpInfo->bmiHeader.biSizeImage, &dRet, NULL);
//	SelectObject(p_hDC, hBmpOld);
//
//
//	//Giai phong bo nho, object...
//	DeleteObject(hTmpBmp);
//	CloseHandle(hFile);
//	GlobalFree(pstBmpInfo);
//	GlobalFree(pBits);
//
//	DeleteObject(hBmp);
//	ReleaseDC(hwnd, p_hDC);
//	DeleteDC(hTargetDC);
//	return TRUE;
//}