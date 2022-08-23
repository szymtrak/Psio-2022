#pragma once

#include"Bullet.h"
class Player
{



public:
	Player() {
		texture.loadFromFile("player.png");
		sprite.setTexture(texture);
		sprite.setScale(3, 3);
		sprite.setPosition(430, 550);
	}
	void draw(sf::RenderWindow& window) {
		window.draw(sprite);
	}
	void movePlayer(char direction, float moveSpeed) {
		if (direction == 'l') {
			if (sprite.getGlobalBounds().left + sprite.getGlobalBounds().width < SCREEN_WIDTH) {
				sprite.move(moveSpeed, 0);
			}
		}
		else if (direction == 'r') {
			if (sprite.getGlobalBounds().left > 0) {
				sprite.move(-moveSpeed, 0);
			}
		}
	}

	bool ChekDead(Bullet bullet) {
		if (bullet.getRight() > sprite.getPosition().x &&
			bullet.getTop() < sprite.getPosition().y + sprite.getGlobalBounds().height &&
			bullet.getBottom() > sprite.getPosition().y &&
			bullet.getLeft() < sprite.getPosition().x + sprite.getGlobalBounds().width &&
			bullet.chek() == false) {
			dead = true;
			return true;
		}
		else {
			return false;
		}
	}

	void getdead() {
		dead = true;
	}

	bool GameSteat() {
		return dead;
	}

	Bullet shot() {
		Bullet bullet;
		float x, y;
		x = sprite.getPosition().x;
		y = sprite.getPosition().y;
		bullet.setposition(x + (sprite.getGlobalBounds().width / 2), y);
		bool t = true;
		bullet.navigation(t);
		bullet.Id();
		return bullet;
	}



private:
	sf::Texture texture;
	sf::Sprite sprite;
	bool dead = false;


};

