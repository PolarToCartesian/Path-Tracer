#pragma once

#include "../Include/Camera.hpp"

Ray Camera::GenerateRandomRay(const std::uint32_t x, const std::uint32_t y,
                              const std::uint32_t width, const std::uint32_t height) noexcept {
  Ray ray;

  const float aspectRatio = width / (float)height;

  ray.origin = this->position;

  ray.direction =
      Vec3f32{2 * (x + 1u) / (float)width - 1.f, 2 * (height - y + 1u) / (float)height - 1.f, 1.f};

  ray.direction.Normalize();

  return ray;
}