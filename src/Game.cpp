#include "Game.h"

#include <stdlib.h>

#include <chrono>
#include <codecvt>
#include <ctime>
#include <iostream>
#include <locale>
#include <thread>

#include "AllLevels.hpp"
#include "Utils.hpp"

Game::Game() :
	m_player(0),
	m_map(100, 30),
	m_isRunning(true),
	m_lastTicks(GetTickCount()),
	m_fps(60),
	m_lastId(0),
	SCREEN_WIDTH(110),
	SCREEN_HEIGHT(50),
	visibleBuffer(new CHAR_INFO[SCREEN_WIDTH * SCREEN_HEIGHT]),
	hiddenBuffer(new CHAR_INFO[SCREEN_WIDTH * SCREEN_HEIGHT]) {
	allLevels = initLevels();

	m_player.setX(allLevels[0].getStartingPosition().first);
	m_player.setY(allLevels[0].getStartingPosition().second);
	m_player.setAppearance(U'😀');
	m_player.setHealth(3);
	m_player.setMaxHealth(5);
	m_player.setExperience(1);
	m_player.setSpeed(2);
	m_map.loadMap(allLevels[0].getMap());
}

Game::~Game() {
	// clean up
	delete[] visibleBuffer;
	delete[] hiddenBuffer;
}

void Game::Run() {
	// Load first map from Levels folder
	m_map.loadMap(allLevels[0].getMap());
	m_player.setX(allLevels[0].getStartingPosition().first);
	m_player.setY(allLevels[0].getStartingPosition().second);
	m_map.addCreature(0, &m_player);

	ModifyEnemy(AddEnemy(20, 8)).setAppearance(U'👹');

	ModifyEnemy(AddEnemy(25, 8)).setAppearance(U'👺');

	while (m_isRunning) {
		DWORD currentTime = GetTickCount();
		DWORD elapsedTime = currentTime - m_lastTicks;
		Update();
		PreRender();
		Render();

		if (elapsedTime < 1000 / m_fps) {
			std::this_thread::sleep_for(
				std::chrono::milliseconds(1000 / m_fps - elapsedTime));
		}
		m_lastTicks = GetTickCount();
	}

	// clean console
	system("cls");
	// say goodbye
	std::wcout << L"Thanks for playing!😉" << std::endl;
	Sleep(1000);
	// clear console
	system("cls");
}

int Game::AddEnemy(int x, int y) {
	Enemy* enemy = new Enemy(++m_lastId);
	enemy->setX(x);
	enemy->setY(y);
	enemy->setAppearance(U'X');

	m_map.addCreature(m_lastId, enemy);
	m_enemies.push_back(enemy);

	return m_lastId;
}

int Game::FindEnemy(int id) {
	for (size_t i = 0; i < m_enemies.size(); i++) {
		if (m_enemies[i]->getId() == id) {
			return i;
		}
	}
	return -1;
}

void Game::RemoveEnemy(int id) {
	const int index = FindEnemy(id);
	delete m_enemies[index];

	m_map.removeCreature(index);
	m_enemies.erase(m_enemies.begin() + index);
}

Enemy& Game::ModifyEnemy(int id) {
	const int index = FindEnemy(id);
	return *m_enemies[index];
}

void Game::MovePlayer(int x, int y) {
	m_player.setX(x);
	m_player.setY(y);
}

void Game::HurtPlayer(int damage) {
	int newHealth = m_player.getHealth() - damage;
	if (newHealth < 0) {
		newHealth = 0;
	}
	m_player.setHealth(newHealth);
}
void Game::HealPlayer(int health) {
	int newHealth = m_player.getHealth() + health;
	if (newHealth > m_player.getMaxHealth()) {
		newHealth = m_player.getMaxHealth();
	}
	m_player.setHealth(newHealth);
}

