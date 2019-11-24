//
// Created by 李源 on 2019-11-22.
//

#include "ModelAndView.h"
#include "../geom/Line.h"

ModelAndView::ModelAndView(const string path)
{
//    string temp ;
//    ifstream file(path) ;
//
//    while(getline(file,temp))
//    {
//        vector<string> temp_s = getstringObj(temp) ;
//        if(temp_s[0]=="v")
//        {
//            Vec3f vertex(round((float)std::atof(temp_s[1].c_str()),2)
//                        ,round((float)std::atof(temp_s[2].c_str()),2)
//                        ,round((float)std::atof(temp_s[3].c_str()),2)) ;
//            vertexs.push_back(vertex) ;
//        }else if(temp_s[0]=="f")
//        {
//            std::vector<int> face ;
//            face.push_back((int)(std::atoi(temp_s[1].c_str()))) ;
//            face.push_back((int)(std::atoi(temp_s[2].c_str()))) ;
//            face.push_back((int)(std::atof(temp_s[3].c_str()))) ;
//
//            faces.push_back(face) ;
//        }
//    }
    readObj(path,vertexs,faces) ;
}
ModelAndView::~ModelAndView()
{

}
int ModelAndView::getVertexSize(){return vertexs.size() ;}
int ModelAndView::getFacesSize() {return faces.size() ;}
Vec3f ModelAndView::getVertex(int n) {return vertexs[n] ;}
std::vector<int> ModelAndView::getFace(int idx){return faces[idx] ;}
void ModelAndView::drawAll_bound(TGAImage& image ,vector<TGAColor> v_c,vector<TGAColor> f_c)
{

    int size = getFacesSize() ;
    for(int i = 0; i<size ;i++)
    {
        std::vector<int> face = getFace(i) ;
        for(int j = 0; j < 3; j++)
        {
            Vec3f v0 = isnormal==true?normal_v[face[j]]:vertexs[face[j]] ;
            Vec3f v1 = isnormal==true?normal_v[face[(j+1)%3]]:vertexs[face[(j+1)%3]] ;
            Line a = Line(new Point(v0[0],v0[1]),new Point(v1[0],v1[1])) ;
            a.drawLine_remove_float_plus(image,(v_c.size()>face[j])?v_c[face[j]]:white) ;
        }
    }
}

void ModelAndView::drawAll(TGAImage& image ,vector<TGAColor> v_c,vector<TGAColor> f_c,Vec3f light_dir)
{

    z_buffer = new float[image.get_width()*image.get_height()] ;

    srand(time(NULL) ) ;
    int size = getFacesSize() ;
    for(int i = 0; i< size;i++)
    {
        std::vector<int> face = getFace(i) ;

        vector<Vec3f*> t4 ;
        if(isnormal)
        {
            t4.push_back(&normal_v[face[0]]);
            t4.push_back(&normal_v[face[1]]);
            t4.push_back(&normal_v[face[2]]);
        }else{
            t4.push_back(&vertexs[face[0]]);
            t4.push_back(&vertexs[face[1]]);
            t4.push_back(&vertexs[face[2]]);
        }

        Vec3f n = (vertexs[face[2]]-vertexs[face[0]])^(vertexs[face[1]]-vertexs[face[0]]) ;
        n.normalize() ;
        float intensity = n*light_dir ;

        if(intensity>0)
        {
            int index3[3] = {0,1,2};
            Triangle d(index3) ;

            d.draw(image,z_buffer, t4,TGAColor(intensity*255,intensity*255,intensity*255,255)) ;

        }

    }

}
void ModelAndView::normal(int height,int width)
{
    isnormal = true ;
    normal_v = vertexs ;
    normalVertexs(normal_v,height,width) ;
}