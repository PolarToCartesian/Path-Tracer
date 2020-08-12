#pragma once

#include "Vector.hpp"

struct Camera {
	Vec3f32 position;
	
	Ray GenerateRandomRay(const std::uint32_t x, const std::uint32_t y, const std::uint32_t width, const std::uint32_t height) noexcept {
		Ray ray;	
		
		const float aspectRatio = width/(float)height;
		
		ray.origin = this->position;

		ray.direction = Normalized(Vec3f32{
			2*(x + 1u) / (float)width - 1.f,
			2*(height - y + 1u) / (float)height - 1.f,
			1.f
		} - this->position);

		return ray;
	}
};
