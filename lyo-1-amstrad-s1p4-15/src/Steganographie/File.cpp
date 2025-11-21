#include "File.h"

bool File::Create(const char* path)
{
	if (path == nullptr || *path == 0)
		return false;

	// Ouvrir/créer le fichier de destination
	errno_t err = fopen_s(&stream, path, "wb");
	if (err != 0 || stream == nullptr)
	{
		std::cout << "Erreur d'ouverture du fichier destination\n";
		return false;
	}

	return true;
}

bool File::Close()
{
	if (stream == 0) {
		return false;
	}

	if (fclose(stream) != 0)
		return false;

	return true;
}

bool File::Open(const char* path)
{
	if (path == nullptr || *path == 0)
		return false;

	if (fopen_s(&stream, path, "rb") != 0)
		return false;

	return true;
}

size_t File::Read(BYTE* buf, int size)
{
	if (stream == nullptr)
		return 0;
	return fread_s(buf, size, 1, size, stream);
}

size_t File::Write(BYTE* buf, int size)
{
	if (stream == nullptr)
		return 0;
   size_t bytesWritten = fwrite(buf, 1, size, stream);
   return bytesWritten;
}

int File::GetSize()
{
	int cur = ftell(stream);
	fseek(stream, 0, SEEK_END);
	int size = ftell(stream);
	fseek(stream, cur, SEEK_SET);
	return size;
}