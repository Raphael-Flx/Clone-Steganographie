#pragma once
#include <windows.h>

class Bouton
{
public:
	void CreateBouton(HWND hWnd);
	void CreateText(HWND hWnd);

	// Identifiants des contrôles
#define IDC_EDIT_PATH      201
#define IDC_EDIT_MESSAGE   202
#define IDC_BUTTON_HIDE    203
#define IDC_BUTTON_EXTRACT 204
#define IDC_EDIT_OUTPUT    205
};

