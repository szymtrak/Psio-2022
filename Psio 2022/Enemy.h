#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

class Enemy
{
public:
	Enemy()
	{
		texture.loadFromFile("enemy.png");
		sprite.setColor(sf::Color::Green);
		sprite.setScale(3, 3);
	}

	void Poz(int i) {
		i += 1;
		if (i < 12) {
			sprite.setPosition(70 * i, 10);
		}
		if (i >= 12 && i < 23) {
			sprite.setPosition(70 * (i - 11), 50);
		}
		if (i >= 23 && i < 34) {
			sprite.setPosition(70 * (i - 22), 90);
		}
		if (i >= 34 && i < 45) {
			sprite.setPosition(70 * (i - 33), 130);
		}
		if (i >= 45) {
			sprite.setPosition(70 * (i - 44), 170);
		}
	}


	void moveEnemy(float moveSpeed) {
		if (move < 10 || (move >= 28 && move < 36)) {
			sprite.move(moveSpeed, 0);
			move++;
		}
		else if (move >= 10 && move < 28) {
			sprite.move(-moveSpeed, 0);
			move++;
		}
		else if (move == 36) {
			sprite.move(0, 40);
			move = 0;
		}
	}

	bool checkGame() {
		if (sprite.getPosition().y < 0) {
			return true;
		}
		else {
			return false;
		}
	}

	bool Edead() {
		return dead;
	}

	bool ChekDead(Bullet bullet) {
		if (bullet.getRight() > sprite.getPosition().x &&
			bullet.getTop() < sprite.getPosition().y + sprite.getGlobalBounds().height &&
			bullet.getBottom() > sprite.getPosition().y &&
			bullet.getLeft() < sprite.getPosition().x + sprite.getGlobalBounds().width &&
			bullet.chek() == true) {
			dead = true;
			return true;
		}
		else {
			return false;
		}
	}



	Bullet shot() {
		Bullet bullet;
		float x, y;
		x = sprite.getPosition().x;
		y = sprite.getPosition().y;
		bullet.setposition(x + (sprite.getGlobalBounds().width / 2), y - sprite.getGlobalBounds().height);
		bool t = false;
		bullet.navigation(t);
		return bullet;
	}

	void draw(sf::RenderWindow& window) {
		sprite.setTexture(texture);
		window.draw(sprite);
	}
private:
	sf::Texture texture;
	sf::Sprite sprite;
	int move = 0;
	bool dead = false;
};