std::wstring Game::showStats() {
	std::wstring output = L"";

	int health                    = m_player.getHealth();
	std::wstring fullHeartString  = char32to16(U'💗');
	std::wstring halfHeartString  = char32to16(U'💔');
	std::wstring emptyHeartString = char32to16(U'🤍');
	// create hearts for health
	std::wstring healthHearts = L"HP: ";
	// for each 2 health, add a full heart, otherwise add a half heart
	for (int i = 0; i < health / 2; i++) {
		for (int j = 0; j < 2; j++) {
			healthHearts += fullHeartString[j];
		}
	}
	if (health % 2 == 1) {
		for (int j = 0; j < 2; j++) {
			healthHearts += halfHeartString[j];
		}
	}
	// add empty hearts
	for (int i = 0; i < m_player.getMaxHealth() / 2 - health / 2; i++) {
		for (int j = 0; j < 2; j++) {
			healthHearts += emptyHeartString[j];
		}
	}

	std::wstring attack =
		L"Attack: " + std::to_wstring(m_player.getAttackPower());
	std::wstring level     = L"Level: " + std::to_wstring(m_player.getLevel());
	std::wstring emptyExp  = char32to16(U'⬜');
	std::wstring fullExp   = char32to16(U'⬛');
	std::wstring expString = L"XP: ";

	int exp          = m_player.getExperience();
	int nextLevelExp = m_player.getNextLevelExp();
	// always show 20 exp bars proportionally to the exp
	short int expBars = 20;
	for (int i = 0; i < expBars; i++) {
		if (i < exp * expBars / nextLevelExp) {
			for (UINT j = 0; j < fullExp.length(); j++) {
				expString += fullExp[j];
			}
		} else {
			for (UINT j = 0; j < emptyExp.length(); j++) {
				expString += emptyExp[j];
			}
		}
	}

	output += attack + L'\t' + healthHearts + L'\n' + level + L'\t' +
			  expString + L'\n';
	return output;
}

std::string Game::showInventory() {
	std::vector<Item> inventory = m_player.getInventory();

	std::string output = "Inventory:";
	for (UINT i = 0; i < inventory.size(); i++) {
		output += '\t' + std::to_string(i + 1) + ". " + inventory[i].getName();
	}
	output += '\n';

	return output;
}

bool Game::isOnTile(Creature& creature, char32_t tile) {
	return m_map.getTileAppearance(creature.getX(), creature.getY()) == tile ||
		   m_map.getTileAppearance(creature.getX() + 1, creature.getY()) ==
			   tile;
}

bool Game::isOnEnemy(Creature& creature) {
	int id = creature.getId();
	for (size_t i = 0; i < m_enemies.size(); i++) {
		if ((m_enemies[i]->getX() == creature.getX() ||
			 m_enemies[i]->getX() == creature.getX() + 1 ||
			 m_enemies[i]->getX() == creature.getX() - 1) &&
			m_enemies[i]->getY() == creature.getY() &&
			m_enemies[i]->getId() != id) {
			return true;
		}
	}
	return false;
}
// Not using SDL

void Game::Update() {
	char32_t forbiddenTile = U'█';
	int prevX              = m_player.getX();
	int prevY              = m_player.getY();

	// allow player to move only m_moveTimer ticks speed times

	// get input
	if (GetAsyncKeyState(VK_UP) || GetAsyncKeyState(0x57)) {
		// check if player can move up
		if (m_player.getY() > 0) {
			m_player.moveUp();
		}
	} else if (GetAsyncKeyState(VK_DOWN) || GetAsyncKeyState(0x53)) {
		if (m_player.getY() < m_map.getHeight() - 1) {
			m_player.moveDown();
		}
	} else if (GetAsyncKeyState(VK_LEFT) || GetAsyncKeyState(0x41)) {
		if (m_player.getX() > 1) {
			m_player.moveLeft();
		}
	} else if (GetAsyncKeyState(VK_RIGHT) || GetAsyncKeyState(0x44)) {
		if (m_player.getX() < m_map.getWidth() - 3) {
			m_player.moveRight();
		}
	}

	if (m_player.getMoveTimer() <= m_player.getSpeed()) {
		m_player.setMoveTimer(m_player.getMoveTimer() + 1);
	}

	if (isOnTile(m_player, forbiddenTile) || isOnEnemy(m_player)) {
		// if so, move player back to previous position
		m_player.setX(prevX);
		m_player.setY(prevY);
	}

	// exit game on escape
	if (GetAsyncKeyState(VK_ESCAPE)) {
		m_isRunning = false;
	}
}

