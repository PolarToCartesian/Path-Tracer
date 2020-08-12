#pragma once

#include "Intersection.hpp"
#include "Material.hpp"

#include <optional>

struct Object {
	Vec3f32 position;
	Material material;
	
	Object(const Vec3f32& position, const Material& material) noexcept
		: position(position), material(material)
	{ }

	virtual std::optional<Intersection> Intersects(const Ray& in) noexcept = 0;

	virtual ~Object() {  }
};

struct Sphere : Object {
	float radius;

	Sphere(const Vec3f32& position, const float radius, const Material& material) noexcept
		: Object(position, material), radius(radius)
	{  }

	virtual std::optional<Intersection> Intersects(const Ray& ray) noexcept override {
		Vec3f32 L = this->position - ray.origin; 

        float tca = DotProduct(L, ray.direction); 
    	float d2 = DotProduct(L, L) - tca * tca; 

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
 
		return Intersection{t, ray.origin + ray.direction*t, (Object*)this};		
	}
};
