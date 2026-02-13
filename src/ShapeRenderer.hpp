#pragma once
#include <SFML/Graphics.hpp>

#include <memory>
#include <vector>

class ShapeRenderer {
public:
  template <typename ShapeT> ShapeT &add(ShapeT shape) {
    auto ptr = std::make_unique<ShapeT>(std::move(shape));
    ShapeT &ref = *ptr;
    m_shapes.emplace_back(std::move(ptr));
    return ref;
  }

  void draw(sf::RenderTarget &target) const {
    for (const auto &s : m_shapes)
      target.draw(*s);
  }

  void clear() { m_shapes.clear(); }

private:
  std::vector<std::unique_ptr<sf::Shape>> m_shapes;
};
