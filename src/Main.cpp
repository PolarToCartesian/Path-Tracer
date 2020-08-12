#include "Renderer.hpp"

#include <iostream>

int main(int argc, char* argv[]) {
  Image surface(500, 500);

  Renderer::camera = Camera{Vec3f32{0.f, 0.f, 0.f}};

  Material material;
  material.diffuseColor = Vec3f32{1.f, 1.f, 1.f};
  Renderer::pObjects.push_back(
      new Sphere(Vec3f32{0.f, 0.f, 5.f}, 1.f, material));

  Renderer::Draw(&surface, 10);

  surface.Save("frame.ppm");
}
