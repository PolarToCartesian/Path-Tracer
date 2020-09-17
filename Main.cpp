#include <iostream>

#include "Path-Tracer/Include/Renderer.hpp"

int main(int argc, char* argv[]) {
  Image surface(500, 500);

  PL::LOG::Println(PL::LOG_TYPE::LOG_SUCCESS, "Start..");

  std::cin.get();

  Renderer::camera = Camera{::PL::Vec4f32{0.f, 0.f, 0.f}, 3.141592f * 0.75f};

  Material mat1;
  mat1.diffuse = ::PL::Vec4f32{1.f, 1.f, 1.f};
  mat1.reflectivity = 0.5f;
  Renderer::pObjects.push_back(
      new Sphere(::PL::Vec4f32{-1.25f, 0.f, 1.5f}, 1.f, mat1));
  mat1.diffuse = ::PL::Vec4f32{1.f, 0.f, 0.f};
  Renderer::pObjects.push_back(
      new Sphere(::PL::Vec4f32{1.25f, 0.f, 1.5f}, 1.f, mat1));
  Material mat2;
    mat2.diffuse = ::PL::Vec4f32{1.f, 1.f, 1.f};
  mat2.emittance = {1.f, 1.f, 1.f};
  mat2.reflectivity = 0.f;
  Renderer::pObjects.push_back(
      new Sphere(::PL::Vec4f32{0.f, 0.f, -2.f}, 1.f, mat2));
//  Renderer::pObjects.push_back(
//      new Sphere(Vec3f32{-3.f, 0.f, -2.f}, 1.f, mat2));
//Renderer::pObjects.push_back(
//      new Sphere(Vec3f32{3.f, 0.f, -2.f}, 1.f, mat2));

  Renderer::Draw(&surface, 100);

  surface.Save("frame.ppm");
}
