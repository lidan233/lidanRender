//
// Created by 李源 on 2019-11-22.
//

#include "triangle.h"


Triangle::Triangle(int index[3]) {
    points_i[0] = index[0] ;
    points_i[1] = index[1] ;
    points_i[2] = index[2] ;
}


void Triangle::draw_vec3f(TGAImage &image, vector<Vec3f> points, TGAColor &color)
{
    Point* t1 =new Point(points[points_i[0]].raw[0],points[points_i[0]].raw[1]) ;
    Point* t2 =  new Point(points[points_i[1]].raw[0],points[points_i[1]].raw[1]) ;
    Point* t3 = new Point(points[points_i[2]].raw[0],points[points_i[2]].raw[1]) ;

    if(t1->getY()>t2->getY()) {std::swap(t1,t2) ;}
    if(t1->getY()>t3->getY()) {std::swap(t1,t3) ;}
    if(t2->getY()>t3->getY()) {std::swap(t2,t3) ;}


    //t2>t1>t0 ;
    int total_height = t3->getY()-t1->getY() ;
//    for(int i = t1->getY();i<t2->getY();i++)
//    {
//        int segment_height = t2->getY()-t1->getY()+1 ;
//        float alpha = (float)(i-t1->getY())/total_height ;
//        float beta = (float)(i-t1->getY())/segment_height ;
//
//        Vec2i A = Vec2i(t1->getX(),t1->getY())+
//                    (Vec2i(t3->getX(),t3->getY())-Vec2i(t1->getX(),t1->getY()))*alpha ;
//        Vec2i B = Vec2i(t1->getX(),t1->getY())+
//                  (Vec2i(t2->getX(),t2->getY())-Vec2i(t1->getX(),t1->getY()))*beta ;
////        image.set(A.x,i,red) ;
////        image.set(B.x,i,green ) ;
//        if(A.x>B.x)
//        {
//            std::swap(A,B) ;
//        }
//        //now the A is the left of B ;
//        //so from A to B ;
//
//        for(int j = A.x ;j< B.x;j++)
//        {
//            image.set(j,i,color) ;
//        }
//    }
//
//    for(int y = t2->getY();y<t3->getY() ;y++)
//    {
//        int segment_height  = t3->getY()-t2->getY()+1 ;
//        float alpha = (float)(y-t1->getY())/total_height ;
//        float beta = (float)(y-t2->getY())/segment_height ;
//        Vec2i A = Vec2i(t1->getX(),t1->getY())+
//                  (Vec2i(t3->getX(),t3->getY())-Vec2i(t1->getX(),t1->getY()))*alpha ;
//        Vec2i B = Vec2i(t2->getX(),t2->getY())+
//                  (Vec2i(t3->getX(),t3->getY())-Vec2i(t2->getX(),t2->getY()))*beta ;
//        if(A.x>B.x)
//        {
//            std::swap(A,B) ;
//        }
//        for(int j = A.x;j<=B.x;j++)
//        {
//            image.set(j,y,color) ;
//        }
//    }

    for(int i = 0 ;i< total_height;i++)
    {
        bool second_half = i>(t2->getY()-t1->getY())|| t1->getY()== t2->getY() ;
        int segment_height = second_half?t3->getY()-t2->getY():t2->getY()-t1->getY() ;
        float alpha = (float) i/total_height ;
        float beta =(float)(i-(second_half?t2->getY()-t1->getY():0))/segment_height ;

        Vec2i A = Vec2i(t1->getX(),t1->getY())+
                  (Vec2i(t3->getX(),t3->getY())-Vec2i(t1->getX(),t1->getY()))*alpha ;
        Vec2i B = second_half?( Vec2i(t2->getX(),t2->getY())+(Vec2i(t3->getX(),t3->getY())-Vec2i(t2->getX(),t2->getY()))*beta)
                              :(Vec2i(t1->getX(),t1->getY())+(Vec2i(t2->getX(),t2->getY())-Vec2i(t1->getX(),t1->getY()))*beta) ;
        if(A.x>B.x) std::swap(A,B) ;
        for(int j =A.x;j<=B.x;j++)
        {
            image.set(j,t1->getY()+i,color) ;
        }


    }
//    Line(t1,t2).drawLine_remove_float_plus(image,color) ;
//    Line(t2,t3).drawLine_remove_float_plus(image,color) ;
//    Line(t3,t1).drawLine_remove_float_plus(image,green) ;
}

void Triangle::draw(TGAImage& image,float* zbuffer ,vector<Vec3f*> points,TGAColor color )
{




    std::pair<Vec2i,Vec2i> bound = getMBR( image,points_i,points) ;
    Vec2i xmin = bound.first ;
    Vec2i xmax = bound.second ;

    vector<Point*> temp ;
    temp.push_back(new Point(points[points_i[0]]->raw[0],points[points_i[0]]->raw[1])) ;
    temp.push_back(new Point(points[points_i[1]]->raw[0],points[points_i[1]]->raw[1])) ;
    temp.push_back(new Point(points[points_i[2]]->raw[0],points[points_i[2]]->raw[1])) ;


    Vec3f p ;
    for(p.u = xmin.x;p.u<=xmax.x ;p.u++)
    {
        for(p.v=xmin.y;p.v<=xmax.y;p.v++)
        {
            Vec3f bscreen = barycentric(temp,new Point(p.u,p.v));
            if(bscreen.raw[0]<0||bscreen.raw[1]<0||bscreen.raw[2]<0) continue ;
            p.c = 0 ;
            for(int i = 0; i<3 ;i++) p.c += points[points_i[i]]->raw[2]*bscreen[i];
            if(zbuffer[int(p.u+p.v*image.get_width())]<p.c)
            {
                zbuffer[int(p.u+p.v*image.get_width())] = p.c ;
                image.set(p.u,p.v,color) ;
            }

        }
    }

}