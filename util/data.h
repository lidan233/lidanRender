//
// Created by 李源 on 2019-11-22.
//

#ifndef TINYRENDER_DATA_H
#define TINYRENDER_DATA_H
#include <math.h>
#include <iostream>
#include <assert.h>
#include <vector>



template<size_t DimCols ,size_t DimRows,typename T> class mat ;

template<size_t DIM,typename T> struct vec
{
private:
    T data_[DIM] ;
public:
    vec(){
        for(size_t i = DIM ;i--;data_[i]=T() ) ;
    }
    T& operator[](const size_t i ){ assert(i<DIM); return data_[DIM] ;}
    const T& operator[](const size_t i) const{assert (i<DIM); return data_[i] ;}
};

template<size_t DIM,typename T> T operator*(const vec<DIM,T>& lhs,const vec<DIM,T>& lhs)
{
    T ret = T() ;
    for(size_t i = DIM)
}
template<class t> struct Vec2
{
    union {
        struct {t u,v ;} ;
        struct {t x,y ;} ;
        t raw[2];

    };
    Vec2():u(0),v(0) {}
    Vec2(t _u,t _v):u(_u),v(_v) {}
    inline Vec2<t> operator+(const Vec2<t>& ano){return Vec2<t>(u+ano.u,v+ano.v) ;}
    inline Vec2<t> operator-(const Vec2<t>& ano){return Vec2<t>(u-ano.u,v-ano.v) ;}
    inline Vec2<t> operator*(float f){ return Vec2<t>(u*f,v*f) ;}
    template<class> friend std::ostream& operator<<(std::ostream& s,Vec2<t> &v) ;
    inline t& operator[](int i)
    {
        return raw[i] ;
    }
};

template<class t> struct Vec3
{
    union {
        struct {t u,v,c ;} ;
        struct {t ivert, iuv, inorm;} ;
        t raw[3] ;
    };

    Vec3():u(0),v(0),c(0){}
    Vec3(t _u,t _v ,t _c):u(_u) ,v(_v),c(_c) {}
    inline Vec3<t> operator+(const Vec3& ano) const { return Vec3<t>(ano.u+u,ano.v+v,ano.c+c) ; }
    inline t operator[](const int i) const{
        if(i==0) return u ;
        else if(i==1) return v  ;
        return c ;
    }
    inline Vec3<t> operator-(const Vec3& ano)const { return Vec3<t>(u-ano.u,v-ano.v,c-ano.c) ;}
//    inline Vec3<t> operator*(const Vec3& ano){ return Vec3<t>(u*ano.u,v*ano.v,c*ano.c) ;}
    inline float operator*(const Vec3& ano) const { return u*ano.u+v*ano.v+c*ano.c  ;}
    inline Vec3<t> operator*(float f ) const { return Vec3<t>(u*f,v*f,c*f) ;}
    inline Vec3<t> operator^(const Vec3& ano )const
            { return  Vec3<t>(v*ano.c-ano.v*c,-u*ano.c+ano.u*c,u*ano.v-ano.u*v) ;}



    template<class> friend std::ostream& operator<<(std::ostream& s,Vec3<t> &v) ;


    float norm()const{return sqrt(u*u+v*v+c*c) ;}
    Vec3<t>& normalize(t l=1 ){*(this) = *(this)*(l/norm()) ;return *this ;}


};


typedef Vec2<float> Vec2f ;
typedef Vec2<int> Vec2i ;
typedef Vec3<float> Vec3f ;
typedef Vec3<int> Vec3i  ;


template <class t>  std::ostream& operator<<(std::ostream& s,Vec2<t> &v)
{
    s<< "("<<v.u<<","<<v.v <<")"<<std::endl ;
}


template <class t>  std::ostream& operator<<(std::ostream& s,Vec3<t> &v)
{
    s<< "("<<v.u<<","<<v.v <<","<<v.c<<")"<<std::endl ;
}



#endif //TINYRENDER_DATA_H
