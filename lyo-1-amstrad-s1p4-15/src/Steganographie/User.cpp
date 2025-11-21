#include "User.h"

void User::Chose(HWND hWnd, LPARAM wParam)
{
	Image* img = nullptr; // Initialisation de l'image
	BinaryOperation binaryOperation;

	int wmId = LOWORD(wParam);

	switch (wmId)
	{
	case IDC_BUTTON_HIDE:
	{
		char path[MAX_PATH];
		char messageTxt[1000];

		// Récupération du chemin
		int len = GetDlgItemTextA(hWnd, IDC_EDIT_PATH, path, MAX_PATH);

		if (len == 0 || path[0] == '\0')
		{
			SetDlgItemText(hWnd, IDC_EDIT_OUTPUT, L"Veuillez entrer le chemin de l'image correctement");
			break;
		}

		// Récupération du message
		int msgLen = GetDlgItemTextA(hWnd, IDC_EDIT_MESSAGE, messageTxt, 1000);

		if (msgLen == 0 || messageTxt[0] == '\0')
		{
			SetDlgItemText(hWnd, IDC_EDIT_OUTPUT, L"Veuillez entrer le texte que vous voulez cacher");
			break;
		}

		// Libérer l'ancienne image si elle existe
		if (img != nullptr) {
			delete img;
		}
		img = new Image();

		// Ouverture du fichier
		File file;
		if (!file.Open(path))
		{
			SetDlgItemText(hWnd, IDC_EDIT_OUTPUT, L"Erreur : impossible d'ouvrir le fichier à ce chemin");
			delete img;
			img = nullptr;
			break;
		}
		
		//Chargement de l'image
		std::cout << "Chargement reussi\n";
		if (!img->Load(&file))
		{
			SetDlgItemText(hWnd, IDC_EDIT_OUTPUT, L"Erreur lors du chargement de l'image");
			file.Close();
			delete img;
			img = nullptr;
			break;
		}

		file.Close();

		// Copie du fichier et changement des pixels
		File outputFile;
		if (!outputFile.Create("NewImage.bmp"))
		{
			SetDlgItemText(hWnd, IDC_EDIT_OUTPUT, L"Erreur lors de la création du fichier de sortie");
			delete img;
			img = nullptr;
			break;
		}

		// Encryptage du message puis fermeture du fichier
		binaryOperation.Encrypt(&outputFile, img, messageTxt);
		outputFile.Close();

		std::wstring output = L"Le message a été caché correctement dans NewImage.bmp\r\n";
		SetDlgItemText(hWnd, IDC_EDIT_OUTPUT, output.c_str());

		SetDlgItemText(hWnd, IDC_EDIT_PATH, L"");
		SetDlgItemText(hWnd, IDC_EDIT_MESSAGE, L"");
		break;
	}
	case IDC_BUTTON_EXTRACT:
	{
		char path[MAX_PATH];
		int len = GetDlgItemTextA(hWnd, IDC_EDIT_PATH, path, MAX_PATH);

		if (len == 0 || path[0] == '\0')
		{
			SetDlgItemText(hWnd, IDC_EDIT_OUTPUT, L"Veuillez entrer le chemin de l'image à décrypter");
			break;
		}

		// Libérer l'ancienne image si elle existe
		if (img != nullptr) {
			delete img;
		}
		img = new Image();

		// Charger l'image à décrypter
		File file;
		if (!file.Open(path))
		{
			SetDlgItemText(hWnd, IDC_EDIT_OUTPUT, L"Erreur : impossible d'ouvrir le fichier");
			delete img;
			img = nullptr;
			break;
		}

		if (!img->Load(&file))
		{
			SetDlgItemText(hWnd, IDC_EDIT_OUTPUT, L"Erreur lors du chargement de l'image");
			file.Close();
			delete img;
			img = nullptr;
			break;
		}

		file.Close();

		// Décrypter le message
		char* text = binaryOperation.Decrypt(img);

		std::wstring output;
		if (text == 0) {
			output = L"Aucun message caché trouvé dans cette image.";
		}
		else {
			// Convertir le texte en wstring pour l'affichage
			int textLen = strlen(text);
			std::wstring wtext(textLen, L' ');
			MultiByteToWideChar(CP_ACP, 0, text, textLen, &wtext[0], textLen);

			output = L"Le message caché est :\r\n" + wtext;
		}

		delete img;

		SetDlgItemText(hWnd, IDC_EDIT_OUTPUT, output.c_str());
		break;
	}
	}
}