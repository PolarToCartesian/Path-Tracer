#pragma once

#include "Intersection.hpp"
#include "Material.hpp"

#include <optional>

struct Object {
	Vec3f position;
	Material material;
	
	virtual std::optional<Intersection> Intersects(const Ray& in) noexcept = 0;

	virtual ~Object() {  }
};

struct Sphere : Object {
	float radius;

	virtual std::optional<Intersection> Intersects(const Ray& ray) noexcept override {
		Vecf32 L = this->position - ray.origin; 

        	float tca = Vector<>::DotProduct(L, ray.direction); 
        	float d2 = Vector<>::DotProduct(L, L) - tca * tca; 

        	if (d2 > this->radius)
			return {};
        
		float thc = sqrt(this->radius - d2); 
        	float t0 = tca - thc; 
        	float t1 = tca + thc; 

		if (t0 > t1) std::swap(t0, t1); 
 
        	if (t0 < 0) { 
            		t0 = t1;
            	
			if (t0 < 0) return { };
        	} 
 
        	float t = t0; 
 
		return Intersect{t, ray.origin + ray.direction*t, (Object*)this};		
	}
};
