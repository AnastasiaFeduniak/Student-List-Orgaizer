#ifndef CHARTVIEW_H
#define CHARTVIEW_H
#include "student.h"
#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QVector>
#include <QPointF>
#include <QGraphicsLineItem>
#include <QGraphicsTextItem>
#include <QtCharts/QChartView>
#include <QtCharts/QAreaSeries>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QHorizontalStackedBarSeries>
#include <QtCharts/QLineSeries>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QtCharts/QChart>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>
//#include <QtCharts/QCategoryAxis>
#include <QtCharts/QBarCategoryAxis>
namespace Ui {
class ChartView;
}

class ChartView : public QWidget
{
    Q_OBJECT

public:
    explicit ChartView(QWidget *parent = nullptr);
    ~ChartView();
     QLineSeries* series ;
 //   void setData(const vector<>);
public slots:
     void getStudentChart(vector<Student>);
private:
    Ui::ChartView *ui;

  //  void populateData();
    void drawLineDiagram();
};

#endif // CHARTVIEW_H
