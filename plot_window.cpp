#include "plot_window.h"

#include "ui_plot_window.h"
#include<QDebug>
plot_window::plot_window(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::plot_window)
{
    ui->setupUi(this);
}

plot_window::plot_window(QString Chart_title,QString X_title,QString Y_title,QVector<double> x_temp,QVector<double> y_temp,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::plot_window)
{
    ui->setupUi(this);
    x=x_temp;
    y=y_temp;
    ChartTitle = Chart_title;
    XTitle = X_title;
    YTitle = Y_title;
    createChart();
    prepareDate();
}

plot_window::~plot_window()
{
    delete ui;
}

void plot_window::createChart()
{
    auto min = std::min_element(y.begin(),y.end());//y轴方向的最小值
    auto max = std::max_element(y.begin(),y.end());//y轴方向的最大值
//    qreal y_min = *min;
//    qreal y_max = *max;

    Chart *chart = new Chart;
    chart->setTitle(ChartTitle);
    ui->m_chartView->setChart(chart);
    QFont font = ui->m_chartView->chart()->titleFont();//设置chart title字体大小
    font.setPixelSize(20);
    ui->m_chartView->chart()->setTitleFont(font);
//    ui->m_chartView->setRenderHint(QPainter::Antialiasing);//抗锯齿（会消耗很多计算机资源,降低运算速度）

    QLineSeries *series0 = new QLineSeries;
//    series0->setName("Untitled line");
    ui->m_chartView->chart()->legend()->setVisible(false);

    //设置曲线的属性，宽度，长度
    QPen pen;
    pen.setStyle(Qt::SolidLine);
    pen.setWidth(2);
    pen.setColor(Qt::red);
    series0->setPen(pen);

    chart->addSeries(series0);

    QValueAxis *axisX = new QValueAxis;
    QValueAxis *axisY = new QValueAxis;

    qreal x_begin = x.front(),x_end = x.back();
    axisX->setRange(x_begin,x_end);
//    axisX->setLabelFormat("%.1f");//一位小数
    axisX->setTickCount(11);//设置背景，大间隔
    axisX->setMinorTickCount(4);//小间隔
    axisX->setTitleText(XTitle);

    qreal y_min = *min,y_max = *max;
    axisY->setRange(y_min,y_max);
//    axisX->setLabelFormat("%.1f");//一位小数
    axisY->setTickCount(3);//设置背景，间隔
    axisY->setMinorTickCount(4);
    axisY->setTitleText(YTitle);

    //将坐标轴给chart
    chart->addAxis(axisX,Qt::AlignBottom); //坐标轴添加到图表，并指定方向
    chart->addAxis(axisY,Qt::AlignLeft);
    series0->attachAxis(axisX); //序列 series0 附加坐标轴
    series0->attachAxis(axisY);
}

void plot_window::prepareDate()
{
    QLineSeries *series0 = (QLineSeries *)ui->m_chartView->chart()->series().at(0);
    series0->clear();
    for(int i = 0;i<x.length();i++){
        series0->append(x[i],y[i]);
    }
}

void plot_window::updateChart()
{
    createChart();
    prepareDate();
}


