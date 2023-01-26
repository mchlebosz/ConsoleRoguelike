#include "Game.h"

#include <stdlib.h>

#include <chrono>
#include <codecvt>
#include <ctime>
#include <future>
#include <iostream>
#include <locale>
#include <thread>

#include "AllLevels.hpp"
#include "Utils.hpp"

/// @brief
/// Constructor for the Game class
/// @details
/// This constructor initializes the game by setting the player's position to
/// the starting position of the first level, loading the map of the first level
/// and setting the game to running.
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
	allLevels      = initLevels();
	m_currentLevel = 0;

	m_player.setX(allLevels[0].getStartingPosition().first);
	m_player.setY(allLevels[0].getStartingPosition().second);
	m_player.setAppearance(U'😀');
	m_player.setExperience(1);
	m_player.setSpeed(50);
	m_player.setAttackPower(1);
	m_player.setAttackRange(2);
	m_player.setAttackSpeed(1000);
	m_map.loadMap(allLevels[m_currentLevel].getMap());
}

Game::~Game() {
	// clean up
	delete[] visibleBuffer;
	delete[] hiddenBuffer;

	for (size_t i = 0; i < m_enemies.size(); i++) {
		delete m_enemies[i];
	}
}

/**
 * The game runs until the player dies or wins
 */
void Game::Run() {
	// Load first map from Levels folder
	LoadLevel(m_currentLevel);

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

	std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> converter;

	// clean console
	system("cls");

	// if player won
	if (m_currentLevel >= allLevels.size()) {
		std::cout << converter.to_bytes(U"You won!🎉") << std::endl;
		Sleep(2000);
	}
	// if player is dead
	if (m_player.getHealth() <= 0) {
		std::cout << converter.to_bytes(U"You died!😵") << std::endl;
		Sleep(2000);
	}

	// say goodbye
	std::cout << converter.to_bytes(U"Thanks for playing!😉") << std::endl;
	Sleep(2000);
	// clear console
	system("cls");
}

/**
 * It loads a level
 *
 * @param level The level to load
 *
 * @return The return value is a reference to the enemy object.
 */
void Game::LoadLevel(UINT level) {
	if (level < 0 || level >= allLevels.size()) {
		m_isRunning = false;
		return;
	}
	// clear enemies
	for (size_t i = 0; i < m_enemies.size(); i++) {
		m_map.removeCreature(m_enemies[i]->getId());
		delete m_enemies[i];
	}
	m_enemies.clear();

	// load new map
	m_map.loadMap(allLevels[level].getMap());
	m_player.setX(allLevels[level].getStartingPosition().first);
	m_player.setY(allLevels[level].getStartingPosition().second);
	m_map.addCreature(0, &m_player);

	// clear creatures id counter
	m_lastId = 0;

	for (size_t i = 0; i < allLevels[level].getEnemies().size(); i++) {
		Enemy* newEnemy = allLevels[level].getEnemies()[i];

		int newEnemyId = AddEnemy(newEnemy->getX(), newEnemy->getY());

		ModifyEnemy(newEnemyId).setAppearance(newEnemy->getAppearance());
		ModifyEnemy(newEnemyId).setAttackPower(newEnemy->getAttackPower());
		ModifyEnemy(newEnemyId).setHealth(newEnemy->getHealth());
		ModifyEnemy(newEnemyId).setSpeed(newEnemy->getSpeed());
		ModifyEnemy(newEnemyId).setAttackSpeed(newEnemy->getAttackSpeed());
		ModifyEnemy(newEnemyId).updateExperience();
	}

	return;
}

/**
 * It creates a new enemy, sets its position, appearance, and ID, and then adds
 * it to the map and the enemy list
 *
 * @param x The x coordinate of the enemy
 * @param y The y coordinate of the enemy
 *
 * @return The ID of the enemy.
 */
int Game::AddEnemy(int x, int y) {
	++m_lastId;
	Enemy* enemy = new Enemy(m_lastId);
	enemy->setX(x);
	enemy->setY(y);
	enemy->setAppearance(U'X');

	m_map.addCreature(m_lastId, enemy);
	m_enemies.push_back(enemy);

	return m_lastId;
}

/**
 * Find the index of the enemy with the given id
 *
 * @param id The id of the enemy you want to find.
 *
 * @return The index of the enemy in the vector.
 */
