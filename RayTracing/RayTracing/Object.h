//
//  Object.h
//  MonteCarloRayTracing
//
//  Created by leah on 2018/3/28.
//  Copyright © 2018年 Leah Love Cage. All rights reserved.
//

#ifndef Object_h
#define Object_h

#include "GlobalControl.h"
#include "Material.h"
#include "Ray.h"

struct ObjectIntersection {
	bool isHit;
	double distance;
	Double3 faceNormal;
	Material faceMaterial;

	ObjectIntersection(bool isHit_ = false, double distance_ = INFINITE, Double3 faceNormal_ = Double3(), Material faceMaterial_ = Material()) : isHit(isHit_), distance(distance_), faceNormal(faceNormal_), faceMaterial(faceMaterial_) {}
};

class Object {
public:
	//Double3 position;
	virtual ObjectIntersection Intersection(const Ray &ray) = 0;
};

#endif /* Object_h */
