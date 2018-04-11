//
//  Scene.cpp
//  MonteCarloRayTracing
//
//  Created by leah on 2018/3/29.
//  Copyright © 2018年 Leah Love Cage. All rights reserved.
//

#include "Scene.h"

void Scene::Add(Object *obj) {
	objects.push_back(obj);
}

void Scene::Clear() {
	objects.clear();
}

ObjectIntersection Scene::Intersection(const Ray &ray) {
	ObjectIntersection inter, tmp;
	for (unsigned int i = 0; i < objects.size(); ++i) {
		tmp = objects[i]->Intersection(ray);
		if (tmp.distance != 0 && inter.distance > tmp.distance) {
			inter = tmp;
		}
	}
	return inter;
}

Double3 Scene::RayTracing(const Ray &ray, int depth) {
	ObjectIntersection inter = Intersection(ray);

	if (!inter.isHit)
		return Double3();

	Double3 normal = inter.faceNormal;
	Double3 normal_ = dot(normal, ray.direction) < 0 ? normal : -1 * normal;
	Material *material = &inter.faceMaterial;
	Double3 ka = material->getMka();
	Double3 kd = material->getMkd();
	Double3 ks = material->getMks();
	Double3 tf = material->getMtf();
	double ni = material->getMni();
	int ns = material->getMns();

	if (ka != Double3())
		return ka * lightPower;

	if (++depth > RAY_TRACE_DEPTH) {
		return Double3();
	}

	Double3 position = ray.original + inter.distance * ray.direction;

	//漫反射
	if (kd != Double3()) {
		double r1 = 2 * M_PI * drand48(), r2 = drand48(), r2s = sqrt(r2);
		Double3 w = normal_, u = normalize((fabs(w.x)>.1 ? Double3(0, 1) : Double3(1)) % w), v = w % u;
		Double3 diff = normalize(u * cos(r1) * r2s + v * sin(r1) * r2s + w * sqrt(1 - r2));
		return kd * RayTracing(Ray(position, diff), depth) * abs(dot(normal_, diff));
	}

	//反射、折射和全反射
	double nn = dot(normal, normal_) > 0 ? 1.0 / ni : ni;
	double tmp = dot(ray.direction, normal_);
	double cos2c = 1 - nn * nn * (1 - tmp * tmp);
	Double3 reflect = ray.direction - normal * 2 * dot(normal, ray.direction);
	Double3 refract = normalize(ray.direction * nn - normal_ * (tmp * nn + sqrt(cos2c)));

	if (SCENE_NUM == 2) {//金属材质
		Double3 w = reflect;
		Double3 u = normalize((w.z != 0) ? Double3(-w.z, 0, w.x) : Double3(0, -w.z, w.y));
		Double3 v = normalize(u % w);

		double r1 = drand48(), r2 = drand48();
		double theTa = acos(pow(r1, 1.0 / (ns + 1)));
		double phy = 2 * M_PI * r2;

		Double3 reflect = normalize(sin(theTa)*cos(phy) * u + sin(theTa) * sin(phy) * v + cos(theTa) * w);
		return ks * RayTracing(Ray(position, reflect), depth);
	}

	if (cos2c < 0)
		return ks * RayTracing(Ray(position, reflect), depth); //全反射

	if (tf == Double3()) {
		return ks * RayTracing(Ray(position, reflect), depth);//反射
	}
	else {
		double a = ni - 1, b = ni + 1;
		double c = 1 - (dot(normal, normal_) > 0 ? -tmp : dot(refract, normal));
		double R0 = a * a / (b * b);
		double Re = R0 + (1 - R0) * c * c * c * c * c, Tr = 1 - Re;

		double P = .25 + .5 * Re, RP = Re / P, TP = Tr / (1 - P);
		return depth > 2 ? (drand48() < P ?
			RayTracing(Ray(position, reflect), depth) * RP : RayTracing(Ray(position, refract), depth) * TP) :
			RayTracing(Ray(position, reflect), depth) * Re + RayTracing(Ray(position, refract), depth) * Tr;
		//return ks * RayTracing(Ray(position, reflect), depth) * Re + RayTracing(Ray(position, refract), depth) * Tr;//反射、折射
	}
}




