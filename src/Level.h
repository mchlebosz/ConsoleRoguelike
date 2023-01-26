#pragma once
#include <windows.h>

#include <iostream>
#include <string>
#include <vector>

#include "Enemy.h"

class Level {
public:
	Level();

	Level(std::vector<std::u32string> map, std::pair<int, int> startingPosition,
		  std::pair<int, int> exitPosition, std::vector<Enemy*> enemies);

	virtual ~Level() = default;

	// getters
	std::vector<std::u32string> getMap() const;
	std::pair<int, int> getStartingPosition() const;
	std::pair<int, int> getExitPosition() const;
	std::vector<Enemy*> getEnemies() const;

	// setters
	void setMap(std::vector<std::u32string>);
	void setStartingPosition(std::pair<int, int> startingPosition);
	void setExitPosition(std::pair<int, int> exitPosition);
	void setEnemies(std::vector<Enemy*> enemies);

private:
	// variables
	std::vector<std::u32string> m_tiles;

	// pair starting position
	std::pair<int, int> m_startingPosition;

	std::pair<int, int> m_exitPosition;

	std::vector<Enemy*> m_enemies;
};