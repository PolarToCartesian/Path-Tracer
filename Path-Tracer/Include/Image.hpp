#pragma once

#include <cstdio>
#include <cstring>

#include "Vector.hpp"

class Image {
 private:
  std::uint32_t m_width = 0, m_height = 0;
  std::uint64_t m_nPixels = 0;

  Vec3u8 *m_pBuff = nullptr;

 public:
  Image() = default;
  Image(const std::uint32_t width, const std::uint32_t height) noexcept;

  Image(const Image &img) noexcept;

  inline ~Image() { delete[] this->m_pBuff; }

  Image &operator=(Image &&other) noexcept;

  inline Vec3u8 &operator()(const std::uint32_t x, const std::uint32_t y) noexcept {
    return this->m_pBuff[y * this->m_width + x];
  }

  inline const Vec3u8 &operator()(const std::uint32_t x, const std::uint32_t y) const noexcept {
    return this->m_pBuff[y * this->m_width + x];
  }

  inline Vec3u8 *Get() const noexcept { return this->m_pBuff; }
  inline std::uint32_t GetWidth() const noexcept { return this->m_width; }
  inline std::uint32_t GetHeight() const noexcept { return this->m_height; }

  void Save(const char *filename) const noexcept;
};