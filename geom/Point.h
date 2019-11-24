//
// Created by 李源 on 2019-11-21.
//

#ifndef TINYRENDER_POINT_H
#define TINYRENDER_POINT_H


#include "../util/data.h"

class Point {
private:
    double x_ ;
    double y_ ;
    char* data ;

public:
    Point(double x ,double y):x_(x),y_(y){}
    Point(const Point& ano):x_(ano.x_),y_(ano.y_){}
    Point(const Vec3f& vec):x_(vec[0]),y_(vec[1]){}
    Point* CopyPoint(Point& point){return new Point(point);}

    double getX(){return x_ ;}
    double getY(){return y_ ;}
};


#endif //TINYRENDER_POINT_H
