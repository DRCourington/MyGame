#include <SFML/Graphics.hpp>
#include <optional>

#include "AssetCache.hpp"
#include "MusicPlayer.hpp"

int main() {
  // Create the main window
  sf::RenderWindow window(sf::VideoMode({800, 600}), "SFML window");

  AssetCache<sf::Font> fonts("assets/", &sf::Font::openFromFile);
  MusicPlayer music("assets");

  sf::Font &font = fonts.get("fonts/Moogalator.ttf");

  sf::Text text(font, "Hello SFML", 50);

  music.play("music/ReturnOfThe8BitEra.mp3");

  // Start the game loop
  while (window.isOpen()) {
    // Process events
    while (const std::optional event = window.pollEvent()) {
      // Close window: exit
      if (event->is<sf::Event::Closed>())
        window.close();
    }

    // Clear screen
    window.clear();

    // Draw the sprite
    // window.draw(sprite);

    // Draw the string
    window.draw(text);

    // Update the window
    window.display();
  }
}
