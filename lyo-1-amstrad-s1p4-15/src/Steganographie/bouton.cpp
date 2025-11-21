#include "Bouton.h"

// Création des champs de texte
void Bouton::CreateText(HWND hWnd)
{
    CreateWindow(L"EDIT", L"Veuillez ecrire le chemin de l'image.",
        WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
        400, 150, 900, 25, hWnd, (HMENU)IDC_EDIT_PATH, NULL, NULL);

    CreateWindow(L"EDIT", L"Veuillez ecrire le texte a cacher.",
        WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
        400, 190, 900, 25, hWnd, (HMENU)IDC_EDIT_MESSAGE, NULL, NULL);

    CreateWindow(L"EDIT", L"",
        WS_CHILD | WS_VISIBLE | WS_BORDER |
        ES_MULTILINE | ES_READONLY,
        400, 300, 900, 100, hWnd, (HMENU)IDC_EDIT_OUTPUT, NULL, NULL);
}

// Création des boutons
void Bouton::CreateBouton(HWND hWnd)
{
    CreateWindow(L"BUTTON", L"Cacher le message",
        WS_CHILD | WS_VISIBLE,
        600, 260, 150, 30, hWnd, (HMENU)IDC_BUTTON_HIDE, NULL, NULL);

    CreateWindow(L"BUTTON", L"Extraire le message",
        WS_CHILD | WS_VISIBLE,
        800, 260, 150, 30, hWnd, (HMENU)IDC_BUTTON_EXTRACT, NULL, NULL);
}