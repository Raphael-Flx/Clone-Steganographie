#include "BinaryOperation.h"

int GetLength(const char* txt) {
	int i = 0;
	while (txt[i] != '\0') {
		++i;
	}
	return i;
}

BinaryOperation::BinaryOperation() {
	_magicNumber = 255; // 0b01101001
	_magicNumberByteSize = 2;

	_textSize = 0;
	_textSizeByteSize = 2;
}

BinaryOperation::~BinaryOperation() {

}

void BinaryOperation::EncryptData(Image* pimg, BYTE* data, int dataSize, int offset) {
	int _offset = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + offset;

	// Pour tout le message
	for (int iSrc = 0, iTrg = _offset; iSrc < dataSize; iSrc++)
	{
		// Pour un octet du message
		BYTE c = data[iSrc];
		for (int iBit = 0; iBit < 8; iBit++)
		{
			if (iBit == 2 || iBit == 6)
			{
				// Encodage de 2 bits dans les canaux rouges
				BYTE v = (c >> (6 - iBit)) & 3;
				pimg->ChangeBufByte(iTrg, v, RED);
				iBit++;
			}
			else
			{
				// Encodage de 1 bit dans le LSB
				BYTE v = (c >> (7 - iBit)) & 1;
				pimg->ChangeBufByte(iTrg, v);
			}
			iTrg++;
		}
	}
}

void BinaryOperation::Encrypt(File* pfile, Image* pimg, const char* txt)
{
	const char* text = txt;
	_textSize = GetLength(text);

	BYTE byteTab[sizeof(int)];

	// Magic Number
	memcpy(byteTab, &_magicNumber, sizeof(__int16));
	EncryptData(pimg, byteTab, _magicNumberByteSize, 0);

	// Size of the text
	memcpy(byteTab, &_textSize, sizeof(int));
	EncryptData(pimg, byteTab, _textSizeByteSize, _magicNumberByteSize * 8);

	// Text
	EncryptData(pimg, (BYTE*)text, _textSize, _magicNumberByteSize * 8 + _textSizeByteSize * 8);

	pfile->Write(pimg->GetBuf(), pimg->GetSize());
}

void BinaryOperation::DecryptData(Image* pimg, BYTE* data, int dataSize, int offset)
{
	int _offset = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + offset;

	// Pour tout le message
	for (int iSrc = 0, iTrg = _offset; iSrc < dataSize; iSrc++)
	{
		data[iSrc] = 0; // Initialiser à 0

		// Pour un octet du message
		for (int iBit = 0; iBit < 8; iBit++)
		{
			if (iBit == 2 || iBit == 6)
			{
				// Décodage de 2 bits depuis les canaux rouges
				BYTE bits = (pimg->GetBuf(iTrg) & 0b11);
				data[iSrc] = (data[iSrc] << 2) | bits;
				iBit++;
			}
			else
			{
				// Décodage de 1 bit depuis le LSB
				BYTE bit = (pimg->GetBuf(iTrg) & 0b1);
				data[iSrc] = (data[iSrc] << 1) | bit;
			}
			iTrg++;
		}
	}
}

char* BinaryOperation::Decrypt(Image* pimg)
{
	if (pimg == nullptr)
		return 0;

	int offset = 0;
	BYTE magicNumberByteTab[sizeof(int)] = { 0 };

	// Decrypt the magic number
	int magicNumber = 0;
	DecryptData(pimg, magicNumberByteTab, _magicNumberByteSize, offset);
	memcpy(&magicNumber, magicNumberByteTab, sizeof(__int16));

	if (magicNumber != _magicNumber)
	{
		std::cout << "Magic number incorrect: " << magicNumber << " attendu: " << _magicNumber << std::endl;
		return 0;
	}

	// Decrypt the size of the text
	int textSize = 0;
	offset += _magicNumberByteSize * 8;

	BYTE textSizeByteTab[sizeof(int)] = { 0 };

	DecryptData(pimg, textSizeByteTab, _textSizeByteSize, offset);
	memcpy(&textSize, textSizeByteTab, sizeof(__int16));

	if (textSize <= 0 || textSize > 10000) // Vérification de sécurité
	{
		std::cout << "Taille de texte invalide: " << textSize << std::endl;
		return 0;
	}

	// Decrypt the text
	BYTE* textByte = new BYTE[textSize];

	offset += _textSizeByteSize * 8;
	DecryptData(pimg, textByte, textSize, offset);

	char* text = new char[textSize + 1];
	for (int charac = 0; charac < textSize; charac++) {
		text[charac] = (char)textByte[charac];
	}
	text[textSize] = '\0';

	std::cout << "Message decrypte : " << text << std::endl;

	delete[] textByte;

	return text;
}