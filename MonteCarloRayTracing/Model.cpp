//
//  Model.cpp
//  MonteCarloRayTracing
//
//  Created by leah on 2018/3/27.
//  Copyright © 2018年 Leah Love Cage. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <math.h>
#include <Eigen/Dense>
#include "Model.h"
#include "myString.h"

using namespace std;
using namespace Eigen;

Model::Model(const string &MTLPath, const string &OBJPath){
    Load(MTLPath, OBJPath);
}

bool Model::Load(const string &MTLPath, const string &OBJPath){
    if(LoadMTL(MTLPath)){
        return LoadOBJ(OBJPath);
    }
    return false;
}

bool Model::LoadMTL(const string &filePath){
    ifstream file(filePath);
    if(!file.is_open()){
        cout << "Can't open the file." << endl;
        return false;
    }
    string line;
    int count = 0;
    while(getline(file, line)){
        string type;
        stringstream stringPos;
        
        if(line.substr(0, 6) == "newmtl"){
            Material newMat;
            stringPos << line;
            stringPos >> type >> newMat.m_type;
            materialList.push_back(newMat);
            ++count;
        }
        if(line.substr(0, 5) == "illum"){
            int illu;
            stringPos << line;
            stringPos >> type >> illu;
            materialList[count - 1].m_illu = illu;
        }
        if(line.substr(0, 2) == "Ka"){
            Double3 ka;
            stringPos << line;
            stringPos >> type >> ka.x >> ka.y >> ka.z;
            materialList[count - 1].m_ka = ka;
        }
        if(line.substr(0, 2) == "Kd"){
            Double3 kd;
            stringPos << line;
            stringPos >> type >> kd.x >> kd.y >> kd.z;
            materialList[count - 1].m_kd = kd;
        }
        if(line.substr(0, 2) == "Ks"){
            Double3 ks;
            stringPos << line;
            stringPos >> type >> ks.x >> ks.y >> ks.z;
            materialList[count - 1].m_ks = ks;
        }
        if(line.substr(0, 2) == "Tf"){
            Double3 tf;
            stringPos << line;
            stringPos >> type >> tf.x >> tf.y >> tf.z;
            materialList[count - 1].m_tf = tf;
        }
        if(line.substr(0, 2) == "Ni"){
            double ni;
            stringPos << line;
            stringPos >> type >> ni;
            materialList[count - 1].m_ni = ni;
        }
        if(line.substr(0, 2) == "Ns"){
            int ns;
            stringPos << line;
            stringPos >> type >> ns;
            materialList[count - 1].m_ns = ns;
        }
    }
    
    file.close();
    cout << "Load MTL successfully." << endl;
    return true;
}

