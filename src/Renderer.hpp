#pragma once

#include "Image.hpp"
#include "Object.hpp"
#include "Camera.hpp"

#include <vector>

class Renderer {
	static Camera camera;
	static std::vector<Object*> pObjects;

	static void Draw(Image const* pImage, const std::uint32_t nSamples) noexcept;

	static Vec3f32 TraceRay(const Ray& ray) noexcept;
};
