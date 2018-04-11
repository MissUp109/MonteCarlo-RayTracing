//
//  ShapeDefine.h
//  MonteCarloRayTracing
//
//  Created by leah on 2018/3/28.
//  Copyright © 2018年 Leah Love Cage. All rights reserved.
//

#ifndef ShapeDefine_h
#define ShapeDefine_h
#include "Object.h"

class Sphere : public Object {
private:
	Double3 center;
	double radius;
	Material material;
public:
	Sphere(Double3 center_, double radius_, Material material_) : center(center_), radius(radius_), material(material_) {}
	virtual ObjectIntersection Intersection(const Ray &ray);
};

#endif /* ShapeDefine_h */
