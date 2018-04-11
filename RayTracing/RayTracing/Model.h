//
//  Model.h
//  MonteCarloRayTracing
//
//  Created by leah on 2018/3/27.
//  Copyright © 2018年 Leah Love Cage. All rights reserved.
//

#ifndef Model_h
#define Model_h
#include <string>
#include <vector>
#include "Object.h"
#include "Material.h"
#include "Double3.h"

using namespace std;
class Model;
class Vertex {
private:
	Double3 pos;
	//Double3 color;
public:
	Vertex() {};//对color初始化
	friend class Model;
};

class Face {
private:
	vector<int> vertexIDX;
	vector<int> normalIDX;
	Double3 normal;
	Material *material;
public:
	Face() {};
	//bool LoadMTL(const string &filePath);
	friend class Model;
};

class Model : public Object {
private:
	vector<Vertex> vertexList;
	vector<Double3> normalList;
	vector<Face>   faceList;
	vector<Material> materialList;

public:
	Model() {};
	Model(const string &MTLPath, const string &OBJPath);

	bool Load(const string &MTLPath, const string &OBJPath);
	bool LoadOBJ(const string &filePath);
	bool LoadMTL(const string &filePath);
	virtual ObjectIntersection Intersection(const Ray &ray);
	ObjectIntersection FaceIntersection(const Ray &ray, const Face &face);
	friend class Face;
};

#endif /* Model_h */
