//
//  Render.h
//  MonteCarloRayTracing
//
//  Created by leah on 2018/3/30.
//  Copyright © 2018年 Leah Love Cage. All rights reserved.
//

#ifndef Render_h
#define Render_h
#include <thread>
#include "Scene.h"
#include "Camera.h"
#include "GlobalControl.h"

class Render {
private:
	Scene *scene;
	Camera *camera;
	Double3 *buffer;
	int width;
	int height;
public:
	Render(Scene *s, Camera *c);
	void renderingThread();
	void rendering(int start, int end, int samples = SAMPLE_NUM);
	void savePicture(const string path);
	void rayCasting();
};

inline double clamp(double x) { return x<0 ? 0 : x>1 ? 1 : x; }
inline int toInt(double x) { return int(pow(clamp(x), 1 / 2.2) * 255 + .5); }

#endif /* Render_h */
