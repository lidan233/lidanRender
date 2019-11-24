//
// Created by 李源 on 2019-11-22.
//

#ifndef TINYRENDER_MODELANDVIEW_H
#define TINYRENDER_MODELANDVIEW_H

#include "../util/data.h"
#include "../util/common.h"
#include "tgaimage.h"
#include <string.h>
#include <vector>
#include <iostream>
#include <fstream>


using namespace std;

class ModelAndView {
private:
    std::vector<Vec3f> vertexs ;
    std::vector<Vec3f> normal_v;
    std::vector< vector<int> > faces ;

    bool isnormal = false  ;
    float* z_buffer ;

public:
    ModelAndView(const string path) ;
    ModelAndView(vector<Vec3f> points,vector<vector<int> > faces) ;
    ~ModelAndView() ;
    int getVertexSize() ;
    int getFacesSize() ;
    Vec3f getVertex(int n) ;
    std::vector<int> getFace(int idx) ;
    void drawAll_bound(TGAImage& image ,vector<TGAColor> v_c,vector<TGAColor> m_c) ;
    void normal(int height,int width) ;
    void drawAll(TGAImage& image ,vector<TGAColor> v_c,vector<TGAColor> f_c,Vec3f light_dir) ;

};


#endif //TINYRENDER_MODELANDVIEW_H
