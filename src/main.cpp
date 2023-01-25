#include <Windows.h>

// #include "FontLoader.hpp"
#include "Game.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
				   LPSTR lpCmdLine, int nCmdShow) {
	// HANDLE font;
	// HDC hdc;
	// loadFont(&font, &hdc);

	// GetConsoleOutputCP(void);
	std::cout << GetConsoleOutputCP() << std::endl;

	if (SetConsoleOutputCP(CP_UTF8)) {
		Game game;
		//  cls
		system("cls");
		game.Run();

	} else {
		std::cout << "Error: " << GetLastError() << std::endl;
	}
	// Remove fonts
	// RemoveFontMemResourceEx(font);
	// ReleaseDC(GetConsoleWindow(), hdc);

	// cls
	system("cls");

	return 0;
}
