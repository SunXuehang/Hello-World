#include "trace_init.h"

trace_init::trace_init()
{

}

QVector<double> trace_init::trace_target(double step, QVector<double> P0, double vlimit)
{
    QTime randtime=QTime::currentTime();
    qsrand(randtime.msec()+randtime.second()*1000);

    int i=0;
    for(i=0;i<LEN;i++)
    {
        int rand_num=qrand()%1000;
        double frand_num=double(rand_num)/1000;

    }


}
