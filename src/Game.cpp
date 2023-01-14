#include "Game.h"

#include <stdlib.h>

#include <chrono>
#include <codecvt>
#include <ctime>
#include <iostream>
#include <locale>
#include <thread>

Game::Game() :
	m_map(50, 30),
	m_lastId(0),
	m_player(0),
	m_isRunning(true),
	m_lastTicks(GetTickCount()),
	m_fps(30),
	SCREEN_WIDTH(80),
	SCREEN_HEIGHT(50),
	visibleBuffer(new CHAR_INFO[SCREEN_WIDTH * SCREEN_HEIGHT]),
	hiddenBuffer(new CHAR_INFO[SCREEN_WIDTH * SCREEN_HEIGHT]) {
	m_player.setX(1);
	m_player.setY(1);
	m_player.setAppearance(U'🧧');
	m_map.addCreature(0, &m_player);
}

Game::~Game() {}

void Game::Run() {
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
}

void Game::AddEnemy(int x, int y) {
	int id       = ++m_lastId;
	Enemy* enemy = new Enemy(id);
	enemy->setX(x);
	enemy->setY(y);
	enemy->setAppearance(U'X');

	m_map.addCreature(id, enemy);
	m_enemies.push_back(enemy);
}

void Game::RemoveEnemy(int id) {
	delete m_enemies[id];

	m_map.removeCreature(id);
	m_enemies.erase(m_enemies.begin() + id);
}

Enemy* Game::ModifyEnemy(int id) {
	return m_enemies[id];
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
	std::wstring health = L"Health: " + std::to_wstring(m_player.getHealth());
	std::wstring attack =
		L"Attack: " + std::to_wstring(m_player.getAttackPower());
	std::wstring level = L"Level: " + std::to_wstring(m_player.getLevel());
	std::wstring exp =
		L"Experience: " + std::to_wstring(m_player.getExperience());

	output += health + L'\t' + attack + L'\t' + level + L'\t' + exp + L'\n';
	return output;
}

std::string Game::showInventory() {
	std::vector<Item> inventory = m_player.getInventory();

	std::string output = "Inventory:";
	for (int i = 0; i < inventory.size(); i++) {
		output += '\t' + std::to_string(i + 1) + ". " + inventory[i].getName();
	}
	output += '\n';

	return output;
}

// Not using SDL

void Game::Update() {
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
		if (m_player.getX() > 0) {
			m_player.moveLeft();
		}
	} else if (GetAsyncKeyState(VK_RIGHT) || GetAsyncKeyState(0x44)) {
		if (m_player.getX() < m_map.getWidth() - 2) {
			m_player.moveRight();
		}
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

	// add stats, map, inventory to hidden buffer
	int x = 0;
	int y = 0;
	for (int i = 0; i < stats.length(); i++) {
		if (stats[i] == '\t') {
			for (int j = 0; j < 4; j++) {
				hiddenBuffer[x + SCREEN_WIDTH * y].Char.UnicodeChar = ' ';
				hiddenBuffer[x + SCREEN_WIDTH * y].Attributes =
					FOREGROUND_GREEN | FOREGROUND_BLUE;
				x += 1;
			}
		} else if (stats[i] == '\n') {
			x = 0;
			y += 1;
		} else {
			hiddenBuffer[x + SCREEN_WIDTH * y].Char.UnicodeChar = stats[i];
			hiddenBuffer[x + SCREEN_WIDTH * y].Attributes =
				FOREGROUND_GREEN | FOREGROUND_BLUE;
			x += 1;
		}
	}

	x = 0;
	y = 2;
	// add map to hidden buffer
	for (int i = 0; i < map.length(); i++) {
		if (map[i] == '\n') {
			x = 0;
			y += 1;
		} else {
			char32_t c = map[i];
			// convert char32_t to two wchars that support utf16 surrogate pairs
			wchar_t wchars[2];
			int numWchars = 0;
			if (c <= 0xFFFF) {
				wchars[0] = c;
				numWchars = 1;
			} else {
				wchars[0] = 0xD800 + ((c - 0x10000) >> 10);
				wchars[1] = 0xDC00 + ((c - 0x10000) & 0x3FF);
				numWchars = 2;
				// skip next char32_t
				i += 1;
			}
			// convert wchars to utf16 wstring
			std::wstring wstr = L"";
			for (int j = 0; j < numWchars; j++) {
				wstr += wchars[j];
			}

			// add bytes to hidden buffer
			for (int j = 0; j < wstr.length(); j++) {
				hiddenBuffer[x + SCREEN_WIDTH * y].Char.UnicodeChar = wstr[j];
				hiddenBuffer[x + SCREEN_WIDTH * y].Attributes =
					FOREGROUND_GREEN | FOREGROUND_BLUE;
				x += 1;
			}
		}
	}

	x = 0;
	y = m_map.getHeight() + 5;
	// add inventory to hidden buffer
	for (int i = 0; i < inventory.length(); i++) {
		if (inventory[i] == '\t') {
			for (int j = 0; j < 4; j++) {
				hiddenBuffer[x + SCREEN_WIDTH * y].Char.UnicodeChar = ' ';
				hiddenBuffer[x + SCREEN_WIDTH * y].Attributes =
					FOREGROUND_RED | FOREGROUND_GREEN;
				x += 1;
			}
		} else if (inventory[i] == '\n') {
			x = 0;
			y += 1;
		} else {
			hiddenBuffer[x + SCREEN_WIDTH * y].Char.UnicodeChar = inventory[i];
			hiddenBuffer[x + SCREEN_WIDTH * y].Attributes =
				FOREGROUND_RED | FOREGROUND_GREEN;
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