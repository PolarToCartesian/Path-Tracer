#include "Renderer.hpp"

#include <iostream>

int main(int argc, char* argv[]) {
  Image surface(100, 100);

  Renderer::camera = Camera{Vec3f32{0.f, 0.f, 0.f}};

  Material material;
  material.diffuse = Vec3f32{1.f, 1.f, 1.f};
  Renderer::pObjects.push_back(
      new Sphere(Vec3f32{0.f, 0.f, 1.5f}, 1.f, material));
  material.emittance = {1.f,1.f,1.f};
  Renderer::pObjects.push_back(
      new Sphere(Vec3f32{0.f, 0.f, -1.25f}, 1.f, material));

  Renderer::Draw(&surface, 100);

  surface.Save("frame.ppm");
}
