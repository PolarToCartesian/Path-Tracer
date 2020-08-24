#include "../Include/Renderer.hpp"

Camera Renderer::camera({}, M_PI / 2.f);
std::vector<Object *> Renderer::pObjects;

std::optional<Intersection> Renderer::GetClosestIntersection(const Ray &ray) noexcept {
  std::optional<Intersection> closest;
  for (Object *pObject : Renderer::pObjects) {
    const std::optional<Intersection> current = pObject->Intersects(ray);

    if (current.has_value())
      if (!closest.has_value() || current.value().distance < closest.value().distance)
        closest = current;
  }

  return closest;
}

void Renderer::Draw(Image *pImage, const std::uint32_t nSamples) noexcept {
  Image &surface = *pImage;

  constexpr size_t THREAD_COUNT = 10;

  std::array<std::thread, THREAD_COUNT> threads;

  auto DrawScanlines = [&surface, nSamples](const size_t yStart, const size_t yEnd) {
    for (std::uint32_t y = yStart; y < yEnd; y++) {
      for (std::uint32_t x = 0u; x < surface.GetWidth(); x++) {
        Vec3f32 pixelColor;

        for (std::uint32_t i = 0u; i < nSamples; i++) {
          pixelColor += TraceRay(
              Renderer::camera.GenerateRandomRay(x, y, surface.GetWidth(), surface.GetHeight()));
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
      threads[threadIndex] =
          std::thread(DrawScanlines, scanlinesLeft - scanlinesPerThread, scanlinesLeft);
      scanlinesLeft -= scanlinesPerThread;
    } else {
      threads[threadIndex] = std::thread(DrawScanlines, 0, scanlinesLeft);
    }
  }

  for (auto &thread : threads) thread.join();

  std::putc('\n', stdout);
}

Vec3f32 Renderer::TraceRay(const Ray &ray, const std::uint32_t recursionDepth) noexcept {
  constexpr static float PROBABILITY_OF_NEW_RAY = 1.f / (2 * 3.141592f);

  Intersection closestIntersection;
  {
    const auto closestIntersectionOptional = Renderer::GetClosestIntersection(ray);
    if (!closestIntersectionOptional.has_value() || recursionDepth == 10u) return Vec3f32{};

    closestIntersection = closestIntersectionOptional.value();
  }

  // Extract Intersected Object
  const Object &object = *closestIntersection.pObject;
  const Material &material = object.material;

  const Vec3f32 surfaceNormal = object.GetNormal(closestIntersection.location);

  Vec3f32 finalColor;
  if (std::rand() / (float)RAND_MAX < material.reflectivity) {
    Ray newRay;
    newRay.origin = closestIntersection.location + surfaceNormal * 0.1f;
    newRay.direction = Reflected(ray.direction, surfaceNormal);

    const Vec3f32 reflectedColor = TraceRay(newRay, recursionDepth + 1u);
    finalColor = reflectedColor + material.emittance;
  } else {
    Ray newRay;
    newRay.origin = closestIntersection.location + surfaceNormal * 0.1f;

    const Vec3f32 angle((3.141592f / 4.f) * (2.f * (std::rand() / (float)RAND_MAX) - 1.f),
                        (3.141592f / 4.f) * (2.f * (std::rand() / (float)RAND_MAX) - 1.f),
                        (3.141592f / 4.f) * (2.f * (std::rand() / (float)RAND_MAX) - 1.f));

    newRay.direction =
        Vec3f32(surfaceNormal.x, surfaceNormal.y, surfaceNormal.z, 1.f) * MakeRotation(angle);

    const Vec3f32 incomingColor = TraceRay(newRay, recursionDepth + 1u);

    const float dotProduct = std::clamp(DotProduct(newRay.direction, surfaceNormal), 0.f, 1.f);

    finalColor = material.diffuse *
                 (material.emittance + (incomingColor * dotProduct / PROBABILITY_OF_NEW_RAY));
  }

  finalColor.Clamp(0.f, 1.f);

  return finalColor;
}