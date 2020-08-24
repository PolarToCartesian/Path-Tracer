#pragma once

#include "Ray.hpp"

struct Camera {
  Vec3f32 position;

  float fov;

  Camera() = delete;
  Camera(const Vec3f32& position, const float fov);

  Ray GenerateRandomRay(const std::uint32_t x, const std::uint32_t y, const std::uint32_t width,
                        const std::uint32_t height) noexcept;
};
