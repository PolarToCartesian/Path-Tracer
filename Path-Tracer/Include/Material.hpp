#pragma once

#include "Vector.hpp"

struct Material {
  Vec3f32 emittance;
  Vec3f32 diffuse;

  float reflectivity = 0.f;
};