#include <QApplication>
#include<gnss_signal.h>
#include<plot_window.h>
#include<string>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    GNSS_Signal *new_s = new GNSS_Signal();
    double step = 0.1;   //此处赋值无用，step步长取决于采样频率
    double t = 0.001;
    QVector<double> qb=new_s->GPS_single_signal(3,t,step,100);

//    QVector<Complex> qv=FFT(qb);

//    double *dd=new double[qb.size()];
//    int i=0;
//    for(i=0;i<qb.size();i++)
//    {
//       dd[i]=qb[i];
//        dd[i]=qv[i].amp();
//    }
//    qDebug()<<dd[0];
//    qDebug()<<qb.size();
    int length_t = t/step;
    QVector<double> t_vector(length_t);
    for(int i=0;i<t/step;i++){
        t_vector[i] = i*step;
    }

    plot_window w("CA码","时间","signal",
                  static_cast<QVector<double>>(t_vector),static_cast<QVector<double>>(qb),
                  nullptr);
    w.show();
//    delete[] dd;
    return a.exec();
}
