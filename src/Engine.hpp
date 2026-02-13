#pragma once
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include <optional>

#include "AssetCache.hpp"
#include "MusicPlayer.hpp"
#include "ShapeRenderer.hpp"

class Engine {
public:
  Engine();
  void run();

private:
  void processEvents();
  void update(float dt);
  void render();

  sf::RenderWindow m_window;
  sf::Clock m_clock;

  AssetCache<sf::Font> m_fonts;
  AssetCache<sf::Texture> m_textures;
  AssetCache<sf::SoundBuffer> m_sfx;
  MusicPlayer m_music;

  std::optional<sf::Text> m_debugText;

  float m_fpsAccum = 0.f;
  unsigned m_fpsFrames = 0;
  float m_fpsUpdateInterval = 0.25f;

  ShapeRenderer m_shapes;

  sf::RectangleShape *m_rect = nullptr;
};
