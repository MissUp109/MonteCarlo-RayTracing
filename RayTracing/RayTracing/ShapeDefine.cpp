//
//  ShapeDefine.cpp
//  MonteCarloRayTracing
//
//  Created by leah on 2018/3/28.
//  Copyright © 2018年 Leah Love Cage. All rights reserved.
//

#include "ShapeDefine.h"
#include "GlobalControl.h"

ObjectIntersection Sphere::Intersection(const Ray &ray) {
	bool hit = false;
	double distance = 0;
	Double3 normal;

	Double3 oc = center - ray.original;
	double b = dot(oc, ray.direction);
	double det = b * b - dot(oc, oc) + radius * radius;
	if (det < 0)
		return ObjectIntersection(false);
	else
		det = sqrt(det);

	if (b - det > EPSILON) {
		distance = b - det;
	}
	else if (b + det > EPSILON) {
		distance = b + det;
	}
	else {
		distance = 0;
	}

	if (distance != 0) {
		hit = true;
		normal = normalize((ray.original + ray.direction * distance) - center);
	}

	return ObjectIntersection(hit, distance, normal, material);
}


