#pragma once

#include <optional>

#include "Intersection.hpp"
#include "Material.hpp"
#include "Ray.hpp"

struct Object {
  Vec3f32 position;
  Material material;

  Object(const Vec3f32 &position, const Material &material) noexcept;

  virtual Vec3f32 GetNormal(const Vec3f32 &point) const noexcept = 0;
  virtual std::optional<Intersection> Intersects(const Ray &in) const noexcept = 0;

  virtual ~Object();
};

struct Sphere : Object {
  float radius;

  Sphere(const Vec3f32 &position, const float radius, const Material &material) noexcept;

  virtual Vec3f32 GetNormal(const Vec3f32 &point) const noexcept override;

  virtual std::optional<Intersection> Intersects(const Ray &ray) const noexcept override;
};