bool Model::LoadOBJ(const string &filePath){
    ifstream file(filePath);
    if(!file.is_open()){
        cout << "Can't open the file." << endl;
        return false;
    }
    string line, currMatName;
    Material *currMat = NULL;
    while(getline(file, line)){//注意：顶点和法向量数据要在面数据前
        string type;
        stringstream stringPos;
        
        if(line.substr(0, 6) == "usemtl"){
            stringPos << line;
            stringPos >> type >> currMatName;
            int i = 0;
            unsigned long materialNum = materialList.size();
            for( ; i < materialNum; ++i){
                if(materialList[i].m_type == currMatName){
                    currMat = &materialList[i];
                    break;
                }
            }
            if(i >= materialNum){
                cout << "There is something wrong with mtl" << endl;
                return false;
            }
        }
        
        if(line.substr(0, 2) == "v "){//model.vertexList
            Vertex v;
            stringPos << line;
            stringPos >> type >> v.pos.x >> v.pos.y >> v.pos.z;
            vertexList.push_back(v);
        }
        else if(line.substr(0, 2) == "vn"){//model.normalList
            Double3 vn;
            stringPos << line;
            stringPos >> type >> vn.x >> vn.y >> vn.z;
            normalList.push_back(vn);
        }
        else if(line.substr(0, 2) == "f "){//model.faceList
            vector<string> strArr = Split(line, " ");
            Face f1;
            for(int i = 1; i <= 3; ++i){
                if(strArr[i].npos != strArr[i].find('/')){
                    vector<string> tmpArr1 = Split(strArr[i], "/");
                    
                    int vIdx1 = atoi(tmpArr1[0].c_str());//顶点索引：f.vertexIDX
                    f1.vertexIDX.push_back(--vIdx1);//obj的索引是从1开始
                    
                    int nIdx1 = atoi(tmpArr1[2].c_str());//法向量索引：f.normalIDX
                    f1.normalIDX.push_back(--nIdx1);//obj的索引是从1开始
                    
                }
            }
            for(int i = 0; i < 3; ++i)//面法向量：f.normal
                f1.normal += normalList[f1.normalIDX[i]];
            f1.normal = normalize(f1.normal);
            f1.material = currMat;
            faceList.push_back(f1);
            
            if(strArr.size() == 6){
                Face f2;
                for(int i = 3; i <= 5; ++i){
                    int index = (i == 5) ? 1 : i;
                    if(strArr[index].npos != strArr[index].find('/')){
                        vector<string> tmpArr2 = Split(strArr[index], "/");
                        
                        int vIdx2 = atoi(tmpArr2[0].c_str());//顶点索引：f.vertexIDX
                        f2.vertexIDX.push_back(--vIdx2);//obj的索引是从1开始
                        
                        int nIdx2 = atoi(tmpArr2[2].c_str());//法向量索引：f.normalIDX
                        f2.normalIDX.push_back(--nIdx2);//obj的索引是从1开始
                        
                    }
                }
                f2.normal = f1.normal;
                f2.material = currMat;
                faceList.push_back(f2);
            }
        }
    }
    
    file.close();
    cout << "Load model successfully." << endl;
    return true;
}

ObjectIntersection Model::Intersection(const Ray &ray){
    ObjectIntersection inter, tmp;
    
    for(int i = 0; i < faceList.size(); ++i){
        tmp = FaceIntersection(ray, faceList[i]);
        if(tmp.isHit && (tmp.distance < inter.distance || inter.distance == 0)){
            inter = tmp;
        }
    }
    return inter;
}

ObjectIntersection Model::FaceIntersection(const Ray &ray, const Face &face){
    //cout << ray.original << ray.direction;
    /*if(face.vertexIDX.size() != 3){
        cout << "There is something wrong with face's vertexIDX size." << endl;
        return ObjectIntersection();
    }*/
    Double3 vertex[3];
    
    for(int i = 0; i < 3; ++i){
        vertex[i] = vertexList[face.vertexIDX[i]].pos;
    }
    
    Double3 edge1 = vertex[1] - vertex[0];
    Double3 edge2  = vertex[2] - vertex[0];
    Double3 dir = ray.direction;
    //cout << dir.x << " " << dir.y << " " << dir.z << endl;
    Double3 ori_v0 = ray.original - vertex[0];
    
    Matrix3d A;
    A.col(0) = Vector3d(edge1.x, edge1.y, edge1.z);
    A.col(1) = Vector3d(edge2.x, edge2.y, edge2.z);
    A.col(2) = Vector3d(-dir.x, -dir.y, -dir.z);
    
    //判断行列式
    double det = A.determinant();

    if(abs(det) <= ZERO ){
        return ObjectIntersection();
    }
    Vector3d B = Vector3d(ori_v0.x, ori_v0.y, ori_v0.z);
    Matrix3d a1, a2, a3;
    a1 = A; a1.col(0) = B;
    a2 = A; a2.col(1) = B;
    a3 = A; a3.col(2) = B;
    
    /*Vector3d results = A.reverse() * B;
    
    double u = results[0];
    double v = results[1];
    double t = results[2];*/
    
    double u = a1.determinant() / det;
    double v = a2.determinant() / det;
    double t = a3.determinant() / det;
        
    if(u < 0 | u > 1 | v < 0 | v > 1 | t <= 0 | u + v > 1){
        return ObjectIntersection();
    }
    //cout << "hhhhh"<< endl;
    
    return ObjectIntersection(true, t, face.normal, *face.material);
}


