#include "receiver.h"

Receiver::Receiver()
{

}

QVector<double> Receiver::Catch(QVector<double> sign, int type)
{
    //复现载波和CA码
    GNSS_Signal *new_s=new GNSS_Signal();
    double step=0.1;   //此处赋值无用，step步长取决于采样频率
    QVector<double> qb=new_s->GPS_single_signal(3,0.01,step,100);
}
