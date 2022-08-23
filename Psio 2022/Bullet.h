#pragma once
#include "Global.h"
#include <SFML/Graphics.hpp>

class Bullet {
public:
	Bullet() {
		bullet.setSize(sf::Vector2f(6.0, 10.0));
		up = false;
	}

	void setposition(float x, float y) {
		bullet.setPosition(x, y);
	}

	void fire() {
		bullet.move(PLAYER_BULLET_SPEED, 0);
	}
	void navigation(bool t) {
		if (t == true) {
			up = true;
		}
		else
		{
			up = false;
		}
	}
	void move() {
		if (up == true) {
			bullet.move(0, PLAYER_BULLET_SPEED * -1);
		}
		else {
			bullet.move(0, ENEMY_BULLET_SPEED);
		}
	}

	int getRight() {
		return bullet.getPosition().x + bullet.getSize().x;
	}

	int getLeft() {
		return bullet.getPosition().x;
	}

	int getTop() {
		return bullet.getPosition().y;
	}

	int getBottom() {
		return bullet.getPosition().y + bullet.getSize().y;
	}

	void draw(sf::RenderWindow& window) {
		window.draw(bullet);
	}
	bool destroy() {
		if (bullet.getPosition().y < 0 || bullet.getPosition().y> SCREEN_HEIGHT) {
			return true;
		}
	}
	void Id() {
		Player = true;
	}
	bool chek() {
		return Player;
	}
private:
	sf::RectangleShape bullet;
	bool up;
	bool Player = false;
};