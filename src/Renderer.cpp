#include "Renderer.hpp"

Camera Renderer::camera;
std::vector<Object*> Renderer::pObjects;

#include <cstdint>

void Renderer::Draw(Image* pImage, const std::uint32_t nSamples) noexcept {
	Image& surface = *pImage;

	for (std::uint32_t y = 0u; y < surface.GetHeight(); y++) {
	for (std::uint32_t x = 0u; x < surface.GetWidth();  x++) {
		Vec3f32 pixelColor;		

		for (std::uint32_t i = 0u; i < nSamples; i++) {
			const Ray& cameraRay = Renderer::camera.GenerateRandomRay(x, y, surface.GetWidth(), surface.GetHeight());					
			pixelColor += Vec3f32{};
		}

		pixelColor /= nSamples;

		surface(x, y) = Vec3u8{static_cast<std::uint8_t>(pixelColor.x),
							   static_cast<std::uint8_t>(pixelColor.y),
							   static_cast<std::uint8_t>(pixelColor.z)};
	}
	}
}

Vec3f32 Renderer::TraceRay(const Ray& ray) noexcept {
	return {};
}