#pragma once

struct Object;

struct Intersection {
  float distance;
  Vec3f32 location;
  Object* pObject;
};
