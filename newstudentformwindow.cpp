#include "newstudentformwindow.h"
#include "ui_newstudentformwindow.h"

NewStudentFormWindow::NewStudentFormWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::NewStudentFormWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("New student form");
}

NewStudentFormWindow::~NewStudentFormWindow()
{
    delete ui;
}

//запис та переправка інформації про нового студента в головне вікно
void NewStudentFormWindow::on_CreateStudent_clicked()
{
    Student temp(ui->EnterSurname->text().toStdString(),
                 ui->EnterName->text().toStdString(),
                 ui->EnterCathedra->text().toStdString(),
                 ui->EnterGroup->text().toStdString(),
                 ui->EnterAvgMark->text().toDouble(),
                 ui->EnterSemester->text().toInt(),
                 ui->EnterYear->text().toInt()
                 );
    emit returnStudent(temp);
    ui->EnterSurname->clear();
    ui->EnterName->clear();
    ui->EnterCathedra->clear();
    ui->EnterGroup->clear();
    ui->EnterSemester->clear();
    ui->EnterAvgMark->clear();
    ui->EnterYear->clear();
    close();
}

