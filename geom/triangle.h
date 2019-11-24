//
// Created by 李源 on 2019-11-22.
//

#ifndef TINYRENDER_TRIANGLE_H
#define TINYRENDER_TRIANGLE_H
#include "Point.h"
#include "Line.h"
#include "../module/tgaimage.h"
#include "../util/common.h"

#include <vector>
#include <tuple>
using namespace std ;


class Triangle {
public:
    Triangle(int index[3]);
    void draw_vec3f(TGAImage& image,vector<Vec3f> points,TGAColor& color ) ;
    void draw(TGAImage& image,float* zbuffer ,vector<Vec3f*> points,TGAColor color );
    int  points_i[3] ;
};


#endif //TINYRENDER_TRIANGLE_H
