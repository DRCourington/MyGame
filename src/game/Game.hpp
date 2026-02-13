#pragma once

#include <SFML/Graphics.hpp>

class Game {
public:
  Game();
  void run();

private:
  void processEvents();
  void update(float dt);
  void render();

private:
  sf::RenderWindow m_window;
  sf::RectangleShape m_player;
  float m_playerSpeed = 260.0f; // pixels per second
};
