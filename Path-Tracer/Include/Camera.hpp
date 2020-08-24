#pragma once

#include <cmath>

#include "Ray.hpp"

struct Camera {
  Vec3f32 position{0.f, 0.f, 0.f};

  float fov = 3.1415926f * 0.75f;

  Camera() = delete;
  Camera(const Vec3f32& position, const float fov);

  Ray GenerateRandomRay(const std::uint32_t x, const std::uint32_t y, const std::uint32_t width,
                        const std::uint32_t height) noexcept;
};
