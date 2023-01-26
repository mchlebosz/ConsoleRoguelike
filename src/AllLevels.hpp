#pragma once

#include <fstream>
#include <iostream>
#include <vector>

#include "Level.h"

/*
	Working Chars
	 🚪  🥰 🥴 🤢 🤮  😈 👿 💀 👽 👻 🤖 🦂 🍪 🍩 🍭 🍦 🍔 🌟
	 👹👺🤡🐲🐍🐭🦂

	*/
// types of enemies
// store them in  structure

typedef struct {
	char32_t symbol;
	int health;
	int damage;
	int speed;
	int attackSpeed;
} EnemyType;

EnemyType mouse    = { U'🐭', 1, 1, 6, 4 };       // Exp: 1*1*6*4 = 24
EnemyType scorpion = { U'🦂', 1, 2, 4, 4 };       // Exp: 1*2*4*4 = 32
EnemyType snake    = { U'🐍', 5, 2, 2, 3 };       // Exp: 5*2*2*3 = 60
EnemyType ghost    = { U'👻', 5, 2, 6, 5 };       // Exp: 5*2*6*5 = 300
EnemyType skeleton = { U'💀', 6, 3, 5, 4 };       // Exp: 6*3*5*4 = 360
EnemyType demon    = { U'😈', 10, 3, 4, 4 };      // Exp: 10*3*4*4 = 480
EnemyType troll    = { U'👺', 30, 3, 4, 3 };      // Exp: 30*3*4*3 = 720
EnemyType ogre     = { U'👹', 50, 5, 2, 2 };      // Exp: 50*5*2*2 = 1000
EnemyType dragon   = { U'🐲', 100, 5, 3, 3 };     // Exp: 100*5*3*3 = 4500
EnemyType clown    = { U'🤡', 1000, 8, 5, 5 };    // Exp: 1000*8*5*5 = 40000

