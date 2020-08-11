#include "Renderer.hpp"

int main(int argc, char* argv[]) {
	Image surface(1920, 1080);
	
	Renderer::camera = Camera{Vec3f32{0.f,0.f,0.f}};
	
	Material material;
	Renderer::pObjects.push_back(new Sphere(Vec3f32{0.f,0.f,5.f}, 1.f, material));
	Renderer::Draw(&surface);

	surface.Save("frame.ppm");
}
