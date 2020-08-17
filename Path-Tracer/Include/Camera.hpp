#pragma once

#include "Ray.hpp"

struct Camera {
  Vec3f32 position;

  Ray GenerateRandomRay(const std::uint32_t x, const std::uint32_t y, const std::uint32_t width,
                        const std::uint32_t height) noexcept;
};
