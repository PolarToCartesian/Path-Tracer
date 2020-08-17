#pragma once

#include <algorithm>
#include <chrono>
#include <cstdint>
#include <future>
#include <limits>
#include <optional>
#include <random>
#include <vector>

#include "Camera.hpp"
#include "Image.hpp"
#include "Matrix.hpp"
#include "Object.hpp"
#include "ProgressBar.hpp"
#include "Ray.hpp"

class Renderer {
 public:
  static Camera camera;
  static std::vector<Object*> pObjects;

 private:
  static std::optional<Intersection> GetClosestIntersection(
      const Ray& ray) noexcept;

 public:
  static void Draw(Image* pImage, const std::uint32_t nSamples) noexcept;

  static Vec3f32 TraceRay(const Ray& ray,
                          const std::uint32_t recursionDepth = 0u) noexcept;
};
