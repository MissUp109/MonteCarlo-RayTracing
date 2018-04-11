//
//  Double3.h
//  MonteCarlo
//
//  Created by leah on 2018/3/19.
//  Copyright © 2018年 Leah Love Cage. All rights reserved.
//

#ifndef Double3_h
#define Double3_h
#include <math.h>
#include <iostream>
using namespace std;

class Double3{
public:
    union {
        struct{ double x, y, z; };
        struct{ double r, g, b; };
    };
    
    //Double3(){};
    Double3(double x = 0, double y = 0, double z = 0){
        this->x = x;
        this->y = y;
        this->z = z;
    };
    
    inline double maganitude(){ return sqrt(x * x + y * y + z * z);}
    
    inline Double3& operator = (const Double3 &v) { x = v.x; y = v.y; z = v.z; return *this; }
    
    inline Double3& operator += (double num) { x += num; y += num; z += num; return *this; }
    inline Double3& operator += (const Double3 &v) { x += v.x; y += v.y; z += v.z; return *this; }
    
    inline Double3& operator -= (double num) { x -= num; y -= num; z -= num; return *this; }
    inline Double3& operator -= (const Double3 &v) { x -= v.x; y -= v.y; z -= v.z; return *this; }
    
    inline Double3& operator *= (double num) { x *= num; y *= num; z *= num; return *this; }
    inline Double3& operator *= (const Double3 &v) { x *= v.x; y *= v.y; z *= v.z; return *this; }
    
    inline Double3& operator /= (double num) { x /= num; y /= num; z /= num; return *this; }
    inline Double3& operator /= (const Double3 &v) { x /= v.x; y /= v.y; z /= v.z; return *this; }
    
    inline bool operator == (const Double3 &u) {
        return (x - u.x == 0) && (y - u.y == 0) && (z - u.z == 0);
    }
    inline bool operator != (const Double3 &u) {
        return !((x - u.x == 0) && (y - u.y == 0) && (z - u.z == 0));
    }
    
    friend inline ostream& operator << (ostream &out, const Double3 &obj){
        out << obj.x << " " << obj.y << " " << obj.z << endl;
        return out;
    }

    friend inline Double3 operator + (const Double3 &u, double num) {
        return Double3(u.x + num, u.y + num, u.z + num);
    }
    friend inline Double3 operator + (double num, const Double3 &u) {
        return Double3(num + u.x, num + u.y, num + u.z);
    }
    friend inline Double3 operator + (const Double3 &u, const Double3 &v) {
        return Double3(u.x + v.x, u.y + v.y, u.z + v.z);
    }
    friend inline Double3 operator - (const Double3 &u, double num) {
        return Double3(u.x - num, u.y - num, u.z - num);
    }
    friend inline Double3 operator - (double num, const Double3 &u) {
        return Double3(num - u.x, num - u.y, num - u.z);
    }
    friend inline Double3 operator - (const Double3 &u, const Double3 &v) {
        return Double3(u.x - v.x, u.y - v.y, u.z - v.z);
    }
    friend inline Double3 operator * (const Double3 &u, double num) {
        return Double3(u.x * num, u.y * num, u.z * num);
    }
    friend inline Double3 operator * (double num, const Double3 &u) {
        return Double3(num * u.x, num * u.y, num * u.z);
    }
    friend inline Double3 operator * (const Double3 &u, const Double3 &v) {
        return Double3(u.x * v.x, u.y * v.y, u.z * v.z);
    }
    friend inline Double3 operator / (const Double3 &u, double num) {
        return Double3(u.x / num, u.y / num, u.z / num);
    }
    friend inline Double3 operator / (double num, const Double3 &u) {
        return Double3(num / u.x, num / u.y, num / u.z);
    }
    friend inline Double3 operator / (const Double3 &u, const Double3 &v) {
        return Double3(u.x / v.x, u.y / v.y, u.z / v.z);
    }
    
    friend inline Double3 operator % (const Double3 &u, const Double3 &v){
        return Double3(u.y * v.z - u.z * v.y, u.z * v.x - u.x * v.z, u.x * v.y - u.y * v.x);
    }
};

inline Double3 cross(const Double3 &u, const Double3 &v)
{
    return Double3(u.y * v.z - u.z * v.y, u.z * v.x - u.x * v.z, u.x * v.y - u.y * v.x);
}

inline double dot(const Double3 &u, const Double3 &v)
{
    return u.x * v.x + u.y * v.y + u.z * v.z;
}

inline double length(const Double3 &u)
{
    return sqrt(u.x * u.x + u.y * u.y + u.z * u.z);
}

inline Double3 normalize(const Double3 &u)
{
    return u * (1.0f / sqrt(u.x * u.x + u.y * u.y + u.z * u.z));
}


#endif /* Double3_h */
