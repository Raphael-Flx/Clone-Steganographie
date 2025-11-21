#pragma once
#include "Bouton.h"
#include "File.h"
#include "Image.h"
#include "BinaryOperation.h"
#include<filesystem>

class User
{
public:
	void Chose(HWND hWnd, LPARAM wParam);

private:
	BYTE* buf = nullptr;
};

