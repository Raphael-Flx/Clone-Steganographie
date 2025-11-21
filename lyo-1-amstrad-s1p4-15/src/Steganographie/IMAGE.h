#pragma once
#include <Windows.h>
#include "File.h"

#define BLUE 0
#define GREEN 1
#define RED 2

class Image
{
public:
	Image();

	int Load(File* stream);
	void Write(File* pfile, int color, int value);
	void Show(HDC hdc);

	void ChangeBufByte(int index, int val);
	void ChangeBufByte(int index, int val, int color);

	BYTE* GetBuf();
	int GetBuf(int index);
	int GetSize();

	~Image();

private:
	BYTE* buf = nullptr;

	BITMAPFILEHEADER _bitmapFileHeader = {};
	BITMAPINFOHEADER _bitmapInfoHeader = {};
	BITMAPINFO _bitmapInfo = {};

	int _size = 0;
};