int Game::FindEnemy(int id) {
	for (size_t i = 0; i < m_enemies.size(); i++) {
		if (m_enemies[i]->getId() == id) {
			return i;
		}
	}
	return -1;
}

/**
 * It loops through the vector of enemies and checks if the enemy's x and y
 * coordinates are equal to the x and y coordinates passed in as parameters. If
 * they are, it returns the index of the enemy in the vector. If not, it returns
 * -1
 *
 * @param x The x coordinate of the enemy
 * @param y The y coordinate of the enemy
 *
 * @return The index of the enemy in the vector.
 */
int Game::FindEnemy(int x, int y) {
	for (size_t i = 0; i < m_enemies.size(); i++) {
		if (m_enemies[i]->getX() == x && m_enemies[i]->getY() == y) {
			return i;
		}
	}
	return -1;
}

/**
 * It removes an enemy from the game
 *
 * @param id The id of the enemy to remove
 */
void Game::RemoveEnemy(int id) {
	const int index = FindEnemy(id);

	m_map.removeCreature(id);
	delete m_enemies[index];
	m_enemies.erase(m_enemies.begin() + index);
}

/**
 * "The function returns a reference to the enemy object with the given id, or a
 * reference to the first enemy if the id is not found."
 *
 * The function first checks if the id is valid. If it is, it returns a
 * reference to the enemy object with the given id. If the id is not valid, it
 * returns a reference to the first enemy object
 *
 * @return A reference to the object.
 */
Enemy& Game::ModifyEnemy(int id) {
	const int index = FindEnemy(id);
	return *m_enemies[index];
}

/**
 * This function moves the player to the specified x and y coordinates.
 *
 * @param x The x coordinate of the player.
 * @param y The y coordinate of the player
 */
void Game::MovePlayer(int x, int y) {
	m_player.setX(x);
	m_player.setY(y);
}

/**
 * If the player's health is less than 0, set it to 0
 *
 * @param damage The amount of damage to be dealt to the player.
 */
void Game::HurtPlayer(int damage) {
	int newHealth = m_player.getHealth() - damage;
	if (newHealth < 0) {
		newHealth = 0;
	}
	m_player.setHealth(newHealth);
}
/**
 * HealPlayer() takes an integer as a parameter and adds it to the player's
 * current health. If the new health is greater than the player's max health,
 * then the new health is set to the player's max health
 *
 * @param health The amount of health to add to the player.
 */
void Game::HealPlayer(int health) {
	int newHealth = m_player.getHealth() + health;
	if (newHealth > m_player.getMaxHealth()) {
		newHealth = m_player.getMaxHealth();
	}
	m_player.setHealth(newHealth);
}

/**
 * It creates a string of hearts for the player's health, a string of bars for
 * the player's experience, and then combines them with the player's attack
 * power and level
 *
 * @return A string of the player's stats.
 */
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
	for (int i = 0; i < (m_player.getMaxHealth() - health) / 2; i++) {
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
	int prevLevelExp = m_player.getPrevLevelExp();
	// int expToNext    = nextLevelExp - exp;
	// int nowExp	   = exp - prevLevelExp;
	// always show 20 exp bars proportionally to the exp
	short int expBars = 20;
	for (int i = 0; i < expBars; i++) {
		if (exp >= prevLevelExp + (nextLevelExp - prevLevelExp) * i / expBars) {
			for (int j = 0; j < 2; j++) {
				expString += fullExp[j];
			}
		} else {
			for (int j = 0; j < 2; j++) {
				expString += emptyExp[j];
			}
		}
	}

	output += attack + L'\t' + healthHearts + L'\n' + level + L'\t' +
			  expString + L'\n';
	return output;
}

/**
 * It drops a random item at the given coordinates.
 *
 * @param x The x coordinate of the item to drop.
 * @param y The y coordinate of the item to drop.
 */
