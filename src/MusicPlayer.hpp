#pragma once
#include <SFML/Audio.hpp>

#include <filesystem>
#include <stdexcept>
#include <utility>

class MusicPlayer {
public:
  explicit MusicPlayer(std::filesystem::path basePath)
      : m_basePath(std::move(basePath)) {}

  void play(const std::filesystem::path &relativePath, bool loop = true) {
    const auto fullPath = m_basePath / relativePath;

    m_music.stop();
    if (!m_music.openFromFile(fullPath)) {
      throw std::runtime_error(
          "MusicPlayer: failed to open '" + fullPath.string() +
          "' (cwd=" + std::filesystem::current_path().string() + ")");
    }

    m_music.setLooping(loop);
    m_music.play();
  }

  void stop() { m_music.stop(); }
  void pause() { m_music.pause(); }
  void resume() {
    if (m_music.getStatus() == sf::SoundSource::Status::Paused)
      m_music.play();
  }
  void setVolume(float volume) { m_music.setVolume(volume); }
  float getVolume() const { return m_music.getVolume(); }

private:
  std::filesystem::path m_basePath;
  sf::Music m_music;
};
