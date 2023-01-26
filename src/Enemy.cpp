#include "Enemy.h"

/**
 * Enemy::Enemy(int id) : Creature() {
 *
 * @param id The id of the enemy.
 */
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
	m_experience  = m_health * m_attackPower * m_speed * m_attackSpeed;
	m_moveTimer   = steady_clock::now();
	m_attackTimer = steady_clock::now();
	m_speed       = 500;
	m_attackSpeed = 1000;
}

/**
 * The Enemy constructor initializes the member variables of the Enemy class
 *
 * @param id The id of the enemy.
 * @param appearance The character that will be used to represent the enemy on
 * the map.
 * @param x The x coordinate of the enemy.
 * @param y The y coordinate of the enemy.
 * @param health The amount of health the enemy has.
 * @param attackPower How much damage the enemy does when it attacks.
 * @param speed How many tiles the enemy can move per second.
 * @param attackSpeed The number of milliseconds between attacks.
 */
Enemy::Enemy(int id, char32_t appearance, int x, int y, int health,
			 int attackPower, int speed, int attackSpeed) :
	Creature(id, appearance, x, y, health),
	m_attackPower(attackPower),
	m_speed(speed),
	m_attackSpeed(attackSpeed) {
	m_experience  = m_health * m_attackPower * m_speed * m_attackSpeed;
	m_moveTimer   = steady_clock::now();
	m_attackTimer = steady_clock::now();
}

void Enemy::move() {
	// TODO: Implement enemy movement
}

/**
 * If the time since the last attack is greater than 3000 / attackSpeed, then
 * attack
 *
 * @param other The creature that is being attacked.
 */
void Enemy::attack(Creature &other) {
	auto timer = steady_clock::now();

	if (duration_cast<milliseconds>(timer - m_attackTimer).count() >
		3000 / m_attackSpeed) {
		m_attackTimer = timer;
		other.setHealth(other.getHealth() - m_attackPower);
	}
}

/**
 * The function returns the value of the private member variable m_type
 *
 * @return The type of enemy.
 */
std::string Enemy::getType() const {
	return m_type;
}

/**
 * The function takes a string as a parameter and sets the m_type variable to
 * that string
 *
 * @param type The type of enemy.
 */
void Enemy::setType(std::string type) {
	m_type = type;
}

/**
 * This function returns the dodge chance of the enemy
 *
 * @return The dodge chance of the enemy.
 */
int Enemy::getDodgeChance() const {
	return m_dodgeChance;
}

/**
 * This function sets the dodge chance of the enemy
 *
 * @param dodgeChance The chance that the enemy will dodge an attack.
 */
void Enemy::setDodgeChance(int dodgeChance) {
	m_dodgeChance = dodgeChance;
}
/**
 * This function returns the value of the private member variable m_attackPower.
 *
 * @return The attack power of the enemy.
 */

int Enemy::getAttackPower() const {
	return m_attackPower;
}

/**
 * This function sets the attack power of the enemy.
 *
 * @param attackPower The amount of damage the enemy will do to the player.
 */
void Enemy::setAttackPower(int attackPower) {
	m_attackPower = attackPower;
}

/**
 * The function returns a copy of the vector of items
 *
 * @return A vector of items.
 */
std::vector<Item> Enemy::getItems() const {
	return m_items;
}

/**
 * `void Enemy::setItems(std::vector<Item> items)`
 *
 * The function is called `setItems` and it's a member function of the `Enemy`
 * class. It takes a single parameter, which is a vector of `Item` objects. The
 * function returns nothing
 *
 * @param items The items that the enemy will drop when killed.
 */
void Enemy::setItems(std::vector<Item> items) {
	m_items = items;
}

/**
 * This function adds an item to the enemy's inventory
 *
 * @param item The item to add to the enemy's inventory.
 */
void Enemy::addToItems(Item item) {
	m_items.push_back(item);
}

/**
 * This function returns the value of the private member variable m_experience.
 *
 * @return The value of m_experience.
 */
int Enemy::getExperience() const {
	return m_experience;
}

/**
 * This function updates the experience of the enemy by multiplying the health,
 * attack power, speed, and attack speed of the enemy.
 */
void Enemy::updateExperience() {
	m_experience = m_health * m_attackPower * m_speed * m_attackSpeed;
}

/**
 * If the enemy is on the same tile as the player, attack the player
 *
 * @param player The player object
 *
 * @return Nothing.
 */
void Enemy::moveTowardsPlayer(Creature &player) {
	auto timer = steady_clock::now();

	if (duration_cast<milliseconds>(timer - m_moveTimer).count() >
		3000 / m_speed) {
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
/**
 * It returns a vector of all the tiles that are on the line between two given
 * tiles
 *
 * @param tile1 The first tile in the line.
 * @param tile2 The tile you want to get to.
 *
 * @return A vector of pairs of ints.
 */
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

/**
 * It returns true if the player is in the enemy's line of sight, and false if
 * the player is not in the enemy's line of sight
 *
 * @param player The player object
 * @param map The map object
 *
 * @return A vector of pairs of ints.
 */
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

// getters and setters for speed and attack speed
/**
 * This function returns the value of the private member variable m_speed.
 *
 * @return The speed of the enemy.
 */
int Enemy::getSpeed() const {
	return m_speed;
}

/**
 * This function sets the speed of the enemy
 *
 * @param speed The speed of the enemy.
 */
void Enemy::setSpeed(int speed) {
	m_speed = speed;
}

/**
 * This function returns the value of the private member variable m_attackSpeed
 *
 * @return The attack speed of the enemy.
 */
int Enemy::getAttackSpeed() const {
	return m_attackSpeed;
}

/**
 * This function sets the attack speed of the enemy
 *
 * @param attackSpeed The speed at which the enemy attacks.
 */
void Enemy::setAttackSpeed(int attackSpeed) {
	m_attackSpeed = attackSpeed;
}