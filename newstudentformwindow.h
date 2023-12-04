#ifndef NEWSTUDENTFORMWINDOW_H
#define NEWSTUDENTFORMWINDOW_H
#include "student.h"
#include <QWidget>
#include <QMainWindow>
//vector<Student> StudentList;
namespace Ui {
class NewStudentFormWindow;
}

class NewStudentFormWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit NewStudentFormWindow(QWidget *parent = nullptr);
    ~NewStudentFormWindow();

private slots:
    void on_CreateStudent_clicked();

private:
    Ui::NewStudentFormWindow *ui;
signals:
    void returnStudent(Student result);
};

#endif // NEWSTUDENTFORMWINDOW_H
