#pragma once

#include <Polar-Lib.hpp>

struct Object;

struct Intersection {
  float distance;
  ::PL::Vec4f32 location;
  Object *pObject;
};
