#include "Renderer.hpp"

Camera Renderer::camera;
std::vector<Object*> Renderer::pObjects;

std::optional<Intersection> Renderer::GetClosestIntersection(const Ray& ray) noexcept
{
  std::optional<Intersection> closest;
  for (Object* pObject : Renderer::pObjects) {
    const std::optional<Intersection> current = pObject->Intersects(ray);

    if (current.has_value())
      if (!closest.has_value() || current.value().distance < closest.value().distance)
        closest = current;
  }

  return closest;
}

void Renderer::Draw(Image* pImage, const std::uint32_t nSamples) noexcept {
  Image& surface = *pImage;

  for (std::uint32_t y = 0u; y < surface.GetHeight(); y++) {
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

    // Update Progress Bar
    PrintProgressBar((y + 1u) / (float)surface.GetHeight());
  }

  std::putc('\n', stdout);
}

Vec3f32 Renderer::TraceRay(const Ray& ray, const std::uint32_t recursionDepth) noexcept {
  Intersection closestIntersection;
  {
    const auto closestIntersectionOptional = Renderer::GetClosestIntersection(ray);
    if (!closestIntersectionOptional.has_value() || recursionDepth == 10u) return Vec3f32{ };

    closestIntersection = closestIntersectionOptional.value();
  }

  // Extract Intersected Object
  const Object&   object   = *closestIntersection.pObject;
  const Material& material = object.material;

  Ray newRay;
  newRay.origin = closestIntersection.location;
  newRay.direction = object.GetNormal(newRay.origin);

  const Vec3f32 incomingColor = TraceRay(newRay, recursionDepth + 1u);

  Vec3f32 finalColor = material.emittance + incomingColor;
  finalColor.x = std::clamp(finalColor.x, 0.f, 1.f);
  finalColor.y = std::clamp(finalColor.y, 0.f, 1.f);
  finalColor.z = std::clamp(finalColor.z, 0.f, 1.f);

  return finalColor;
}