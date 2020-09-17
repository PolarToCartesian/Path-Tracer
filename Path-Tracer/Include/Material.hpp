#pragma once

#include <Polar-Lib.hpp>

struct Material {
  ::PL::Vec4f32 emittance;
  ::PL::Vec4f32 diffuse;

  float reflectivity = 0.f;
};