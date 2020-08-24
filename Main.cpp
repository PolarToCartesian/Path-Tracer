#include <iostream>

#include "Path-Tracer/Include/Renderer.hpp"

int main(int argc, char* argv[]) {
  Image surface(1000, 1000);

  Renderer::camera = Camera{Vec3f32{0.f, 0.f, 0.f}, M_PI * 0.75f};

  Material mat1;
  mat1.diffuse = Vec3f32{1.f, 1.f, 1.f};
  mat1.reflectivity = 0.5f;
  Renderer::pObjects.push_back(
      new Sphere(Vec3f32{-1.25f, 0.f, 1.5f}, 1.f, mat1));
  mat1.diffuse = Vec3f32{1.f, 0.f, 0.f};
  Renderer::pObjects.push_back(
      new Sphere(Vec3f32{1.25f, 0.f, 1.5f}, 1.f, mat1));
  Material mat2;
    mat2.diffuse = Vec3f32{1.f, 1.f, 1.f};
  mat2.emittance = {1.f, 1.f, 1.f};
  mat2.reflectivity = 0.f;
  Renderer::pObjects.push_back(
      new Sphere(Vec3f32{0.f, 0.f, -2.f}, 1.f, mat2));
//  Renderer::pObjects.push_back(
//      new Sphere(Vec3f32{-3.f, 0.f, -2.f}, 1.f, mat2));
//Renderer::pObjects.push_back(
//      new Sphere(Vec3f32{3.f, 0.f, -2.f}, 1.f, mat2));

  Renderer::Draw(&surface, 1000);

  surface.Save("frame.ppm");
}
