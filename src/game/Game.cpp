#include "Game.hpp"

Game::Game() : m_window(sf::VideoMode({800, 600}), "My Game") {
  m_player.setSize({40.0f, 40.0f});
  m_player.setOrigin(m_player.getSize() * 2.0f);
  m_player.setPosition({400.0f, 300.0f});
  m_player.setFillColor(sf::Color::White);
}

void Game::run() {
  sf::Clock clock;

  while (m_window.isOpen()) {
    const float dt = clock.restart().asSeconds();

    processEvents();
    update(dt);
    render();
  }
}

void Game::processEvents() {
  while (const auto event = m_window.pollEvent()) {
    if (event->is<sf::Event::Closed>()) {
      m_window.close();
    }
  }
}

void Game::update(float dt) {
  sf::Vector2f dir{0.0f, 0.0f};

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
    dir.y -= 1.0f;
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
    dir.y += 1.0f;
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
    dir.x -= 1.0f;
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
    dir.x += 1.0f;

  if (dir.lengthSquared() > 0.0f)
    dir = dir.normalized();

  m_player.move(dir * (m_playerSpeed * dt));
}

void Game::render() {
  m_window.clear(sf::Color::Black);
  m_window.draw(m_player);
  m_window.display();
}
