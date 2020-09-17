#pragma once

#include <Polar-Lib.hpp>
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
#include "Object.hpp"

class Renderer {
 public:
  static Camera camera;
  static std::vector<Object *> pObjects;

 private:
  static std::optional<Intersection> GetClosestIntersection(const ::PL::Ray4f32 &ray) noexcept;

 public:
  static void Draw(Image *pImage, const std::uint32_t nSamples) noexcept;

  static ::PL::Vec4f32 TraceRay(const ::PL::Ray4f32 &ray,
                                const std::uint32_t recursionDepth = 0u) noexcept;
};
