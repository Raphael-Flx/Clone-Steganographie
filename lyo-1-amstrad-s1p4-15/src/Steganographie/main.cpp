#include <iostream>
#include <string>
#include <windows.h>
#include "Bouton.h"
#include "main.h"
#include "User.h"
#include "Image.h"
#include "File.h"
#include "BinaryOperation.h"
#include "framework.h"
#include "WindowsProject1.h"


#define MAX_LOADSTRING 100


File file;
Image* img = nullptr;
Bouton btn;
User u;

// Variables globales
HINSTANCE hInst;
WCHAR szTitle[MAX_LOADSTRING];
WCHAR szWindowClass[MAX_LOADSTRING];

// Déclarations
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);


// --------------------------------------------------------
//                   wWinMain (POINT D’ENTRÉE)
// --------------------------------------------------------
int APIENTRY wWinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPWSTR lpCmdLine,
	int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// Chargement des chaînes depuis les ressources
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_WINDOWSPROJECT1, szWindowClass, MAX_LOADSTRING);

	// Sécuriser si les ressources n'existent pas
	if (wcslen(szTitle) == 0)
		wcscpy_s(szTitle, L"Fenetre Steganographie");

	if (wcslen(szWindowClass) == 0)
		wcscpy_s(szWindowClass, L"MyWinClass");

	// IMPORTANT : enregistrement de la classe
	if (!MyRegisterClass(hInstance))
	{
		MessageBox(NULL, L"Erreur : impossible d’enregistrer la classe de fenêtre.",
			L"Erreur", MB_OK | MB_ICONERROR);
		return FALSE;
	}

	// Création de la fenêtre
	if (!InitInstance(hInstance, nCmdShow))
	{
		MessageBox(NULL, L"Erreur : impossible de créer la fenêtre.",
			L"Erreur", MB_OK | MB_ICONERROR);
		return FALSE;
	}

	// Boucle messages
	MSG msg;
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int)msg.wParam;
}



// --------------------------------------------------------
//                Enregistrement de la classe
// --------------------------------------------------------
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex = { 0 };
	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.hInstance = hInstance;

	// Sécurisé si les icônes de ressources n’existent pas
	HICON hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINDOWSPROJECT1));
	if (!hIcon) hIcon = LoadIcon(NULL, IDI_APPLICATION);

	HICON hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SMALL));
	if (!hIconSm) hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	wcex.hIcon = hIcon;
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = CreateSolidBrush(RGB(170, 200, 220)); //(HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = hIconSm;

	return RegisterClassExW(&wcex);
}



// --------------------------------------------------------
//                 Création de la fenêtre
// --------------------------------------------------------
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance;

	HWND hWnd = CreateWindowW(
		szWindowClass,
		szTitle,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		500,
		350,
		nullptr,
		nullptr,
		hInstance,
		nullptr
	);

	if (!hWnd)
	{
		wchar_t buffer[256];
		wsprintf(buffer, L"CreateWindowW a échoué.\nErreur = %lu", GetLastError());
		MessageBox(NULL, buffer, L"Erreur", MB_ICONERROR);
		return FALSE;
	}

	ShowWindow(hWnd, SW_MAXIMIZE);
	UpdateWindow(hWnd);
	return TRUE;
}


// --------------------------------------------------------
//           WNDPROC : Gestion des événements Windows
// --------------------------------------------------------
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CREATE:
	{
		btn.CreateBouton(hWnd);
		btn.CreateText(hWnd);
		break;
	}
	case WM_COMMAND:
	{
		u.Chose(hWnd, wParam);
	}
	case IDM_ABOUT:
	{
		DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
		break;
	}
	case IDM_EXIT:
	{
		DestroyWindow(hWnd);
		break;
	}
	/*case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);

		if (img == nullptr) 
		{
			break;
		}

		img->Show(hdc);
		break;
	}*/
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		break;
	}
	default:
	{
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	}
	return 0;
}

// --------------------------------------------------------
//                 Boîte de dialogue "About"
// --------------------------------------------------------
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
		return TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
		}
		break;
	}
	return FALSE;
}