void Game::DropRandomItem(int x, int y) {
	// init random number generator
	srand(time(NULL));

	// healing sprites 🍪 🍩 🍭 🍦 🍔 🥕 🥐 🍏
	// Exp sprites 🌟
	// Attack sprites 🗡️
	// Range 🏹

	// Items we can drop
	std::vector<Item> healingItems = {
		Item("Cookie", U'🍪', 1, ItemType::Food),
		Item("Candy", U'🍭', 1, ItemType::Food),
		Item("Donut", U'🍩', 2, ItemType::Food),
		Item("Croissant", U'🥐', 2, ItemType::Food),
		Item("Ice Cream", U'🍦', 3, ItemType::Food),
		Item("Hamburger", U'🍔', 4, ItemType::Food),
		Item("Carrot", U'🥕', 5, ItemType::Food),
		Item("Apple", U'🍏', 5, ItemType::Food),
	};

	std::vector<Item> expItems = {
		Item("Star", U'🌟', rand() % 100, ItemType::Experience),
	};

	std::vector<Item> attackItems = {
		Item("Sword", U'💪', 1, ItemType::Weapon),
	};

	std::vector<Item> rangeItems = {
		Item("Bow", U'🏹', 1, ItemType::RangedWeapon),
	};

	int random = rand() % 1000;
	// 58% chance of dropping nothing
	//  20% chance of dropping healing item
	//  20% chance of dropping exp item
	//  1% chance of dropping attack item
	//  1% chance of dropping range item
	if (random < 580) {
		return;
	} else if (random < 780) {
		int randomItem = rand() % healingItems.size();
		m_map.addItem(&healingItems[randomItem], x, y);
	} else if (random < 980) {
		int randomItem = rand() % expItems.size();
		m_map.addItem(&expItems[randomItem], x, y);
	} else if (random < 990) {
		int randomItem = rand() % attackItems.size();
		m_map.addItem(&attackItems[randomItem], x, y);
	} else {
		int randomItem = rand() % rangeItems.size();
		m_map.addItem(&rangeItems[randomItem], x, y);
	}

	// TODO: make this better
}

/**
 * It returns a string that contains the player's inventory
 *
 * @return A string.
 */
std::string Game::showInventory() {
	std::vector<Item> inventory = m_player.getInventory();

	std::string output = "Inventory:";
	for (UINT i = 0; i < inventory.size(); i++) {
		output += '\t' + std::to_string(i + 1) + ". " + inventory[i].getName();
	}
	output += '\n';

	return output;
}

/**
 * It checks if the creature is on the tile.
 *
 * @param creature The creature to check.
 * @param tile The tile to check for.
 */
bool Game::isOnTile(Creature& creature, char32_t tile) {
	return m_map.getTileAppearance(creature.getX(), creature.getY()) == tile ||
		   m_map.getTileAppearance(creature.getX() + 1, creature.getY()) ==
			   tile;
}

/**
 * It checks if the creature is on an enemy
 *
 * @param creature The creature that is being checked.
 *
 * @return A boolean value.
 */
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

