#include "../Include/Object.hpp"

Object::Object(const Vec3f32 &position, const Material &material) noexcept
    : position(position), material(material) {}

Object::~Object() {}

Sphere::Sphere(const Vec3f32 &position, const float radius, const Material &material) noexcept
    : Object(position, material), radius(radius) {}

Vec3f32 Sphere::GetNormal(const Vec3f32 &point) const noexcept {
  return Normalized(point - this->position);
}

std::optional<Intersection> Sphere::Intersects(const Ray &ray) const noexcept {
  Vec3f32 L = this->position - ray.origin;

  float tca = DotProduct(L, ray.direction);
  float d2 = DotProduct(L, L) - tca * tca;

  if (d2 > this->radius) return {};

  float thc = sqrt(this->radius - d2);
  float t0 = tca - thc;
  float t1 = tca + thc;

  if (t0 > t1) std::swap(t0, t1);

  if (t0 < 0.01f) {
    t0 = t1;

    if (t0 < 0) return {};
  }

  float t = t0;

  return Intersection{t, ray.origin + ray.direction * t, (Object *)this};
}