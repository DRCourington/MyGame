#include "Engine.hpp"

Engine::Engine()
    : m_window(sf::VideoMode({800, 600}), "MyGame"),
      m_fonts("assets",
              [](sf::Font &f, const std::filesystem::path &p) {
                return f.openFromFile(p);
              }),
      m_textures("assets",
                 [](sf::Texture &t, const std::filesystem::path &p) {
                   return t.loadFromFile(p);
                 }),
      m_sfx("assets",
            [](sf::SoundBuffer &b, const std::filesystem::path &p) {
              return b.loadFromFile(p);
            }),
      m_music("assets"), m_debugText() {

  m_window.setVerticalSyncEnabled(true);

  m_music.play("music/ReturnOfThe8BitEra.mp3", true);

  sf::Font &font = m_fonts.get("fonts/Moogalator.ttf");

  m_debugText.emplace(font, "Engine Running", 24);
  m_debugText->setPosition({20.f, 20.f});
  m_debugText->setFillColor(sf::Color::White);

  {
    sf::RectangleShape rect({200.f, 80.f});
    rect.setPosition({100.f, 120.f});
    rect.setFillColor(sf::Color(50, 200, 80));
    rect.setOutlineThickness(3.f);
    rect.setOutlineColor(sf::Color::Black);
    m_rect = &m_shapes.add(rect);
  }

  {
    sf::CircleShape circ(50.f);
    circ.setPosition({400.f, 100.f});
    circ.setFillColor(sf::Color(80, 160, 255));
    m_shapes.add(circ);
  }

  {
    sf::ConvexShape tri;
    tri.setPointCount(3);
    tri.setPoint(0, {0.f, 80.f});
    tri.setPoint(1, {60.f, 0.f});
    tri.setPoint(2, {120.f, 80.f});
    tri.setPosition({550.f, 350.f});
    tri.setFillColor(sf::Color(255, 140, 0));
    m_shapes.add(tri);
  }
}

void Engine::run() {
  while (m_window.isOpen()) {
    processEvents();
    const float dt = m_clock.restart().asSeconds();
    update(dt);
    render();
  }
}

void Engine::processEvents() {
  while (const std::optional event = m_window.pollEvent()) {
    if (event->is<sf::Event::Closed>())
      m_window.close();
  }
}

void Engine::update(float dt) {
  if (!m_rect)
    return;

  auto pos = m_rect->getPosition();
  pos.x += 100.f * dt; // 100 pixels/sec to the right

  if (pos.x > 800.f)
    pos.x = -200.f; // wrap (rect width ~200)
  m_rect->setPosition(pos);

  m_fpsAccum += dt;
  m_fpsFrames += 1;

  if (m_fpsAccum >= m_fpsUpdateInterval) {
    const float fps = static_cast<float>(m_fpsFrames) / m_fpsAccum;

    if (m_debugText) {
      m_debugText->setString("FPS: " +
                             std::to_string(static_cast<int>(fps + 0.5f)));
    }

    m_fpsAccum = 0.f;
    m_fpsFrames = 0;
  }
}

void Engine::render() {
  m_window.clear();

  m_shapes.draw(m_window);

  if (m_debugText)
    m_window.draw(*m_debugText);

  m_window.display();
}
