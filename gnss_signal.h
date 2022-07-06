#ifndef GNSS_SIGNAL_H
#define GNSS_SIGNAL_H

#include<QVector>
#include<QDebug>
#include<cmath>
#include "math_operation.h"
class GNSS_Signal
{
public:

    double f0=1.023e7;
    GNSS_Signal();
    QVector<QVector<bool>> G1;
    QVector<QVector<bool>> G2;
    int LEN;
    QVector<QVector<int>> PRN_SLC;

    QVector<QVector<bool>> CA_G1(int length); //生成G1码
    QVector<QVector<bool>> CA_G2(int length);
    QVector<bool> CA(int PRN);
    void carrier(double c_freq,double amp,double phi,double xstep,int length);
    QVector<double> cff(int PRN1,int PRN2);  //计算相关系数
    QVector<double> GPS_single_signal(int PRN,double t,double &step,double CN);
    //PRN表示卫星号，CN表示载噪比
    double Anoise(double CN);
    double Pass_time(QVector<double> p_rfr,QVector<double> v,QVector<double> p_u);
    double Doppler(vec3 P1,vec3 Pr,vec3 v1,vec3 vr,double freq);
    //Doppler计算多普勒频移，P1,v1表示卫星位置和速度向量，Pr和vr表示接收机,freq表示载波频率


private:
    double c_light=3e8;     //光速
    double WIF=4.309e6;        //模拟中频信号
    double W_sample=5.714e6;   //采样频率
    double amp_s=1;        //载波幅值
    QVector<double> car;  //载波
    double Td=0;  //信号传输延时
    double dtd=0;   //接收机相对卫星时钟偏差，超前为正
    double Wd=0;      //多普勒频移——角频率
};

#endif // GNSS_SIGNAL_H
