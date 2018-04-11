//
//  Render.cpp
//  MonteCarloRayTracing
//
//  Created by leah on 2018/3/30.
//  Copyright © 2018年 Leah Love Cage. All rights reserved.
//

#include "Render.h"
#include <string.h>
#include <stdio.h>
using namespace std;

Render::Render(Scene *s, Camera *c) {
	scene = s;
	camera = c;
	width = camera->getWidth();
	height = camera->getHeight();
	buffer = new Double3[width * height];
	memset(buffer, 0, width * height * 3);
}

void Render::rayCasting() {
	for (int y = 0; y < height; ++y) {
		fprintf(stderr, "\rRendering (%i SAMPLES): %.2f%% ", 1, (double)y / height * 100);
		for (int x = 0; x < width; ++x) {
			Ray ray = camera->newRay(x, y);
			//ObjectIntersection inter = scene->Intersection(ray);
			//if(inter.isHit){
			//cout << "isHit." << endl;
			//buffer[y * width + x] = inter.faceNormal * 255;
			//}
			Double3 color = scene->RayTracing(ray, 0);
			buffer[y * width + x] = 255 * Double3(clamp(color.r), clamp(color.g), clamp(color.b));
		}
	}

}

void Render::renderingThread()
{
	std::thread t1(&Render::rendering, this, 0, 100, SAMPLE_NUM);
	std::thread t2(&Render::rendering, this, 100, 200, SAMPLE_NUM);
	std::thread t3(&Render::rendering, this, 200, 300, SAMPLE_NUM);
	std::thread t4(&Render::rendering, this, 300, 400, SAMPLE_NUM);
	t1.join();
	t2.join();
	t3.join();
	t4.join();
}

void Render::rendering(int start, int end, int samples) {
	for (int y = start; y < end; ++y) {
		fprintf(stderr, "\rRendering (%i SAMPLES): %.2f%% ", samples, (double)y / height * 100);
		for (int x = 0; x < width; ++x) {
			Double3 color = Double3();
			for (int i = 0; i < samples; ++i) {
				Ray ray = camera->newRay(x, y);
				color += scene->RayTracing(ray, 0);
			}
			color *= 1.0 / samples;
			buffer[y * width + x] = 255 * Double3(clamp(color.r), clamp(color.g), clamp(color.b));
		}
	}
}

void Render::savePicture(const string path) {
	FILE *f = fopen(path.c_str(), "w");         // Write image to PPM file.
	fprintf(f, "P3\n%d %d\n%d\n", width, height, 255);
	for (int i = 0; i < width * height; i++)
		fprintf(f, "%d %d %d ", (int)buffer[i].x, (int)buffer[i].y, (int)buffer[i].z);
	//fprintf(f,"%d %d %d ", toInt(buffer[i].x), toInt(buffer[i].y), toInt(buffer[i].z));
}

