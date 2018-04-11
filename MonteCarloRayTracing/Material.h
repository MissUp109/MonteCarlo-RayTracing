//
//  Material.h
//  MonteCarloRayTracing
//
//  Created by leah on 2018/3/27.
//  Copyright © 2018年 Leah Love Cage. All rights reserved.
//

#ifndef Material_h
#define Material_h
#include "Double3.h"
#include "Ray.h"
//#include "Model.h" 不能和相互引用
#include <string>
using namespace std;

enum ReflectType{
    DIFF, SPEC, REFR
};

class Material {
private:
    string m_type; //材质名称
    Double3 m_ka;  //ambient color
    Double3 m_kd;  //diffuse color
    Double3 m_ks;  //specular color
    Double3 m_tf;  //滤光透射率
    double m_ni;  //折射率
    int m_ns;
    int m_illu;
public:
    Material(string mtype = "", Double3 mka = Double3(), Double3 mkd = Double3(), Double3 mks = Double3(), Double3 mtf = Double3(), double mni = 1, int mns = 0, int millu = 0):
    m_type(mtype), m_ka(mka), m_kd(mkd), m_ks(mks), m_tf(mtf), m_ni(mni), m_ns(mns), m_illu(millu) {}
    
    //Ray getRefelectedRay(const Ray &ray, const Double3 &inter, const Double3 &normal, const ReflectType &type) const;
    
    string getMtype() const;
    Double3 getMka() const;
    Double3 getMkd() const;
    Double3 getMks() const;
    Double3 getMtf() const;
    double getMni() const;
    int getMns() const;
    int getMillu() const;
    
    friend class Model;
};
#endif /* Material_h */
