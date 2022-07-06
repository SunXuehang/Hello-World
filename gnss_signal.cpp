#include "gnss_signal.h"

GNSS_Signal::GNSS_Signal()
{
    this->LEN=1023;
    this->G1=CA_G1(1023);
    this->G2=CA_G2(1023);
    PRN_SLC={
        {2,6},
        {3,7},
        {4,8},
        {5,9},
        {1,9},
        {2,10},
        {1,8},
        {2,9},
        {3,10},
        {2,3},
        {3,4},
        {5,6},
        {6,7},
        {7,8},
        {8,9},
        {9,10},
        {1,4},
        {2,5},
        {3,6},
        {4,7},
        {5,8},
        {6,9},
        {1,3},
        {4,6},
        {5,7},
        {6,8},
        {7,9},
        {8,10},
        {1,6},
        {2,7},
        {3,8},
        {4,9}

    };

}

QVector<QVector<bool>> GNSS_Signal::CA_G1(int length)
{
// CA码中G1发生器生成函数
    QVector<QVector<bool>> vans(length,QVector<bool>(10,1));

    int i=0;
    int j=0;
    for(i=1;i<length;i++)
    {

        for(j=1;j<10;j++)
        {
            vans[i][j]=vans[i-1][j-1];
        }
        vans[i][0]=vans[i-1][2]^vans[i-1][9];
    }
    return vans;
}

QVector<QVector<bool> > GNSS_Signal::CA_G2(int length)
{
    // CA码中G2发生器生成函数
    QVector<QVector<bool>> vans(length,QVector<bool>(10,1));

    int i=0;
    int j=0;
    for(i=1;i<length;i++)
    {
        for(j=1;j<10;j++)
        {
            vans[i][j]=vans[i-1][j-1];
        }
        vans[i][0]=vans[i-1][1]^vans[i-1][2]^vans[i-1][5]^vans[i-1][7]^vans[i-1][8]^vans[i-1][9];
    }
    return vans;
}

QVector<bool> GNSS_Signal::CA(int PRN)
{
// 根据PRN号获取对应的CA码
    qDebug()<<"GNSS_Signal::CA";
    int i=0;
    QVector<int> S_PRN=PRN_SLC[PRN-1];
    QVector<bool> ans(LEN,0);
    for(i=0;i<LEN;i++)
    {
        bool G2i=G2[i][S_PRN[0]-1]^G2[i][S_PRN[1]-1];
        ans[i]=G1[i][9]^G2i;
    }
    return ans;

}

void GNSS_Signal::carrier(double c_freq, double amp, double phi, double xstep, int length)
{
    //生成中频信号的载波
    qDebug()<<"GNSS_Signal::carrier";
    double tsi=Td+dtd;
    int i=0;
    car.resize(length);
    for(i=0;i<length;i++)
    {
        car[i]=amp*cos(c_freq*2*pi*(i*xstep-tsi)+phi);
    }

}

QVector<double> GNSS_Signal::cff(int PRN1, int PRN2)
{
    QVector<bool> PCA1=CA(PRN1);
    QVector<bool> PCA2=CA(PRN2);
}

QVector<double> GNSS_Signal::GPS_single_signal(int PRN, double t,double& step,double CN)
{
    qDebug()<<"生成单个卫星信号GNSS_Signal::GPS_single_signal";

    double tsi=Td+dtd;
    step=1/W_sample;
    int len=t/step;
//    qDebug()<<"len:"<<len;
    double CA_t=1e-3;

    carrier(WIF,1,0,step,len);
    QVector<double> ans(len,0);
    QVector<bool> CA_P=CA(PRN);
    int i=0;
    double Ndb=Anoise(CN);
    for(i=0;i<len;i++)
    {
        double tn=i*step-tsi;
        while(tn<0)
            tn+=CA_t;
        int zheng=tn/CA_t;
        int MaPian=(tn-zheng*CA_t)/CA_t*1023;
        if(CA_P[MaPian])
        {
            ans[i]=car[i];
        }
        else
        {
            ans[i]=-car[i];
        }
        ans[i]+=gauss_rand(0,1)*Ndb;
    }
    return ans;

}

double GNSS_Signal::Anoise(double CN)
{
    //根据载噪比计算噪声幅值
    double tmp=10*log10(amp_s*amp_s*W_sample/4);
//    qDebug()<<"noise:"<<tmp;
    double Ndb=tmp-CN;
    if(Ndb<0)
        return 0;
    return Ndb;

}

double GNSS_Signal::Pass_time(QVector<double> p_rfr, QVector<double> v, QVector<double> p_u)
{
    //计算信号传播时间
    int i=0;
    double Tp=Distance(p_rfr,p_u)/c_light;

    for(i=0;i<100;i++)
    {
        double xtfr=p_rfr[0]-v[0]*Tp;
        double ytfr=p_rfr[1]-v[1]*Tp;
        double ztfr=p_rfr[2]-v[2]*Tp;
        QVector<double> p_tfr={xtfr,ytfr,ztfr};
        double Tpp=Distance(p_tfr,p_u)/c_light;
        if(abs(Tp-Tpp)<1e-10)
        {
            break;
        }
        Tp=Tpp;
    }
    return Tp;
}

double GNSS_Signal::Doppler(vec3 P1, vec3 Pr, vec3 v1, vec3 vr,double freq)
{
    //计算多普勒频移
    vec3 cha=P1-Pr;
    vec3 vI=cha.norm();
    double uup=(vr-v1)*vI;
    double lamda=c_light/freq;
    return uup/lamda;
}


