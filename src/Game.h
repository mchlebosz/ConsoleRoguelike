#pragma once
#include <windows.h>

#include <iostream>
#include <vector>

#include "Enemy.h"
#include "Map.h"
#include "Player.h"

class Game {
public:
	Game();
	~Game();

	void Run();

	void ProcessInput();

private:
	void AddEnemy(int x, int y);
	void RemoveEnemy(int id);
	Enemy* ModifyEnemy(int id);

	void MovePlayer(int x, int y);
	void HurtPlayer(int damage);
	void HealPlayer(int health);

	std::wstring showStats();
	std::string showInventory();

	void Update();
	void PreRender();
	void Render();

	std::vector<Enemy*> m_enemies;
	Player m_player;

	Map m_map;

	bool m_isRunning;
	DWORD m_lastTicks;
	int m_fps;
	int m_lastId;

	// Windows stuff
	const short SCREEN_WIDTH;
	const short SCREEN_HEIGHT;

	// some windows specific stuff
	CHAR_INFO* visibleBuffer;
	CHAR_INFO* hiddenBuffer;
	COORD bufferSize = { SCREEN_WIDTH, SCREEN_HEIGHT };
	COORD bufferPos  = { 0, 0 };
	SMALL_RECT rect  = { 0, 0, (short int)(SCREEN_WIDTH - 1),
						 (short int)(SCREEN_HEIGHT - 1) };
};
