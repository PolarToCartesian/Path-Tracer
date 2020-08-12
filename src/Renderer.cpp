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
  }
}

Vec3f32 Renderer::TraceRay(const Ray& ray) noexcept {
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

  return closestIntersection.pObject->material.diffuseColor;
}