//
//  Scene.h
//  MonteCarloRayTracing
//
//  Created by leah on 2018/3/29.
//  Copyright © 2018年 Leah Love Cage. All rights reserved.
//

#ifndef Scene_h
#define Scene_h
#include <vector>
#include "Object.h"

class Scene {
private:
	double lightPower;
	vector<Object *> objects;
public:
	Scene(double power) : lightPower(power) {}
	void Add(Object *obj);
	void Clear();
	ObjectIntersection Intersection(const Ray &ray);
	Double3 RayTracing(const Ray &ray, int depth);
};

inline double drand48() {
	return rand()*1.0 / RAND_MAX;
}

#endif /* Scene_h */
