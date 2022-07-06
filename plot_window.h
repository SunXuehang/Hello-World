#ifndef PLOT_WINDOW_H
#define PLOT_WINDOW_H

#include <QMainWindow>
#include<chart.h>
#include<chartview.h>
#include<algorithm>
#include<QLineSeries>
#include<QValueAxis>

namespace Ui {
class plot_window;
}

class plot_window : public QMainWindow
{
    Q_OBJECT

public:
    explicit plot_window(QWidget *parent = nullptr);
    explicit plot_window(QString,QString,QString,QVector<double>,QVector<double>,QWidget *parent);
    ~plot_window();

    void createChart();
    void prepareDate();
    void updateChart();
    QVector<double> x;
    QVector<double> y;
    QString ChartTitle;
    QString XTitle;
    QString YTitle;

private:
    Ui::plot_window *ui;

};

#endif // PLOT_WINDOW_H