std::vector<Level> initLevels() {
	std::vector<Level> allLevels;

	// add levels here

	allLevels.push_back(Level(
		std::vector<std::u32string> {
			U"█████████████████████████████████████████████████",
			U"██                                             ██",
			U"██                                             ██",
			U"██                                             ██",
			U"██                                             ██",
			U"██                                             ██",
			U"█████████████████████████████████              ██",
			U"██                                             ██",
			U"██                                             ██",
			U"██                                             ██",
			U"██                                             ██",
			U"██                                             ██",
			U"██                                             ██",
			U"██                                             ██",
			U"██                                             ██",
			U"█████████████████████████████████████████████████" },
		std::make_pair(4, 2), std::make_pair(4, 8),
		std::vector<Enemy*> {
			new Enemy(0, mouse.symbol, 30, 3, mouse.health, mouse.damage,
					  mouse.speed, mouse.attackSpeed),
			new Enemy(1, mouse.symbol, 10, 10, mouse.health, mouse.damage,
					  mouse.speed, mouse.attackSpeed),
			new Enemy(2, mouse.symbol, 42, 13, mouse.health, mouse.damage,
					  mouse.speed, mouse.attackSpeed),
		}));

	allLevels.push_back(Level(
		std::vector<std::u32string> {
			U"█████████████████████████████████████████████████",
			U"██                           ██                ██",
			U"██                           ██                ██",
			U"██                                             ██",
			U"██                           ██                ██",
			U"██                           ██                ██",
			U"███████████████████████████████████        ██████",
			U"██                        ██                   ██",
			U"██                        ██                   ██",
			U"██                        ██                   ██",
			U"██                        ██                   ██",
			U"██                        ██                   ██",
			U"██                        ██                   ██",
			U"██                        ████████             ██",
			U"██                                             ██",
			U"█████████████████████████████████████████████████" },
		std::make_pair(4, 8), std::make_pair(4, 3),
		std::vector<Enemy*> {
			new Enemy(0, mouse.symbol, 30, 10, mouse.health, mouse.damage,
					  mouse.speed, mouse.attackSpeed),
			new Enemy(1, mouse.symbol, 35, 2, mouse.health, mouse.damage,
					  mouse.speed, mouse.attackSpeed),
			new Enemy(2, scorpion.symbol, 12, 5, scorpion.health,
					  scorpion.damage, scorpion.speed,
					  scorpion.attackSpeed) }));

	allLevels.push_back(Level(
		std::vector<std::u32string> { U"███████████████████████████████",
									  U"██                           ██",
									  U"██                           ██",
									  U"██                           ██",
									  U"██                           ██",
									  U"██                           ██",
									  U"██             ████████████████",
									  U"██                           ██",
									  U"██                           ██",
									  U"██                           ██",
									  U"██                           ██",
									  U"██                           ██",
									  U"████████████████████         ██",
									  U"██                           ██",
									  U"██                           ██",
									  U"██                           ██",
									  U"██                           ██",
									  U"██                           ██",
									  U"███████████████████████████████" },
		std::make_pair(4, 3), std::make_pair(4, 15),
		std::vector<Enemy*> {
			new Enemy(0, mouse.symbol, 25, 2, mouse.health, mouse.damage,
					  mouse.speed, mouse.attackSpeed),
			new Enemy(1, scorpion.symbol, 12, 10, scorpion.health,
					  scorpion.damage, scorpion.speed, scorpion.attackSpeed),
			new Enemy(2, scorpion.symbol, 15, 16, scorpion.health,
					  scorpion.damage, scorpion.speed,
					  scorpion.attackSpeed) }));

	allLevels.push_back(Level(
		std::vector<std::u32string> {
			U"██████████████████████████████████████████████████████████████████████████████████████████████████",
			U"██                                             ████                                             ██",
			U"██                                             ████                                             ██",
			U"██                                             ████                                             ██",
			U"██                                             ████                                             ██",
			U"██                                             ████                                             ██",
			U"█████████████████████████████████              ███████████████████████████████████              ██",
			U"██                                             ████                             ██              ██",
			U"██                                             ████                             ██              ██",
			U"██                                             ████                             ██              ██",
			U"██                                                                              ██              ██",
			U"██                                                                              ██              ██",
			U"██                                             ████                                             ██",
			U"██                                             ████                                             ██",
			U"██                                             ████                                             ██",
			U"██████████████████████  ██████████████████████████████████████████████████████████████████████████",
			U"     ██                                  ██                                                       ",
			U"     ██                                  ██                                                       ",
			U"     ██                                  ██                                                       ",
			U"     ██                                  ██                                                       ",
			U"     ██                                  ██                                                       ",
			U"     ██                                  ██                                                       ",
			U"     ██                                  ██                                                       ",
			U"     ██                                  ██                                                       ",
			U"     ██                                  ██                                                       ",
			U"     ██                                  ██                                                       ",
			U"     ██                                  ██                                                       ",
			U"     ██████████████████████████████████████                                                       " },
		std::make_pair(8, 20), std::make_pair(4, 8),
		std::vector<Enemy*> {
			new Enemy(0, scorpion.symbol, 12, 10, scorpion.health,
					  scorpion.damage, scorpion.speed, scorpion.attackSpeed),
			new Enemy(1, scorpion.symbol, 15, 16, scorpion.health,
					  scorpion.damage, scorpion.speed, scorpion.attackSpeed),
			new Enemy(2, scorpion.symbol, 55, 13, scorpion.health,
					  scorpion.damage, scorpion.speed, scorpion.attackSpeed),
			new Enemy(3, snake.symbol, 52, 3, snake.health, snake.damage,
					  snake.speed, snake.attackSpeed),
			new Enemy(4, snake.symbol, 28, 3, snake.health, snake.damage,
					  snake.speed, snake.attackSpeed),
		}));

	allLevels.push_back(Level(
		std::vector<std::u32string> {
			U"██████████████████████████████████████████████████████████████████████████████████████████████████",
			U"██                                             ████                                             ██",
			U"██                                             ████                                             ██",
			U"██                                             ████                                             ██",
			U"██                                             ████                                             ██",
			U"██                                             ████                                             ██",
			U"█████████████████████████████████              ██████████████    █████████████████              ██",
			U"██                                             ████                             ██              ██",
			U"██                                             ████                             ██              ██",
			U"██                                             ████                             ██              ██",
			U"██                                                                              ██              ██",
			U"██                                                                              ██              ██",
			U"██                                             ████                             ██              ██",
			U"██                                             ████                             ██              ██",
			U"██                                             ████                             ██              ██",
			U"████████████████████    ██████████████████████████████████████████████████████████████████████████",
			U"     ██                                  ████                                  ██                 ",
			U"     ██                                  ████                                  ██                 ",
			U"     ██                                  ████                                  ██                 ",
			U"     ██                                  ████                                  ██                 ",
			U"     ██                                  ████                                  ██                 ",
			U"     ██                                  ████                                  ██                 ",
			U"     ██                                                                        ██                 ",
			U"     ██                                  ████                                  ██                 ",
			U"     ██                                  ████                                  ██                 ",
			U"     ██                                  ████                                  ██                 ",
			U"     ██                                  ████                                  ██                 ",
			U"     ████████████████████████████████████████████████████████████████████████████                 " },
		std::make_pair(4, 8), std::make_pair(60, 21),
		std::vector<Enemy*> {
			new Enemy(0, snake.symbol, 12, 10, snake.health, snake.damage,
					  snake.speed, snake.attackSpeed),
			new Enemy(1, snake.symbol, 15, 16, snake.health, snake.damage,
					  snake.speed, snake.attackSpeed),
			new Enemy(2, snake.symbol, 55, 13, snake.health, snake.damage,
					  snake.speed, snake.attackSpeed),
			new Enemy(3, ghost.symbol, 52, 3, ghost.health, ghost.damage,
					  ghost.speed, ghost.attackSpeed),
			new Enemy(4, ghost.symbol, 90, 10, ghost.health, ghost.damage,
					  ghost.speed, ghost.attackSpeed),
			new Enemy(5, ghost.symbol, 10, 3, ghost.health, ghost.damage,
					  ghost.speed, ghost.attackSpeed),
			new Enemy(6, ghost.symbol, 60, 20, ghost.health, ghost.damage,
					  ghost.speed, ghost.attackSpeed)

		}));

	return allLevels;
}
