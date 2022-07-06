#ifndef TRACE_INIT_H
#define TRACE_INIT_H

#include<math_operation.h>

class trace_init
{
public:
    int LEN=3000;


    trace_init();
    QVector<double> trace_target(double step,QVector<double> P0,double vlimit);
};

#endif // TRACE_INIT_H
