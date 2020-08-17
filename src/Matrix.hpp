#pragma once

#include <mmintrin.h>

#include <array>
#include <cmath>

#include "Vector.hpp"

class Mat4x4f32 {
 private:
  std::array<float, 16> m = {0};

 public:
  Mat4x4f32() noexcept = default;
  Mat4x4f32(const std::array<float, 16>& arr) noexcept : m(arr) {}

  inline float& operator()(const size_t r, const size_t c) noexcept {
    return this->m[r * 4u + c];
  }
  inline const float& operator()(const size_t r,
                                 const size_t c) const noexcept {
    return this->m[r * 4u + c];
  }
};

inline Mat4x4f32 operator*(const Mat4x4f32& matA,
                           const Mat4x4f32& matB) noexcept {
  Mat4x4f32 result;

  for (size_t r = 0u; r < 4u; r++) {
    for (size_t c = 0u; c < 4u; c++) {
      const Vec4f32 vecA =
          Vec4f32(matA(r, 0), matA(r, 1), matA(r, 2), matA(r, 3));
      const Vec4f32 vecB =
          Vec4f32(matB(0, c), matB(1, c), matB(2, c), matB(3, c));

      result(r, c) = DotProduct(vecA, vecB);
    }
  }

  return result;
}

inline Mat4x4f32 MakeRotationX(const float radX = 0) noexcept {
  const float sinX = std::sin(radX);
  const float cosX = std::cos(radX);

  return Mat4x4f32{std::array<float, 16u>{1, 0, 0, 0, 0, cosX, -sinX, 0, 0,
                                          sinX, cosX, 0, 0, 0, 0, 1}};
}

inline Mat4x4f32 MakeRotationY(const float radY = 0) noexcept {
  const float sinY = std::sin(radY);
  const float cosY = std::cos(radY);

  return Mat4x4f32(std::array<float, 16u>{cosY, 0, sinY, 0, 0, 1, 0, 0, -sinY,
                                          0, cosY, 0, 0, 0, 0, 1});
}

inline Mat4x4f32 MakeRotationZ(const float radZ = 0) noexcept {
  const float sinZ = std::sin(radZ);
  const float cosZ = std::cos(radZ);

  return Mat4x4f32(std::array<float, 16u>{cosZ, -sinZ, 0, 0, sinZ, cosZ, 0, 0,
                                          0, 0, 1, 0, 0, 0, 0, 1});
}

inline Mat4x4f32 MakeRotation(const float radX = 0, const float radY = 0,
                              const float radZ = 0) noexcept {
  return MakeRotationX(radX) * MakeRotationY(radY) * MakeRotationZ(radZ);
}

inline Mat4x4f32 MakeRotation(const Vec3f32& v) noexcept {
  return MakeRotation(v.x, v.y, v.z);
}

inline auto operator*(const Vec4f32& v, const Mat4x4f32& mat) noexcept {
  return Vec4f32(
      DotProduct(v, Vec4f32(mat(0, 0), mat(1, 0), mat(2, 0), mat(3, 0))),
      DotProduct(v, Vec4f32(mat(0, 1), mat(1, 1), mat(2, 1), mat(3, 1))),
      DotProduct(v, Vec4f32(mat(0, 2), mat(1, 2), mat(2, 2), mat(3, 2))),
      DotProduct(v, Vec4f32(mat(0, 3), mat(1, 3), mat(2, 3), mat(3, 3))));
}