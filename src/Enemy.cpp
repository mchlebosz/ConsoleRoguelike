#include "Enemy.h"

Enemy::Enemy(int id) : Creature() {
	m_id          = id;
	m_appearance  = U'X';
	m_type        = "None";
	m_dodgeChance = 0;
	m_attackPower = 1;
	m_items       = std::vector<Item>();
	m_health      = 10;
	m_x           = 0;
	m_y           = 0;
	m_experience  = m_health * m_attackPower;
	m_moveTimer   = steady_clock::now();
	m_attackTimer = steady_clock::now();
}

Enemy::Enemy(int id, char32_t appearance, int x, int y, int health,
			 int attackPower) :
	Creature(id, appearance, x, y, health), m_attackPower(attackPower) {
	m_experience  = health * attackPower;
	m_moveTimer   = steady_clock::now();
	m_attackTimer = steady_clock::now();
}

void Enemy::move() {
	// TODO: Implement enemy movement
}

void Enemy::attack(Creature &other) {
	auto timer = steady_clock::now();

	if (duration_cast<milliseconds>(timer - m_attackTimer).count() > 1000) {
		m_attackTimer = timer;
		other.setHealth(other.getHealth() - m_attackPower);
	}
}

std::string Enemy::getType() const {
	return m_type;
}

void Enemy::setType(std::string type) {
	m_type = type;
}

int Enemy::getDodgeChance() const {
	return m_dodgeChance;
}

void Enemy::setDodgeChance(int dodgeChance) {
	m_dodgeChance = dodgeChance;
}

int Enemy::getAttackPower() const {
	return m_attackPower;
}

void Enemy::setAttackPower(int attackPower) {
	m_attackPower = attackPower;
}

std::vector<Item> Enemy::getItems() const {
	return m_items;
}

void Enemy::setItems(std::vector<Item> items) {
	m_items = items;
}

void Enemy::addToItems(Item item) {
	m_items.push_back(item);
}

int Enemy::getExperience() const {
	return m_experience;
}

void Enemy::moveTowardsPlayer(Creature &player) {
	auto timer = steady_clock::now();

	if (duration_cast<milliseconds>(timer - m_moveTimer).count() > 500) {
		int prevX = getX();
		int prevY = getY();

		m_moveTimer = timer;
		int playerX = player.getX();
		int playerY = player.getY();

		int x = getX();
		int y = getY();

		if (playerX > x) {
			x++;
		} else if (playerX < x) {
			x--;
		}

		if (playerY > y) {
			y++;
		} else if (playerY < y) {
			y--;
		}

		setX(x);
		setY(y);

		// Check if the enemy is on the same tile as the player
		if ((playerX == x || playerX + 1 == x || playerX - 1 == x) &&
			playerY == y) {
			attack(player);
			setX(prevX);
			setY(prevY);
		}

		return;
	}
}

// Bresenham's line algorithm
std::vector<std::pair<int, int>> get_tiles_on_line(std::pair<int, int> tile1,
												   std::pair<int, int> tile2) {
	std::vector<std::pair<int, int>> tiles;
	int x1 = tile1.first, y1 = tile1.second, x2 = tile2.first,
		y2 = tile2.second;
	int dx = abs(x2 - x1), dy = abs(y2 - y1);
	int sx = x1 < x2 ? 1 : -1, sy = y1 < y2 ? 1 : -1;
	int err = dx - dy;

	while (true) {
		tiles.push_back(std::make_pair(x1, y1));
		if (x1 == x2 && y1 == y2) break;
		int e2 = 2 * err;
		if (e2 > -dy) {
			err -= dy;
			x1 += sx;
		}
		if (e2 < dx) {
			err += dx;
			y1 += sy;
		}
	}
	return tiles;
}

bool Enemy::checkLineOfSight(Creature &player, Map &map) {
	int playerX = player.getX();
	int playerY = player.getY();

	int x = getX();
	int y = getY();

	char32_t wall = U'█';

	std::vector<std::pair<int, int>> tiles = get_tiles_on_line(
		std::make_pair(x, y), std::make_pair(playerX, playerY));

	for (auto tile : tiles) {
		if (map.getTileAppearance(tile.first, tile.second) == wall) {
			return false;
		}
	}

	return true;
}