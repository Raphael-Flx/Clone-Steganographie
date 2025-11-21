#include "Image.h"

Image::Image()
{
	buf = nullptr;
}

Image::~Image()
{
	delete[] buf;
}

int Image::Load(File* pFile)
{
	if (pFile == nullptr)
		return 0;

	_size = pFile->GetSize();
	buf = new BYTE[_size];
	pFile->Read(buf, _size);

	memcpy(&_bitmapFileHeader, buf, sizeof(BITMAPFILEHEADER));
	memcpy(&_bitmapInfoHeader, buf + sizeof(BITMAPFILEHEADER), sizeof(BITMAPINFOHEADER));

	_bitmapInfo.bmiHeader = _bitmapInfoHeader;

	return 1;
}

void Image::Write(File* pfile, int color, int value)
{
	pfile->Write((BYTE*) &_bitmapFileHeader, sizeof(BITMAPFILEHEADER));
	pfile->Write((BYTE*) &_bitmapInfoHeader, sizeof(BITMAPINFOHEADER));

	for (int i = 0 + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER); i < _bitmapFileHeader.bfSize; ++i) {
		if (i % 3 == color) {
			buf[i] = min(buf[i] + value, 255);
		}
	}

	pfile->Write(buf + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER), _size);
}

void Image::Show(HDC hdc) {
	HBITMAP hBitmap = CreateDIBitmap(hdc, &_bitmapInfoHeader, CBM_INIT, buf + 54, &_bitmapInfo, DIB_RGB_COLORS);
	SelectObject(hdc, hBitmap);
	StretchBlt(hdc, 250, 200, _bitmapInfoHeader.biWidth, _bitmapInfoHeader.biHeight, hdc, 0, 0, _bitmapInfoHeader.biWidth, _bitmapInfoHeader.biHeight, MERGECOPY);
}

void Image::ChangeBufByte(int index, int val) {
	buf[index] = (buf[index] & 0xFE) | val;
}

void Image::ChangeBufByte(int index, int val, int color) {
	if (color == RED) {
		buf[index] = (buf[index] & 0xFC) | val;
	}
}

BYTE* Image::GetBuf() {
	return buf;
}

int Image::GetBuf(int index) {
	return buf[index];
}

int Image::GetSize() {
	return _size;
}