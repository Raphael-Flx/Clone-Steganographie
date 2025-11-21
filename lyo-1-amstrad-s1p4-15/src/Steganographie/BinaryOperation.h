#pragma once
#include "Image.h"

class BinaryOperation
{
public:
	BinaryOperation();
	~BinaryOperation();

	void Encrypt(File* pfile, Image* pimg, const char* txt);
	char* Decrypt(Image* pimg);

private:
	void EncryptData(Image* pimg, BYTE* data, int dataSize, int start);
	void DecryptData(Image* pimg, BYTE* data, int dataSize, int offset);

private:
	unsigned __int16 _magicNumber;
	int _magicNumberByteSize;
	int _textSize;
	int _textSizeByteSize;
};

