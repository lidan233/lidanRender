//
// Created by 李源 on 2019-11-29.
//

#include "data.h"

template<> template<> vec<3,int>::vec(const vec<3,float>& v):
    x(int(v.x+0.5)) ,
    y(int(v.y+0.5)) ,
    z(int(v.z+0.5))
{}


template<> template<> vec<3,float>::vec(const vec<3,int>& v):
        x(v.x) ,
        y(v.y) ,
        z(v.z)
{}