#include "../Include/Camera.hpp"

Camera::Camera(const ::PL::Vec4f32& position, const float fov) : position(position), fov(fov) {}

::PL::Ray4f32 Camera::GenerateRandomRay(const std::uint32_t x, const std::uint32_t y,
                                        const std::uint32_t width,
                                        const std::uint32_t height) noexcept {
  ::PL::Ray4f32 ray;

  const float apsectRatio = width / (float)height;
  const float halffovTan = std::tan(this->fov / 2.f);

  ray.origin = this->position;

  ray.direction.x = halffovTan * (2 * (x + 1u) / (float)width - 1.f) * apsectRatio;
  ray.direction.y = halffovTan * (2 * (height - y + 1u) / (float)height - 1.f);
  ray.direction.z = 1.f;

  ray.direction.Normalize();

  return ray;
}