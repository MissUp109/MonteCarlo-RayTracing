//
//  main.cpp
//  MonteCarloRayTracing
//
//  Created by leah on 2018/3/27.
//  Copyright © 2018年 Leah Love Cage. All rights reserved.
//

#include <iostream>
#include "Model.h"
#include "ShapeDefine.h"
#include "Render.h"
using namespace std;
string ROOT = "E:/CPP/RayTracing/";
void setScene(Scene &scene, Camera &camera, int sceneNum);
int main(int argc, const char * argv[]) {
	Scene scene(LIGHT_POWER);
	Camera camera;
	int num = argc == 2 ? atoi(argv[1]) / 4 : SCENE_NUM;
	setScene(scene, camera, num);
	Render *render = new Render(&scene, &camera);
	render->rendering();
	//render->rayCasting();
	render->savePicture(ROOT + "Results/image.ppm");
	delete  render;
	return 0;
}

void setScene(Scene &scene, Camera &camera, int sceneNum) {
	scene.Clear();
	string mtlPath, objPath;

	switch (sceneNum) {
	case 1: {
		mtlPath = ROOT + "Scenes/scene01.mtl";
		objPath = ROOT + "Scenes/scene01.obj";
		scene.Add(dynamic_cast<Object *>(new Model(mtlPath, objPath)));
		Material mirroMat("sphere_mirror", Double3(), Double3(), Double3(1, 1, 1), Double3(), 1, 1000);
		Material transMat("sphere_mirror", Double3(), Double3(), Double3(0.5, 0.5, 0.5), Double3(0.9, 0.9, 0.9), 1.5);
		scene.Add(dynamic_cast<Object *>(new Sphere(Double3(2, 2, -2), 2, mirroMat)));
		scene.Add(dynamic_cast<Object *>(new Sphere(Double3(-2, 2, 2), 2, transMat)));
		camera.setCamera(500, 500, Double3(0, 5, 30), Double3(0, 5, 5), 15.0);
		break;
	}
	case 2: {
		mtlPath = ROOT + "Scenes/scene02.mtl";
		objPath = ROOT + "Scenes/scene02.obj";
		Material lightMat("lambert", Double3(25.0, 25.0, 25.0), Double3(0.5, 0.5, 0.5));
		//scene.Add(dynamic_cast<Object *>(new Model(mtlPath, objPath)));
		//scene.Add(dynamic_cast<Object *>(new Sphere((7, 10, 0), 0.1, lightMat)));
		//scene.Add(dynamic_cast<Object *>(new Sphere((4, 10, 0), 0.4, lightMat)));
		scene.Add(dynamic_cast<Object *>(new Sphere((4, 25, 0), 0.7, lightMat)));
		//scene.Add(dynamic_cast<Object *>(new Sphere((-3, 10, 0), 1.0, lightMat)));
		camera.setCamera(300, 300, Double3(2, 5, 15), Double3(2, 5, 5), 15.0);
		break;
	}
	case 3: {
		mtlPath = ROOT + "Scenes/myScene2.mtl";
		objPath = ROOT + "Scenes/myScene2.obj";
		//Material lightMat("lambert", Double3(25.0, 25.0, 25.0), Double3(0.5, 0.5, 0.5));
		scene.Add(dynamic_cast<Object *>(new Model(mtlPath, objPath)));
		//scene.Add(dynamic_cast<Object *>(new Sphere((1, 10, 0), 0.7, lightMat)));
		camera.setCamera(300, 300, Double3(0, -5, 80), Double3(0, -5, 0), 20.0);
		break;
	}
	default:
		fprintf(stderr, "%d is a wrong number.\n", SCENE_NUM);
		exit(-1);
	}
}
