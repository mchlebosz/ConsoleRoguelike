#include <Windows.h>

// #include "FontLoader.hpp"
#include "Game.h"

/**
 * `SetConsoleOutputCP(CP_UTF8)` sets the console output code page to UTF-8
 *
 * @param hInstance A handle to the current instance of the application.
 * @param hPrevInstance This parameter is always NULL.
 * @param lpCmdLine The command line arguments.
 * @param nCmdShow Specifies how the window is to be shown.
 *
 * @return The error code of the last error that occurred.
 */
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
