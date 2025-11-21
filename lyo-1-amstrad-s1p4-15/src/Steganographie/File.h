#pragma once
#include<iostream>
#include "Windows.h"

class File
{
private:
	FILE* stream = nullptr;

public:
	File() {}
	bool Open(const char* path);
	bool Create(const char* path);
	size_t Read(BYTE* buf, int size);
	size_t Write(BYTE* buf, int size);
	int GetSize();
	bool Close();
};
