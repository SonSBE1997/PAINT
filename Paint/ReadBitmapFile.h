#pragma once
#include <Windows.h>
#pragma warning(disable:4996)

BOOL LoadBitmapFromBMPFile(LPCWSTR szFileName, HBITMAP *phBitmap, HPALETTE *phPalette)
{
	BITMAP  bm;
	*phBitmap = NULL;
	*phPalette = NULL;

	// Tải bitmap image vào DIBSection
	*phBitmap = (HBITMAP)LoadImage(NULL, szFileName, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE);
	if (*phBitmap == NULL)
		return FALSE;

	// Lấy độ sâu màu của  DIBSection
	GetObject(*phBitmap, sizeof(BITMAP), &bm);

	// nếu DIBSection có ít hơn hoặc bằng 256 màu, nó có 1 bảng màu 
	if ((bm.bmBitsPixel * bm.bmPlanes) <= 8)
	{
		HDC           hMemDC;
		HBITMAP       hOldBitmap;
		RGBQUAD       rgb[256];
		LPLOGPALETTE  pLogPal;
		WORD          i;

		// Tạo memory device context và truyền DIBSection vào MDC
		hMemDC = CreateCompatibleDC(NULL);
		hOldBitmap = (HBITMAP)SelectObject(hMemDC, *phBitmap);
		// Lấy bảng màu của DIBSection
		GetDIBColorTable(hMemDC, 0, 256, rgb);
		// Lấy bảng màu từ bảng màu của DIBSection, cấp phát bộ nhớ... 
		pLogPal = (LOGPALETTE *)malloc(sizeof(LOGPALETTE) + (256 * sizeof(PALETTEENTRY)));
		pLogPal->palVersion = 0x300;
		pLogPal->palNumEntries = 256;
		for (i = 0; i < 256; i++)
		{
			pLogPal->palPalEntry[i].peRed = rgb[i].rgbRed;
			pLogPal->palPalEntry[i].peGreen = rgb[i].rgbGreen;
			pLogPal->palPalEntry[i].peBlue = rgb[i].rgbBlue;
			pLogPal->palPalEntry[i].peFlags = 0;
		}
		*phPalette = CreatePalette(pLogPal);
		// Giải phóng bộ nhớ và đối tượng
		free(pLogPal);
		SelectObject(hMemDC, hOldBitmap);
		DeleteDC(hMemDC);
	}
	else   // Nó không có bảng màu, vì vậy hãy sử dụng bảng màu halftone (các dấu chấm liên tiếp)
	{
		HDC hRefDC;
		hRefDC = GetDC(NULL);
		*phPalette = CreateHalftonePalette(hRefDC);
		ReleaseDC(NULL, hRefDC);
	}
	return TRUE;

}