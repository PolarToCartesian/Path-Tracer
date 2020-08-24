#include "../Include/Camera.hpp"

Camera::Camera(const Vec3f32& position, const float fov) : position(position), fov(fov) {}

Ray Camera::GenerateRandomRay(const std::uint32_t x, const std::uint32_t y,
                              const std::uint32_t width, const std::uint32_t height) noexcept {
  Ray ray;

  const float aspectRatio = width / (float)height;
  const float fovTan = std::tan(fov / 2.f);

  ray.origin = this->position;

  ray.direction = Vec3f32((2 * (x / static_cast<float>(width)) - 1) * fovTan * aspectRatio,
                          (1 - 2 * (y / static_cast<float>(height))) * fovTan, 1.f);

  ray.direction.Normalize();

  return ray;
}