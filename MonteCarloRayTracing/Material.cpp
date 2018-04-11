//
//  Material.cpp
//  MonteCarloRayTracing
//
//  Created by leah on 2018/3/30.
//  Copyright © 2018年 Leah Love Cage. All rights reserved.
//

#include "Material.h"
#include <stdlib.h>
string Material::getMtype() const{ return m_type; }
Double3 Material::getMka() const{ return m_ka; }
Double3 Material::getMkd() const{ return m_kd; }
Double3 Material::getMks() const{ return m_ks; }
Double3 Material::getMtf() const{ return m_tf; }
double Material::getMni() const{ return m_ni; }
int Material::getMns() const{return m_ns; }




