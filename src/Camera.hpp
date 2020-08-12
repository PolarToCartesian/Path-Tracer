#pragma once

#include "Ray.hpp"

struct Camera {
  Vec3f32 position;

  Ray GenerateRandomRay(const std::uint32_t x, const std::uint32_t y,
                        const std::uint32_t width,
                        const std::uint32_t height) noexcept {
    Ray ray;

    const float aspectRatio = width / (float)height;

    ray.origin = this->position;

    ray.direction = Vec3f32{(2 * (x + 1u) + std::rand()/(float)RAND_MAX - 0.5f) / (float)width - 1.f,
                            (2 * (height - y + 1u) + std::rand()/(float)RAND_MAX - 0.5f) / (float)height - 1.f,
                            1.f};

    ray.direction -= this->position;
    ray.direction.Normalize();

    return ray;
  }
};
