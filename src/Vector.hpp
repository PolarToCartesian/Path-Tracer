#pragma once

#include <x86intrin.h>

#include <cmath>
#include <cstdint>

struct Vec4f32;

inline float DotProduct(const Vec4f32 &a, const Vec4f32 &b) noexcept;

struct Vec4f32 {
  union {
    __m128 m_reg;
    struct {
      float x, y, z, w;
    };
  };

  inline Vec4f32(const __m128 &reg) noexcept { this->m_reg = reg; }

  inline Vec4f32(const float x = 0.f, const float y = 0.f, const float z = 0.f,
                 const float w = 0.f) noexcept {
    this->m_reg = _mm_set_ps(w, z, y, x);
  }

  inline float Length() const noexcept {
    return std::sqrt(DotProduct(this->m_reg, this->m_reg));
  }

  inline void Normalize() noexcept { this->operator/=(this->Length()); }

  inline void Clamp(const float min, const float max) noexcept {
    this->x = std::clamp(this->x, 0.f, 1.f);
    this->y = std::clamp(this->y, 0.f, 1.f);
    this->z = std::clamp(this->z, 0.f, 1.f);
    this->w = std::clamp(this->w, 0.f, 1.f);
  }

  inline void operator+=(const Vec4f32 &other) noexcept {
    this->m_reg = _mm_add_ps(this->m_reg, other.m_reg);
  }
  inline void operator-=(const Vec4f32 &other) noexcept {
    this->m_reg = _mm_sub_ps(this->m_reg, other.m_reg);
  }
  inline void operator*=(const Vec4f32 &other) noexcept {
    this->m_reg = _mm_mul_ps(this->m_reg, other.m_reg);
  }
  inline void operator/=(const Vec4f32 &other) noexcept {
    this->m_reg = _mm_div_ps(this->m_reg, other.m_reg);
  }

  inline void operator*=(const float &n) noexcept {
    this->m_reg = _mm_mul_ps(this->m_reg, _mm_set1_ps(n));
  }

  inline void operator/=(const float &n) noexcept {
    this->m_reg = _mm_div_ps(this->m_reg, _mm_set1_ps(n));
  }
};

inline Vec4f32 operator+(const Vec4f32 &a, const Vec4f32 &b) noexcept {
  return Vec4f32(_mm_add_ps(a.m_reg, b.m_reg));
}

inline Vec4f32 operator-(const Vec4f32 &a, const Vec4f32 &b) noexcept {
  return Vec4f32(_mm_sub_ps(a.m_reg, b.m_reg));
}

inline Vec4f32 operator*(const Vec4f32 &a, const Vec4f32 &b) noexcept {
  return Vec4f32(_mm_mul_ps(a.m_reg, b.m_reg));
}

inline Vec4f32 operator/(const Vec4f32 &a, const Vec4f32 &b) noexcept {
  return Vec4f32(_mm_div_ps(a.m_reg, b.m_reg));
}

inline Vec4f32 operator*(const Vec4f32 &v, const float &n) noexcept {
  return _mm_mul_ps(v.m_reg, _mm_set1_ps(n));
}

inline Vec4f32 operator/(const Vec4f32 &v, const float &n) noexcept {
  return _mm_div_ps(v.m_reg, _mm_set1_ps(n));
}

inline Vec4f32 operator*(const float &n, const Vec4f32 &v) noexcept {
  return operator*(v, n);
}

inline Vec4f32 operator/(const float &n, const Vec4f32 &v) noexcept {
  return operator/(v, n);
}

inline float DotProduct(const Vec4f32 &a, const Vec4f32 &b) noexcept {
  // __m128 product = (a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w)
  const __m128 product  = _mm_mul_ps(a.m_reg, b.m_reg);

  const __m128 tmp_hadd1 = _mm_hadd_ps(product,   product);
  const __m128 tmp_hadd2 = _mm_hadd_ps(tmp_hadd1, tmp_hadd1);

  // return (tmp_hadd2.x)
  return _mm_cvtss_f32(tmp_hadd2);
}

inline Vec4f32 Reflected(const Vec4f32 &in, const Vec4f32 &normal) noexcept {
  return in - 2 * DotProduct(in, normal) * normal;
}

inline Vec4f32 Normalized(const Vec4f32 &v) noexcept { return v / v.Length(); }

struct Vec3u8 {
  std::uint8_t r, g, b;
};

struct Vec4u8 : Vec3u8 {
  std::uint8_t a;
};

typedef Vec4f32 Vec3f32;