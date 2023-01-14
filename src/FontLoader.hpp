#include <Windows.h>

#include <fstream>
#include <vector>

void loadFont(HANDLE *outputFont, HDC *hdc) {
	// Add requred fonts
	std::ifstream fontFile(".\\CascadiaMono.ttf", std::ios::binary);
	if (!fontFile.is_open()) {
		// handle error
		return;
	}

	// Get the size of the file
	fontFile.seekg(0, std::ios::end);
	std::streamsize size = fontFile.tellg();
	fontFile.seekg(0, std::ios::beg);

	// Allocate memory to hold the file data
	std::vector<char> font(size);

	// Read the data into the font
	if (!fontFile.read(font.data(), size)) {
		// handle error
	}

	// Close the file
	fontFile.close();

	// Now you can use the font variable to pass it to the
	// AddFontMemResourceEx function
	DWORD numFonts;
	*outputFont = AddFontMemResourceEx(font.data(), font.size(), 0, &numFonts);

	*hdc = GetDC(GetConsoleWindow());

	HFONT hfont = CreateFont(20, 0, 0, 0, FW_NORMAL, 0, 0, 0, DEFAULT_CHARSET,
							 OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
							 DEFAULT_QUALITY, FF_DONTCARE, "Cascadia Mono PL");
	SelectObject(*hdc, hfont);

	return;
}