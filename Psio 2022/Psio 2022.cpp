#include <array>
#include <random>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Global.h"
#include "Player.h"
#include "Enemy.h"
#include <iostream>


sf::RectangleShape bar(int i) {
    int wid;
    wid = SCREEN_WIDTH / 17;
    sf::RectangleShape bar;
    bar.setSize(sf::Vector2f(wid, 5));
    if (i < 8) {
        bar.setPosition(sf::Vector2f((wid * (i * 2) + wid), 500));
    }
    else if (i < 16) {
        bar.setPosition(sf::Vector2f((wid * ((i - 8) * 2) + wid), 508));
    }
    else if (i < 24) {
        bar.setPosition(sf::Vector2f((wid * ((i - 16) * 2) + wid), 516));
    }
    return bar;
}



int main() {
    // create the window
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "GAME");
    window.setKeyRepeatEnabled(true);
    int lvl = 0;

    Player Player;
    Enemy enemy;

    std::vector<Enemy> enemis;
    std::vector<Bullet> bullets;
    std::vector<sf::RectangleShape> Barier;
    sf::Clock clock;
    sf::Time elapsed, PlayerR, EnemyR, move, beg;
    int v = 2000;
    sf::Text text, instruction;
    sf::String game("Game over");
    sf::String ins("A,D to Move\nSpacebar to shot\nWith each swarm of enemis game will be harder");
    sf::Font font;
    font.loadFromFile("ArialTh.ttf");
    instruction.setFont(font);
    instruction.setString(ins);
    instruction.setCharacterSize(50);
    text.setFont(font);
    text.setString(game);
    text.setCharacterSize(100);
    text.setPosition(SCREEN_WIDTH / 2 - text.getLocalBounds().width / 2, SCREEN_HEIGHT / 2);
    window.setFramerateLimit(60);


    // run the program as long as the window is open
    while (window.isOpen()) {
        if (beg.asMilliseconds() < 5000) {
            window.draw(instruction);
            beg += elapsed;
            elapsed = clock.restart();
        }
        else {

            PlayerR += elapsed;
            EnemyR += elapsed;
            move += elapsed;
            elapsed = clock.restart();

            sf::Event event;
            while (window.pollEvent(event)) {

                if (event.type == sf::Event::Closed)
                    window.close();
            }

            //Poruszanie się
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                Player.movePlayer('l', PLAYER_MOVE_SPEED);
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
                Player.movePlayer('r', PLAYER_MOVE_SPEED);
            }

            //Strzelanie
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                if (PlayerR.asMilliseconds() >= 1000) {
                    bullets.push_back(Player.shot());
                    PlayerR = elapsed;
                }
            }
            //Enemy creation
            if (enemis.size() == 0) {
                for (int i = 0; i < 55; i++)
                {
                    Enemy enemy;
                    enemy.Poz(i);
                    enemis.push_back(enemy);
                    lvl++;
                }
                //Barier creation
                for (int i = 0; i < 24; i++) {
                    Barier.push_back(bar(i));
                }
            }


            //Enemy move
            if (move.asMilliseconds() > 1500 - (lvl * 10)) {
                for (int i = 0; i < enemis.size(); i++) {
                    enemis[i].moveEnemy(ENEMY_MOVE_SPEED);
                    move = elapsed;
                    if (enemis[i].checkGame() == true) {
                        Player.getdead();
                    }
                }
            }

            //Enemy shot
            if (EnemyR.asMilliseconds() > v + 1000 - (lvl * 10)) {
                for (int i = 0; i < enemis.size(); i++) {
                    int v2 = rand() % 100;
                    if (v2 < 5) {
                        bullets.push_back(enemis[i].shot());

                    }
                }
                v = rand() % 1000;
                EnemyR = elapsed;
            }



            //Bullets colision


            for (auto i = enemis.begin(); i != enemis.end(); i++) {
                int v2 = rand() % 100;
                for (auto j = bullets.begin(); j != bullets.end(); j++) {
                    if (i->ChekDead(*j) == true) {
                        bullets.erase(j);
                        break;
                    }
                    if (Player.ChekDead(*j) == true) {
                        bullets.erase(j);
                        break;
                    }
                }
            }
            for (auto i = Barier.begin(); i != Barier.end(); i++) {
                int v2 = rand() % 100;
                for (auto j = bullets.begin(); j != bullets.end(); j++) {
                    if (j->getRight() > i->getPosition().x &&
                        j->getTop() < i->getPosition().y + i->getGlobalBounds().height &&
                        j->getBottom() > i->getPosition().y &&
                        j->getLeft() < i->getPosition().x + i->getGlobalBounds().width) {
                        Barier.erase(i);
                        bullets.erase(j);
                        break;


                    }
                }
            }

            //Player
            for (auto i = bullets.begin(); i != bullets.end(); i++) {
                if (i->destroy() == true) {
                    bullets.erase(i);
                    //std::cout << bullets.size()<<std::endl;
                    break;
                }
            }
            for (auto i = enemis.begin(); i != enemis.end(); i++) {
                if (i->Edead() == true) {
                    enemis.erase(i);
                    break;
                }
            }

            // draw
            window.clear();
            if (Player.GameSteat() == false) {
                Player.draw(window);
                for (auto i = bullets.begin(); i < bullets.end(); i++)
                {
                    i->move();
                    i->draw(window);
                }
                for (auto i = enemis.begin(); i != enemis.end(); i++)
                {
                    i->draw(window);
                }
                for (auto i = Barier.begin(); i < Barier.end(); i++)
                {
                    window.draw(*i);
                }
            }
            else {
                window.draw(text);
            }
        }
        // end the current frame;;
        window.display();
    }

    return 0;
}