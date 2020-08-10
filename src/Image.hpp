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
  Image(const std::uint32_t width, const std::uint32_t height) noexcept
      : m_width(width), m_height(height), m_nPixels(width * height) {
    this->m_pBuff = new Vec3u8[this->m_nPixels];
    std::memset(this->m_pBuff, 0, this->m_nPixels * sizeof(Vec3u8));
  }

  Image(const Image &img) noexcept
      : m_width(img.m_width),
        m_height(img.m_height),
        m_nPixels(m_width * m_height) {
    this->m_pBuff = new Vec3u8[this->m_nPixels];
    std::memcpy(this->m_pBuff, img.m_pBuff, this->m_nPixels * sizeof(Vec3u8));
  }

  ~Image() { delete[] this->m_pBuff; }

  Image &operator=(Image &&other) noexcept {
    this->m_width = other.m_width;
    this->m_height = other.m_height;
    this->m_nPixels = other.m_nPixels;
    this->m_pBuff = other.m_pBuff;

    other.m_pBuff = nullptr;

    return *this;
  }

  inline Vec3u8 &operator()(const std::uint32_t x,
                            const std::uint32_t y) noexcept {
    return this->m_pBuff[y * this->m_width + x];
  }

  inline const Vec3u8 &operator()(const std::uint32_t x,
                                  const std::uint32_t y) const noexcept {
    return this->m_pBuff[y * this->m_width + x];
  }

  inline Vec3u8 *Get() const noexcept { return this->m_pBuff; }
  inline std::uint32_t GetWidth() const noexcept { return this->m_width; }
  inline std::uint32_t GetHeight() const noexcept { return this->m_height; }

  void Save(const char *filename) const noexcept {
    // Open
    FILE *fp = std::fopen(filename, "wb");

    // Header
    std::fprintf(fp, "P6\n%d %d 255\n", this->m_width, this->m_height);

    // Write Contents
    std::fwrite(this->m_pBuff, this->m_nPixels * sizeof(Vec3u8), 1u, fp);

    // Close
    std::fclose(fp);
  }
};