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
    readObj(path,vertexs,faces,idxTex,Texs,normal_vector_read,idxNorm) ;
    cout<<"fuck";
}
ModelAndView::~ModelAndView()
{

}
int ModelAndView::getVertexSize(){return vertexs.size() ;}
int ModelAndView::getFacesSize() {return faces.size() ;}
Vec3f ModelAndView::getVertex(int n) {return vertexs[n] ;}


std::vector<int> ModelAndView::getFace(int idx){return faces[idx] ;}
std::vector<int> ModelAndView::getFaceText(int idx){ return idxTex[idx] ;}
std::vector<int> ModelAndView::getFaceVertexNormIndex(int idx){ return idxNorm[idx] ;}

//
//void ModelAndView::drawAll_bound(TGAImage& image ,vector<TGAColor> v_c,vector<TGAColor> f_c)
//{
//
//    int size = getFacesSize() ;
//    for(int i = 0; i<size ;i++)
//    {
//        std::vector<int> face = getFace(i) ;
//        for(int j = 0; j < 3; j++)
//        {
//            Vec3f v0 = isnormal==true?normal_v[face[j]]:vertexs[face[j]] ;
//            Vec3f v1 = isnormal==true?normal_v[face[(j+1)%3]]:vertexs[face[(j+1)%3]] ;
//            Line a = Line(new Point(v0[0],v0[1]),new Point(v1[0],v1[1])) ;
//            a.drawLine_remove_float_plus(image,(v_c.size()>face[j])?v_c[face[j]]:white) ;
//        }
//    }
//}

void ModelAndView::drawAll(TGAImage& image ,vector<TGAColor> v_c,vector<TGAColor> f_c,Vec3f light_dir)
{

    z_buffer = new float[image.get_width()*image.get_height()] ;
    for(int i = image.get_width()*image.get_height();i--;z_buffer[i] = std::numeric_limits<float>::min()) ;

    srand(time(NULL) ) ;
    int size = getFacesSize() ;
    for(int i = 0; i< size;i++)
    {
        std::vector<int> face = getFace(i) ;
        //使用原始世界坐标
        isnormal = false ;
        vector<Vec3i> t4 ;
        Vec3f intensity;
        vector<Vec3f> norms = getFaceVectexNorm(i) ;

        for(int i = 0; i< 3;i++)
        {
            t4.push_back(normal_v[face[i]]);
            intensity[i] = norms[i]*light_dir ;
        }


//        Vec3f n = cross((vertexs[face[2]]-vertexs[face[0]]),(vertexs[face[1]]-vertexs[face[0]]) );
//        n.normalize() ;
//        float intensity = n*light_dir ;





//        if(intensity[0]>0)
//        {
            vector<Vec2i> T_Texts  = getFaceVertexTexturePosition(i);
//            for(int i = 3;i--;)
//            {
//                T_Texts[i] = multiply(T_Texts[i],intensity) ;
//            }

            int index3[3] = {0,1,2};
            Triangle d(index3) ;
            d.draw_vec3i(image,z_buffer, t4,T_Texts,intensity,text ) ;
//        }



    }

}
void ModelAndView::normal(int height,int width,Vec3f center,Vec3f eye,Vec3f up)
{
    isnormal = true ;
    for(int i = 0; i<vertexs.size();i++)
    {
        Vec3i temp ;
        temp[0] = vertexs[i][0] ;
        temp[1] = vertexs[i][1] ;
        temp[2] = vertexs[i][2] ;
        normal_v.push_back(temp) ;
     }
    normalVertexs(vertexs,normal_v,height,width,camera,eye,center,up) ;
}

void ModelAndView::addTexture(string path)
{
    text.read_tga_file(path.c_str()) ;
    text.flip_vertically();
    T_width = text.get_width() ;
    T_height = text.get_height() ;
    useTexture = true ;

}
TGAColor ModelAndView::getTextureColor(Vec2i point )
{
    Vec2i p ;
    p[0] = point[0]*T_width ;
    p[1] = point[1]*T_height ;

    return text.get(p[0],p[1]) ;
}

vector<Vec2i> ModelAndView::getFaceVertexTexturePosition(int face_i )
{
    assert(face_i<getFacesSize()) ;
    vector<int> idx_v = getFaceText(face_i) ;
    vector<Vec2i> result  ;
    for(int i = 0; i <3 ;i++)
    {
        Vec2i temp = Vec2i(Texs[idx_v[i]][0]*text.get_width(),Texs[idx_v[i]][1]*text.get_height()) ;
        result.push_back(temp) ;
    }
    return result ;
}

vector<Vec3f> ModelAndView::getFaceVectexNorm(int face_i)
{
    assert(face_i<getFacesSize()) ;
    vector<int> idx_v = getFaceVertexNormIndex(face_i);
    vector<Vec3f> norms ;
    for(int i =0 ;i <3 ;i++)
    {
        Vec3f temp = normal_vector_read[idx_v[i]] ;
        norms.push_back(temp.normalize()) ;
    }
    return norms;
}

void ModelAndView::setcamera(Vec3f camera)
{
    this->camera = camera ;
}