/**
 * It updates the game.
 */
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
	if (GetAsyncKeyState(VK_SPACE)) {
		bool wasAttacked = false;
		// find m_enemies in m_player.getAttackRange
		for (int i = -m_player.getAttackRange() * 2;
			 i <= m_player.getAttackRange() * 2; i++) {
			int foundEnemy = FindEnemy(m_player.getX() + i, m_player.getY());
			if (foundEnemy != -1) {
				// attack enemy
				wasAttacked = true;
				m_player.attack(*m_enemies[foundEnemy]);
				bool isDead = m_enemies[foundEnemy]->getHealth() <= 0;

				if (isDead) {
					// add exp
					m_player.setExperience(
						m_player.getExperience() +
						m_enemies[foundEnemy]->getExperience());
					// enemy is dead
					DropRandomItem(m_enemies[foundEnemy]->getX(),
								   m_enemies[foundEnemy]->getY());
					RemoveEnemy(m_enemies[foundEnemy]->getId());
				}
			}
		}
		for (int i = -m_player.getAttackRange(); i <= m_player.getAttackRange();
			 i++) {
			int foundEnemy = FindEnemy(m_player.getX(), m_player.getY() + i);
			if (foundEnemy != -1) {
				// attack enemy
				wasAttacked = true;
				m_player.attack(*m_enemies[foundEnemy]);
				bool isDead = m_enemies[foundEnemy]->getHealth() <= 0;

				if (isDead) {
					// add exp
					m_player.setExperience(
						m_player.getExperience() +
						m_enemies[foundEnemy]->getExperience());
					// enemy is dead
					DropRandomItem(m_enemies[foundEnemy]->getX(),
								   m_enemies[foundEnemy]->getY());
					RemoveEnemy(m_enemies[foundEnemy]->getId());
				}
			}
		}
		if (!wasAttacked) {
			m_player.attack();
		}
	}

	// if (GetAsyncKeyState((int)'E')) {
	// 	// increase experience
	// 	m_player.setExperience(m_player.getExperience() + 1);
	// }

	if (isOnTile(m_player, forbiddenTile) || isOnEnemy(m_player)) {
		// if so, move player back to previous position
		m_player.setX(prevX);
		m_player.setY(prevY);
	}

	// Pick up item
	if (m_map.getItem(m_player.getX(), m_player.getY()) != nullptr) {
		Item* pickedItem = m_map.getItem(m_player.getX(), m_player.getY());
		if (pickedItem->getType() == ItemType::Food) {
			m_player.setHealth(m_player.getHealth() + pickedItem->getValue());
		}
		if (pickedItem->getType() == ItemType::Weapon) {
			m_player.setAttackPower(m_player.getAttackPower() +
									pickedItem->getValue());
		}
		if (pickedItem->getType() == ItemType::RangedWeapon) {
			m_player.setAttackRange(m_player.getAttackRange() +
									pickedItem->getValue());
		}
		if (pickedItem->getType() == ItemType::Experience) {
			m_player.setExperience(m_player.getExperience() +
								   pickedItem->getValue());
		}
		m_player.addToInventory(pickedItem);

		m_map.removeItem(pickedItem);
	}

	// update position of visible melee weapons
	// if timer for attack is below attack speed /2

	if (duration_cast<milliseconds>(steady_clock::now() -
									m_player.getAttackTimer())
			.count() >= m_player.getAttackSpeed() / 4) {
		m_player.setIsMeleeAttack(false);
	}
	// add them to the map

	// exit game on escape
	if (GetAsyncKeyState(VK_ESCAPE)) {
		m_isRunning = false;
	}

	// if all enemies are dead, show exit
	if (m_enemies.size() == 0) {
		// add exit to map
		m_map.setTileAppearance(
			allLevels[m_currentLevel].getExitPosition().first,
			allLevels[m_currentLevel].getExitPosition().second, U'🚪');
		// if player on exit load next level
		if ((m_player.getX() ==
				 allLevels[m_currentLevel].getExitPosition().first ||
			 m_player.getX() + 1 ==
				 allLevels[m_currentLevel].getExitPosition().first) &&
			m_player.getY() ==
				allLevels[m_currentLevel].getExitPosition().second) {
			// load next level
			m_currentLevel++;
			LoadLevel(m_currentLevel);
		}
	}

	// update position of enemies
	for (size_t i = 0; i < m_enemies.size(); i++) {
		if (m_enemies[i]->checkLineOfSight(m_player, m_map)) {
			m_enemies[i]->moveTowardsPlayer(m_player);
		}
	}

	// check if player is dead
	if (m_player.getHealth() <= 0) {
		m_isRunning = false;
	}
}

/**
 * A function that is called before the render function.
 */
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
	// draw swords if player is attacking
	if (m_player.getIsMeleeAttack()) {
		std::vector<Creature*> attacks = m_player.getMeleeWeaponList();
		for (UINT i = 0; i < attacks.size(); i++) {
			bool isSurrogatePair;
			// check if
			std::wstring wstr =
				char32to16(attacks[i]->getAppearance(), &isSurrogatePair);

			for (UINT j = 0; j < wstr.length(); j++) {
				UINT coord = attacks[i]->getX() + j + 3 +
							 SCREEN_WIDTH * (attacks[i]->getY() + 4);
				hiddenBuffer[coord].Char.UnicodeChar = wstr[j];
				hiddenBuffer[coord].Attributes       = FG_COLORS::FG_WHITE;
			}
		}
	}

	// inventory no use
	// return;

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

/**
 * It copies the hidden buffer to the visible buffer, then draws the visible
 * buffer
 */
void Game::Render() {
	// copy hidden buffer to visible buffer
	for (int i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT; i++) {
		visibleBuffer[i] = hiddenBuffer[i];
	}

	// draw visible buffer
	WriteConsoleOutputW(GetStdHandle(STD_OUTPUT_HANDLE), visibleBuffer,
						bufferSize, bufferPos, &rect);
}