//
// Created by 李源 on 2019-11-22.
//

#ifndef TINYRENDER_TRIANGLE_H
#define TINYRENDER_TRIANGLE_H
#include "Point.h"
#include "Line.h"
#include "../module/tgaimage.h"
#include "../util/common.h"
#include "../util/data.h"
#include <vector>
#include <tuple>
using namespace std ;


class Triangle {
public:
    int  points_i[3] ;


    Triangle(int index[3]);
    void draw_vec3f(TGAImage& image,vector<Vec3f> points,TGAColor& color ) ;
    void draw(TGAImage& image,float* zbuffer ,vector<Vec3f*> points,vector<Vec2i> colorsPosition ,float intensity,TGAImage textImage);
    void draw_vec3i(TGAImage &image, float *zbuffer, vector<Vec3i> points, vector<Vec2i> colorsPosition, float intensity,
                    TGAImage textImage);
};


#endif //TINYRENDER_TRIANGLE_H
