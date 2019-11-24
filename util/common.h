//
// Created by 李源 on 2019-11-22.
//

#ifndef COMMON
#define COMMON


#include <string>
#include <vector>
#include <functional>
#include <sstream>
#include <iostream>
#include <iomanip>


#include "../module/tgaimage.h"
#include "../geom/triangle.h"

#include <tuple>

using namespace std;


const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red   = TGAColor(255, 0,   0,   255);
const TGAColor green = TGAColor(0,255,0,255) ;
const TGAColor blue = TGAColor(0,0,255,255) ;


const TGAColor colors[] = {white,red,green,blue};



inline string ltrim(string data) {
    string::iterator p = find_if(data.begin(), data.end(), not1(ptr_fun<int, int>(isspace)));
    data.erase(data.begin(), p);
    return data;
}

inline string rtrim(string data)
{
    string::reverse_iterator p = find_if(data.rbegin(),data.rend(),not1(ptr_fun<int,int>(isspace))) ;
    data.erase(p.base(),data.end()) ;
    return data ;
}

inline string trim(string data)
{
    return ltrim(rtrim(data)) ;
}

inline vector<string> getstringObj(string data )
{
    vector<string> result ;
    data = trim(data) ;
    stringstream ss ;
    ss<<data.c_str()[0] ;
    result.push_back(ss.str()) ;
    ss.str("") ;

    for(int i = 1; i<data.size();i++)
    {
        while(data.c_str()[i]==' '||data.c_str()[i]=='\t'){i++ ;}
        if(data.c_str()[i-1]==' '||data.c_str()[i-1]=='\t')
        {
            string temp = ss.str() ;
            if(ss.str()!="")
                result.push_back(temp) ;
            ss.str("");
        }
        ss<<data.c_str()[i] ;
    }
    result.push_back(ss.str()) ;
    return result ;
}

inline void readObj(const string filename,vector<Vec3f>& verts_,vector<vector<int> >& faces_) {
    std::ifstream in;
    in.open (filename, std::ifstream::in);
    if (in.fail()) return;
    std::string line;
    while (!in.eof()) {
        std::getline(in, line);
        std::istringstream iss(line.c_str());
        char trash;
        if (!line.compare(0, 2, "v ")) {
            iss >> trash;
            Vec3f v;
            for (int i=0;i<3;i++) iss >> v.raw[i];
            verts_.push_back(v);
        } else if (!line.compare(0, 2, "f ")) {
            std::vector<int> f;
            int itrash, idx;
            iss >> trash;
            while (iss >> idx >> trash >> itrash >> trash >> itrash) {
                idx--; // in wavefront obj all indices start at 1, not zero
                f.push_back(idx);
            }
            faces_.push_back(f);
        }
    }
    std::cerr << "# v# " << verts_.size() << " f# "  << faces_.size() << std::endl;
}

inline void normalVertexs(vector<Vec3f>& verts_,int height,int width)
{
    for(int i = 0 ;i < verts_.size();i++)
    {
        verts_[i].raw[0] = int((verts_[i].raw[0]+1)*width/2+0.5) ;
        verts_[i].raw[1] = int((verts_[i].raw[1]+1)*height/2+0.5) ;
    }
}

inline double round(double src,int precise)
{
    stringstream ss ;
    ss<<std::fixed<< setprecision(precise) << src;
    ss>>src ;
    return src ;
}

inline template<typename t> t add_xy(t& a,t& b)
{
    return t(a.getX()+b.getX(),a.getY()+b.getY(),a.raw[2]) ;
}

inline template<typename t> t sub_xy(t& a,t& b)
{
    return t(a.getX()-b.getX(),a.getY()-b.getY(),a.raw[2]) ;
}

inline Vec3f barycentric(vector<Point*> points,Point* p)
{
    Vec3f all_x = Vec3f(points[2]->getX()-points[0]->getX(),
                        points[1]->getX()-points[0]->getX(),
                        points[0]->getX()-p->getX()) ;
    Vec3f all_y = Vec3f(points[2]->getY()-points[0]->getY(),
                        points[1]->getY()-points[0]->getY(),
                        points[0]->getY()-p->getY()) ;
    Vec3f result = all_x^all_y ;

    if(abs(result.raw[2])<1) return Vec3f(-1,1,1) ;
    return Vec3f(1.f-(result.raw[0]+result.raw[1])/result.raw[2],result.raw[0]/result.raw[2],result.raw[0]/result.raw[2]) ;
}
inline std::pair<Vec2i,Vec2i> getMBR(TGAImage& image,int* points_i,vector<Vec3f*> points)
{
    Vec2i xmin(INT16_MAX,INT16_MAX) ;
    Vec2i xmax(0,0) ;
    Vec2i clamp(image.get_width()-1,image.get_height()-1) ;

    for(int i = 0;i<3;i++)
    {
        xmin.raw[0] = std::max(0.0,xmin[0]<points[points_i[i]]->raw[0]?xmin[0]*1.0:points[points_i[i]]->raw[0]) ;
        xmin.raw[1] = std::max(0.0,xmin[1]<points[points_i[i]]->raw[1]?xmin[1]*1.0:points[points_i[i]]->raw[1]) ;
        xmax.raw[0] = std::min((float)clamp[0],std::max((float)xmax[0],points[points_i[i]]->raw[0])) ;
        xmax.raw[1] = std::min((float)clamp[1],std::max((float)xmax[1],points[points_i[i]]->raw[1])) ;
    }


    return make_pair(xmin,xmax) ;
}

#endif