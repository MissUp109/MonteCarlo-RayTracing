//
//  Camera.h
//  MonteCarloRayTracing
//
//  Created by leah on 2018/3/30.
//  Copyright © 2018年 Leah Love Cage. All rights reserved.
//

#ifndef Camera_h
#define Camera_h
#include "Double3.h"
#include "Ray.h"

class Camera {
private:
	int width;
	int height;
	Double3 position;
	Double3 target; //投影平面中心点
	double surfaceSize;

	Double3 direction;
	Double3 x_direction;
	Double3 y_direction;
public:
	Camera() {}
	Camera(int w, int h, Double3 pos, Double3 tar, double fSize);
	void setCamera(int w, int h, Double3 pos, Double3 tar, double fSize);
	int getWidth() const;
	int getHeight() const;
	Ray newRay(int x, int y);
};

#endif /* Camera_h */
