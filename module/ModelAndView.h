//
// Created by 李源 on 2019-11-22.
//

#ifndef TINYRENDER_MODELANDVIEW_H
#define TINYRENDER_MODELANDVIEW_H

#include "../util/data.h"
#include "../util/common.h"
#include "tgaimage.h"
#include "../util/manipulation.h"

#include <string.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <cassert>


using namespace std;

class ModelAndView {
private:
    //normals of vertex
    std::vector<Vec3f> normal_vector_read ;
    std::vector<Vec3f> vertexs ;
    std::vector<Vec3i> normal_v;
    std::vector< vector<int> > faces ;

    vector< vector<int> > idxTex ;
    vector< vector<int> > idxNorm ;

    std::vector<Vec2f> Texs ;
    TGAImage text ;

    bool isnormal = false  ;
    bool useTexture = false ;
    float* z_buffer ;

    int T_width ;
    int T_height ;

    Vec3f camera ;


public:
    ModelAndView(const string path) ;
    ModelAndView(vector<Vec3f> points,vector< vector<int> > faces) ;
    ~ModelAndView() ;
    int getVertexSize() ;
    int getFacesSize() ;
    Vec3f getVertex(int n) ;
    std::vector<int> getFace(int idx) ;
    std::vector<int> getFaceText(int idx) ;
    std::vector<int> getFaceVertexNormIndex(int idx);
    void normal(int height,int width,Vec3f center,Vec3f eye,Vec3f up);
    void drawAll(TGAImage& image ,vector<TGAColor> v_c,vector<TGAColor> f_c,Vec3f light_dir) ;
    void addTexture(string path) ;
    TGAColor getTextureColor(Vec2i point ) ;
    vector<Vec2i> getFaceVertexTexturePosition(int face_i ) ;
    vector<Vec3f> getFaceVectexNorm(int face_i) ;
    void setcamera(Vec3f camera);



};


#endif //TINYRENDER_MODELANDVIEW_H
