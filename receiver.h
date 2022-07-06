#ifndef RECEIVER_H
#define RECEIVER_H

#include<math_operation.h>
#include<gnss_signal.h>
class Receiver
{
public:
    Receiver();
    QVector<double> Catch(QVector<double> sign,int type);
};

#endif // RECEIVER_H