void Game::PreRender() {
	// clear hidden buffer
	for (int i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT; i++) {
		hiddenBuffer[i].Char.UnicodeChar = ' ';
		hiddenBuffer[i].Attributes       = FOREGROUND_GREEN | FOREGROUND_BLUE;
	}
	// get stats, map, inventory
	std::wstring stats    = showStats();
	std::u32string map    = m_map.getMapString();
	std::string inventory = showInventory();

	// add stats to hidden buffer
	int x = 0;
	int y = 0;
	for (UINT i = 0; i < stats.length(); i++) {
		if (stats[i] == '\t') {
			for (UINT j = 0; j < 4; j++) {
				hiddenBuffer[x + SCREEN_WIDTH * y].Char.UnicodeChar = ' ';
				hiddenBuffer[x + SCREEN_WIDTH * y].Attributes =
					FG_COLORS::FG_GREEN;
				x += 1;
			}
		} else if (stats[i] == '\n') {
			x = 0;
			y += 1;
		} else {
			hiddenBuffer[x + SCREEN_WIDTH * y].Char.UnicodeChar = stats[i];
			hiddenBuffer[x + SCREEN_WIDTH * y].Attributes = FG_COLORS::FG_GREEN;
			x += 1;
		}
	}

	x = 0;
	y = 2;
	// add map to hidden buffer
	for (UINT i = 0; i < map.length(); i++) {
		if (map[i] == '\n') {
			x = 0;
			y += 1;
		} else {
			// if map[i] bigger than wchar size, split into two wchars
			bool isSurrogatePair;
			std::wstring wstr = char32to16(map[i], &isSurrogatePair);

			if (isSurrogatePair) {
				i += 1;
			}

			// add bytes to hidden buffer
			for (UINT j = 0; j < wstr.length(); j++) {
				hiddenBuffer[x + SCREEN_WIDTH * y].Char.UnicodeChar = wstr[j];
				hiddenBuffer[x + SCREEN_WIDTH * y].Attributes =
					FG_COLORS::FG_WHITE;
				x += 1;
			}
		}
	}

	x = 0;
	y = m_map.getHeight() + 6;
	// add inventory to hidden buffer
	for (UINT i = 0; i < inventory.length(); i++) {
		if (inventory[i] == '\t') {
			for (int j = 0; j < 4; j++) {
				hiddenBuffer[x + SCREEN_WIDTH * y].Char.UnicodeChar = ' ';
				hiddenBuffer[x + SCREEN_WIDTH * y].Attributes =
					FG_COLORS::FG_GREEN;
				x += 1;
			}
		} else if (inventory[i] == '\n') {
			x = 0;
			y += 1;
		} else {
			hiddenBuffer[x + SCREEN_WIDTH * y].Char.UnicodeChar = inventory[i];
			hiddenBuffer[x + SCREEN_WIDTH * y].Attributes = FG_COLORS::FG_BROWN;
			x += 1;
		}
	}
}

void Game::Render() {
	// copy hidden buffer to visible buffer
	for (int i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT; i++) {
		visibleBuffer[i] = hiddenBuffer[i];
	}

	// draw visible buffer
	WriteConsoleOutputW(GetStdHandle(STD_OUTPUT_HANDLE), visibleBuffer,
						bufferSize, bufferPos, &rect);
}