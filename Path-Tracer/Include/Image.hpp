#pragma once

#include <Polar-Lib.hpp>
#include <cstdio>
#include <cstring>

class Image {
 private:
  std::uint32_t m_width = 0, m_height = 0;
  std::uint64_t m_nPixels = 0;

  ::PL::Point3<std::uint8_t> *m_pBuff = nullptr;

 public:
  Image() = default;
  Image(const std::uint32_t width, const std::uint32_t height) noexcept;

  Image(const Image &img) noexcept;

  inline ~Image() { delete[] this->m_pBuff; }

  Image &operator=(Image &&other) noexcept;

  inline ::PL::Point3<std::uint8_t> &operator()(const std::uint32_t x,
                                                const std::uint32_t y) noexcept {
    return this->m_pBuff[y * this->m_width + x];
  }

  inline const ::PL::Point3<std::uint8_t> &operator()(const std::uint32_t x,
                                                      const std::uint32_t y) const noexcept {
    return this->m_pBuff[y * this->m_width + x];
  }

  inline ::PL::Point3<std::uint8_t> *Get() const noexcept { return this->m_pBuff; }
  inline std::uint32_t GetWidth() const noexcept { return this->m_width; }
  inline std::uint32_t GetHeight() const noexcept { return this->m_height; }

  void Save(const char *filename) const noexcept;
};