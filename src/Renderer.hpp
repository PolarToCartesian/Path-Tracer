#pragma once

#include <optional>
#include <limits>
#include <vector>
#include <cstdint>
#include <algorithm>
#include <chrono>
#include <random>
#include <future>

#include "Camera.hpp"
#include "Image.hpp"
#include "Object.hpp"
#include "Ray.hpp"
#include "ProgressBar.hpp"

class Renderer {
 public:
  static Camera camera;
  static std::vector<Object*> pObjects;

private:
  static std::optional<Intersection> GetClosestIntersection(const Ray& ray) noexcept;

public:
  static void Draw(Image* pImage, const std::uint32_t nSamples) noexcept;

  static Vec3f32 TraceRay(const Ray& ray, const std::uint32_t recursionDepth = 0u) noexcept;
};
