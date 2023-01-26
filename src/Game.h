#pragma once
#include <windows.h>

#include <iostream>
#include <memory>
#include <vector>

#include "Enemy.h"
#include "Item.h"
#include "Level.h"
#include "Map.h"
#include "Player.h"

class Game {
public:
	Game();
	~Game();

	void Run();

	void ProcessInput();

private:
	int AddEnemy(int x, int y);
	void RemoveEnemy(int id);
	int FindEnemy(int id);
	int FindEnemy(int x, int y);
	Enemy& ModifyEnemy(int id);

	// player methods
	void MovePlayer(int x, int y);
	void HurtPlayer(int damage);
	void HealPlayer(int health);

	bool isOnTile(Creature& creature, char32_t tile);
	bool isOnEnemy(Creature& creature);

	std::wstring showStats();
	std::string showInventory();

	void DropRandomItem(int x, int y);

	void Update();
	void PreRender();
	void Render();
	void LoadLevel(UINT level);

	std::vector<Enemy*> m_enemies;
	Player m_player;

	Map m_map;

	bool m_isRunning;
	DWORD m_lastTicks;
	DWORD m_fps;
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

	std::vector<Level> allLevels;
	UINT m_currentLevel;
};
