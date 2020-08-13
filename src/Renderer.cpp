#include "Renderer.hpp"

Camera Renderer::camera;
std::vector<Object*> Renderer::pObjects;

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
  if (recursionDepth == 10u)
    return {};

  // Get Closest Intersection
  Intersection closestIntersection;
  {
    closestIntersection.pObject = nullptr;

		for (const Object* object : Renderer::pObjects)
		{
			const std::optional<Intersection> intersection = object->Intersects(ray);

			if (intersection.has_value())
				if (closestIntersection.pObject == nullptr || intersection.value().distance < closestIntersection.distance)
					closestIntersection = intersection.value();
		}
  }

  if (closestIntersection.pObject == nullptr) return Vec3f32{ };

  // Extract Intersected Object
  const Object&   object   = *closestIntersection.pObject;
  const Material& material = object.material;

  Ray newRay;
  newRay.origin    = closestIntersection.location;

  const float u = std::rand()/(float)RAND_MAX;
  const float v = std::rand()/(float)RAND_MAX;

  auto sqrt_v = sqrt(v);

  newRay.direction = object.GetNormal(newRay.origin) * Normalized(Vec3f32(cos(2 * M_PI * u) * sqrt_v, sin(2 * M_PI * u) * sqrt_v,
                                                               sqrt(1 - v)));

  

  const Vec3f32 incomingColor = TraceRay(newRay, recursionDepth + 1u);

  Vec3f32 finalColor = material.diffuse * (material.emittance + incomingColor);
  finalColor.x = std::clamp(finalColor.x, 0.f, 1.f);
  finalColor.y = std::clamp(finalColor.y, 0.f, 1.f);
  finalColor.z = std::clamp(finalColor.z, 0.f, 1.f);

  return finalColor;
}