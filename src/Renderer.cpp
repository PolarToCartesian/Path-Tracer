#include "Renderer.hpp"

Camera Renderer::camera;
std::vector<Object*> Renderer::pObjects;

std::optional<Intersection> Renderer::GetClosestIntersection(
    const Ray& ray) noexcept {
  std::optional<Intersection> closest;
  for (Object* pObject : Renderer::pObjects) {
    const std::optional<Intersection> current = pObject->Intersects(ray);

    if (current.has_value())
      if (!closest.has_value() ||
          current.value().distance < closest.value().distance)
        closest = current;
  }

  return closest;
}

#include <iostream>

void Renderer::Draw(Image* pImage, const std::uint32_t nSamples) noexcept {
  Image& surface = *pImage;

  constexpr size_t THREAD_COUNT = 1u;

  std::array<std::thread, THREAD_COUNT> threads;

  auto DrawScanlines = [&surface, nSamples](const size_t yStart,
                                                    const size_t yEnd) {
    for (std::uint32_t y = yStart; y < yEnd; y++) {
      for (std::uint32_t x = 0u; x < surface.GetWidth(); x++) {
        Vec3f32 pixelColor;

        for (std::uint32_t i = 0u; i < nSamples; i++) {
          const Ray& cameraRay = Renderer::camera.GenerateRandomRay(
              x, y, surface.GetWidth(), surface.GetHeight());
          pixelColor += TraceRay(cameraRay);
        }

        pixelColor /= nSamples;

        surface(x, y) = Vec3u8{static_cast<std::uint8_t>(pixelColor.x * 255u),
                               static_cast<std::uint8_t>(pixelColor.y * 255u),
                               static_cast<std::uint8_t>(pixelColor.z * 255u)};
      }
    }
  };

  size_t scanlinesLeft = surface.GetHeight();
  const size_t scanlinesPerThread = scanlinesLeft / THREAD_COUNT;
  for (size_t threadIndex = 0u; threadIndex < THREAD_COUNT; threadIndex++) {
    if (threadIndex != THREAD_COUNT - 1u) {
      threads[threadIndex] = std::thread(
          DrawScanlines, scanlinesLeft - scanlinesPerThread, scanlinesLeft);
      scanlinesLeft -= scanlinesPerThread;
    } else {
      threads[threadIndex] = std::thread(DrawScanlines, 0, scanlinesLeft);
    }
  }

  for (auto& thread : threads) thread.join();

  std::putc('\n', stdout);
}

Vec3f32 Renderer::TraceRay(const Ray& ray,
                           const std::uint32_t recursionDepth) noexcept {
  Intersection closestIntersection;
  {
    const auto closestIntersectionOptional =
        Renderer::GetClosestIntersection(ray);
    if (!closestIntersectionOptional.has_value() || recursionDepth == 10u)
      return Vec3f32{};

    closestIntersection = closestIntersectionOptional.value();
  }

  // Extract Intersected Object
  const Object& object = *closestIntersection.pObject;
  const Material& material = object.material;

  const float rng = std::rand()/(float)RAND_MAX;

  Ray newRay;
  newRay.origin =
      closestIntersection.location + object.GetNormal(newRay.origin) * 0.01f;

  const float alpha0 = 2 * M_PI * std::rand() / (float)RAND_MAX;
  const float alpha1 = std::acos(1 - 2 * std::rand() / (float)RAND_MAX);

  const Vec3f32 v{std::sin(alpha0) * std::cos(alpha1),
                  std::cos(alpha0) * std::sin(alpha1), std::cos(alpha1)};

  newRay.direction = object.GetNormal(newRay.origin);

  const Vec3f32 incomingColor = TraceRay(newRay, recursionDepth + 1u);

  const float dotProduct = std::min(
      std::max(DotProduct(newRay.direction, object.GetNormal(newRay.origin)),
               0.f),
      1.f);
  Vec3f32 finalColor =
      material.diffuse * (material.emittance + incomingColor * dotProduct);
  finalColor.Clamp(0.f, 1.f);

  return finalColor;
}