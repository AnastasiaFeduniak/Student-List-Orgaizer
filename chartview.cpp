#include "chartview.h"
#include "ui_chartview.h"
#include <QMessageBox>
multimap<double, double> marks;
ChartView::ChartView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChartView)
{
        ui->setupUi(this);
  //  connect(this, &ChartView::getStudentChart, this, &ChartView::signalStudent);
        series = new QLineSeries();

}

ChartView::~ChartView()
{
    delete ui;
}

void ChartView::getStudentChart(vector<Student> a){
    series = new QLineSeries();

    this->setWindowTitle((a[0].getName() + " " + a[0].getSurname()).c_str());
    std::sort(a.begin(), a.end(),
              [](const Student &a, const Student &b) {
                 if (a.getYear() == b.getYear()) {
            return a.getSemester() > b.getSemester();
                  }
              return a.getYear() < b.getYear();
              });
    for(int i = 0; i < a.size(); i++){
        series->append((a[i].getSemester() == 1) ? (double)a[i].getYear() + 0.5 : (double)a[i].getYear(), a[i].getAvgMark());
    }
  QChart*chart = new QChart();
    chart->legend()->hide();
    chart->addSeries(series);
    chart->setTitle(QString::fromStdString(a[0].getName() + " " + a[0].getSurname() + "'s diagram of academic results"));

    QValueAxis *axisX = new QValueAxis;
    QValueAxis *axisY = new QValueAxis;

    axisX->setTitleText("Year");
    axisY->setTitleText("Point");

    axisY->setGridLineVisible(true);
     axisX->setGridLineVisible(true);

    chart->addAxis(axisX, Qt::AlignBottom);
    chart->addAxis(axisY, Qt::AlignLeft);

    series->attachAxis(axisX);
    series->attachAxis(axisY);


    QChartView* chartview = new QChartView(chart);
    chartview->setRenderHint(QPainter::Antialiasing);

     ui->showDiagram->resize(800, 600);
    chartview->setParent(ui->showDiagram);}

