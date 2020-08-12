#pragma once

#include <optional>
#include <limits>
#include <vector>
#include <cstdint>
#include <algorithm>

#include "Camera.hpp"
#include "Image.hpp"
#include "Object.hpp"
#include "Ray.hpp"

class Renderer {
 public:
  static Camera camera;
  static std::vector<Object*> pObjects;

  static void Draw(Image* pImage, const std::uint32_t nSamples) noexcept;

  static Vec3f32 TraceRay(const Ray& ray, const std::uint32_t recursionDepth = 0u) noexcept;
};
