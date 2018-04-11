//
//  Camera.cpp
//  MonteCarloRayTracing
//
//  Created by leah on 2018/3/30.
//  Copyright © 2018年 Leah Love Cage. All rights reserved.
//

#include "Camera.h"
#include <iostream>
using namespace std;
Camera::Camera(int w, int h, Double3 pos, Double3 tar, double fSize) {
	width = w;
	height = h;
	position = pos;
	target = tar;
	surfaceSize = fSize;

	direction = target - position;
	x_direction = normalize(cross(Double3(0, 0, 1), -1 * direction));
	y_direction = normalize(cross(x_direction, direction));
}

void Camera::setCamera(int w, int h, Double3 pos, Double3 tar, double fSize) {
	width = w;
	height = h;
	position = pos;
	target = tar;
	surfaceSize = fSize;

	direction = target - position;
	//x_direction = normalize(cross(Double3(0, 0, 1), -1 * direction));
	x_direction = normalize(cross(Double3(0, 1, 0), direction));
	y_direction = normalize(cross(x_direction, direction));
	//cout << x_direction << y_direction;
}

Ray Camera::newRay(int x, int y) {
	Double3 dir = normalize(direction + x_direction * (x - width / 2) * surfaceSize / width + y_direction * (y - height / 2) * surfaceSize / height);
	//cout << dir << endl;
	return Ray(position, dir);
}

int Camera::getWidth() const {
	return width;
}

int Camera::getHeight() const {
	return height;
}

