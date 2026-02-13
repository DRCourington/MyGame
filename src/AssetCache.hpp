#pragma once
#include <filesystem>
#include <memory>
#include <stdexcept>
#include <string>
#include <string_view>
#include <unordered_map>
#include <utility>

template <typename T> class AssetCache {
public:
  using LoaderFn = bool (T::*)(const std::filesystem::path &);

  AssetCache(std::filesystem::path basePath, LoaderFn loader)
      : m_basePath(std::move(basePath)), m_loader(loader) {}

  T &get(const std::filesystem::path &relativePath) {
    const auto key = normalizeKey(relativePath);

    if (auto it = m_assets.find(key); it != m_assets.end())
      return *it->second;

    auto obj = std::make_unique<T>();
    const std::filesystem::path fullPath = m_basePath / relativePath;

    if (!((*obj).*m_loader)(fullPath)) {
      throw std::runtime_error(
          "AssetCache: failed to load '" + relativePath.string() + "' -> '" +
          fullPath.string() +
          "' (cwd=" + std::filesystem::current_path().string() + ")");
    }

    T &ref = *obj;
    m_assets.emplace(key, std::move(obj));
    return ref;
  }

  T &get(std::string_view relativePath) {
    return get(std::filesystem::path(relativePath));
  }

  T &get(const char *relativePath) {
    return get(std::filesystem::path(relativePath));
  }

  bool contains(const std::filesystem::path &relativePath) const {
    return m_assets.find(normalizeKey(relativePath)) != m_assets.end();
  }

  void clear() { m_assets.clear(); }

private:
  static std::string normalizeKey(const std::filesystem::path &p) {
    return p.lexically_normal().generic_string();
  }

  std::filesystem::path m_basePath;
  LoaderFn m_loader;
  std::unordered_map<std::string, std::unique_ptr<T>> m_assets;
};
