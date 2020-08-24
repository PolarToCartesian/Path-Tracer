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

Plane::Plane(const Vec3f32 &position, const Vec3f32 &normal, const Material &material) noexcept
    : Object(position, material), normal(normal) {}

Vec3f32 Plane::GetNormal(const Vec3f32 &point) const noexcept { return normal; }

std::optional<Intersection> Plane::Intersects(const Ray &ray) const noexcept {
  // thanks
  // https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-plane-and-ray-disk-intersection

  const float denom = DotProduct(this->normal, ray.direction);
  if (std::abs(denom) >= 1e-6) {
    const Vec3f32 v = this->position - ray.origin;
    const float t = DotProduct(v, normal) / denom;

    if (t >= 0) return Intersection{t, ray.origin + ray.direction * t, (Object *)this};
  }

  return {};
}