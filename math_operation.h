#ifndef MATH_OPERATION_H
#define MATH_OPERATION_H

#include<QVector>
#include<QTime>
#include<algorithm>
#include<QDebug>
#include<complex>
#include<Eigen/Geometry>
using namespace Eigen;
#define pi 3.1415926535


class math_operation
{
public:
    math_operation();


};

class Complex
{
public:
    double real;
    double image;
    Complex operator+(Complex& x);
    Complex operator-(Complex& x);
    Complex operator*(Complex& x);
    Complex(double r=0,double i=0);
    double amp();
};


class Point
{
public:
    Point(double x1,double y1,double z1);
    double x;
    double y;
    double z;

    double dist(Point P2);
    Point operator*(double& num);

};

class vec3
{
public:
    vec3(double x1=0,double y1=0,double z1=0);
    double x;
    double y;
    double z;

    double dist(vec3 P2);
    vec3 operator*(double& num);
    double operator*(vec3& v2);
    vec3 operator-(vec3& v2);
    vec3 operator+(vec3& v2);
    vec3 norm(); //返回共线的单位向量
    double len();  //返回向量长度
};




Complex Polar(double amp,double phi);
double uniform_rand(double lowerBndr, double upperBndr);
double gauss_rand(double mean, double sigma);
double Distance(QVector<double>& x,QVector<double>& y);
double Distance(Point& x,Point& y);
QVector<Complex> FFT(QVector<double>& x);
void FFT(QVector<Complex>& x);
#endif // MATH_OPERATION_H
