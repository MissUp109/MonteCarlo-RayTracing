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
string ROOT =  "/Users/leah/Desktop/RayTracing/MonteCarloRayTracing/";
void setScene(Scene &scene, Camera &camera, int sceneNum);
int main(int argc, const char * argv[]) {
    Scene scene(LIGHT_POWER);
    Camera camera;
    int num = argc==2 ? atoi(argv[1])/4 : SCENE_NUM;
    setScene(scene, camera, num);
    Render *render = new Render(&scene, &camera);
    render->rendering();
    //render->rayCasting();
    render->savePicture(ROOT + "Results/image.ppm");
    delete  render;
    return 0;
}

void setScene(Scene &scene, Camera &camera, int sceneNum){
    scene.Clear();
    string mtlPath, objPath;

    switch (sceneNum) {
        case 1:{
            mtlPath = ROOT + "Scene/scene01.mtl";
            objPath = ROOT + "Scene/scene01.obj";
            scene.Add(dynamic_cast<Object *>(new Model(mtlPath, objPath)));
            Material mirroMat("sphere_mirror", Double3(), Double3(), Double3(1, 1, 1), Double3(), 1, 1000);
            Material transMat("sphere_mirror", Double3(), Double3(), Double3(0.5, 0.5, 0.5), Double3(0.9, 0.9, 0.9), 1.5);
            scene.Add(dynamic_cast<Object *>(new Sphere(Double3(2, 2, -2), 2, mirroMat)));
            scene.Add(dynamic_cast<Object *>(new Sphere(Double3(-2, 2, 2), 2, transMat)));
            camera.setCamera(100, 100, Double3(0, 5, 30), Double3(0, 5, 5), 15.0);
            break;
        }
        case 2:{
            mtlPath = ROOT + "Scene/scene03.mtl";
            objPath = ROOT + "Scene/scene03.obj";
            Material lightMat("lambert", Double3(25.0, 25.0, 25.0), Double3(0.5, 0.5, 0.5));
            scene.Add(dynamic_cast<Object *>(new Model(mtlPath, objPath)));
            scene.Add(dynamic_cast<Object *>(new Sphere(Double3(7, 10, 1), 0.1, lightMat)));
            scene.Add(dynamic_cast<Object *>(new Sphere(Double3(4, 10, 1), 0.4, lightMat)));
            scene.Add(dynamic_cast<Object *>(new Sphere(Double3(1, 10, 1), 0.7, lightMat)));
            scene.Add(dynamic_cast<Object *>(new Sphere(Double3(-3, 10, 1), 1.0, lightMat)));
            camera.setCamera(300, 300, Double3(2, 4, 15), Double3(2, 5, 5), 15);
            break;
        }
        case 3:{
            mtlPath = ROOT + "Scene/myScene2.mtl";
            objPath = ROOT + "Scene/myScene2.obj";
            //Material lightMat("lambert", Double3(25.0, 25.0, 25.0), Double3(0.5, 0.5, 0.5));
            scene.Add(dynamic_cast<Object *>(new Model(mtlPath, objPath)));
            //scene.Add(dynamic_cast<Object *>(new Sphere(Double3(7, 10, 0), 0.5, lightMat)));
            camera.setCamera(300, 300, Double3(2, 5, 15), Double3(2, 5, 5), 15);
            break;
        }
        default:
            fprintf(stderr, "%d is a wrong number.\n", SCENE_NUM);
            exit(-1);
    }
}
