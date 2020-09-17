#pragma once

#include <Polar-Lib.hpp>
#include <optional>

#include "Intersection.hpp"
#include "Material.hpp"

struct Object {
  ::PL::Vec4f32 position;
  Material material;

  Object(const ::PL::Vec4f32 &position, const Material &material) noexcept;

  virtual ::PL::Vec4f32 GetNormal(const ::PL::Vec4f32 &point) const noexcept = 0;
  virtual std::optional<Intersection> Intersects(const ::PL::Ray4f32 &in) const noexcept = 0;

  virtual ~Object();
};

struct Sphere : Object {
  float radius;

  Sphere(const ::PL::Vec4f32 &position, const float radius, const Material &material) noexcept;

  virtual ::PL::Vec4f32 GetNormal(const ::PL::Vec4f32 &point) const noexcept override;

  virtual std::optional<Intersection> Intersects(const ::PL::Ray4f32 &ray) const noexcept override;
};

struct Plane : Object {
  ::PL::Vec4f32 normal;

  Plane(const ::PL::Vec4f32 &position, const ::PL::Vec4f32 &normal,
        const Material &material) noexcept;

  virtual ::PL::Vec4f32 GetNormal(const ::PL::Vec4f32 &point) const noexcept override;

  virtual std::optional<Intersection> Intersects(const ::PL::Ray4f32 &ray) const noexcept override;
};
