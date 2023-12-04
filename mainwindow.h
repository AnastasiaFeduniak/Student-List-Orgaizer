#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "chartview.h"
#include "newstudentformwindow.h"
#include <vector>
#include <QPixmap>
#include <algorithm>
#include <QMainWindow>
#include <QMenu>
#include <QTableWidget>
//#include <QtCharts>
//#include <QChartView>
//#include <>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
  //  void on_SearchButton_clicked();
    void on_AddStudent_clicked();
    void setTable(vector<Student> a);
    void on_SeeFullList_clicked();
    double calculateAverageMarkForYear(int year);
    void on_BestRanking_clicked();
    void on_ShellSort_clicked();

    void on_BestGroup_clicked();

    void on_ReadList_clicked();

    void on_WriteList_clicked();

    void deleteStudent();
    void showDiagram();

    double calculateAverageMarkForStudent(string name, string surname);

    void on_ClearList_clicked();

public slots:
    void getStudent(Student received);
private:
    Ui::MainWindow *ui;
    NewStudentFormWindow *nsf;
    ChartView *cv;
    QMenu *contextMenu;
    QAction *deleteStudentAct;
    QAction *showDiagramAct;
    void showContextMenu(const QPoint &pos);
    int rightClickedRow;
signals:
    void getStudentChart(vector<Student>);
};
#endif // MAINWINDOW_H
