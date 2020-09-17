#include "../Include/Image.hpp"

Image::Image(const std::uint32_t width, const std::uint32_t height) noexcept
    : m_width(width), m_height(height), m_nPixels(width * height) {
  this->m_pBuff = new ::PL::Point3<std::uint8_t>[this->m_nPixels];
  std::memset(this->m_pBuff, 0, this->m_nPixels * sizeof(::PL::Point3<std::uint8_t>));
}

Image::Image(const Image &img) noexcept
    : m_width(img.m_width), m_height(img.m_height), m_nPixels(m_width * m_height) {
  this->m_pBuff = new ::PL::Point3<std::uint8_t>[this->m_nPixels];
  std::memcpy(this->m_pBuff, img.m_pBuff, this->m_nPixels * sizeof(::PL::Point3<std::uint8_t>));
}

Image &Image::operator=(Image &&other) noexcept {
  this->m_width = other.m_width;
  this->m_height = other.m_height;
  this->m_nPixels = other.m_nPixels;
  this->m_pBuff = other.m_pBuff;

  other.m_pBuff = nullptr;

  return *this;
}

void Image::Save(const char *filename) const noexcept {
  // Open
  FILE *fp = std::fopen(filename, "wb");

  // Header
  std::fprintf(fp, "P6\n%d %d 255\n", this->m_width, this->m_height);

  // Write Contents
  std::fwrite(this->m_pBuff, this->m_nPixels * sizeof(::PL::Point3<std::uint8_t>), 1u, fp);

  // Close
  std::fclose(fp);
}