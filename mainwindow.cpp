#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMessageBox>
#include <errhandlingapi.h>
#include <QFile>
#include <QTextStream>
#include <QFileDialog>
#include <fstream>
#include <queue>
vector<Student> StudentList;
fstream logF;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Student database");
    QPixmap gold("E:\\PureDoc_2\\DocPure_2\\images\\gold.png");
    ui->gold_img->setPixmap(gold);
    QPixmap silver("E:\\PureDoc_2\\DocPure_2\\images\\silver.png");
    ui->silver_img->setPixmap(silver);
    QPixmap bronze("E:\\PureDoc_2\\DocPure_2\\images\\bronze.png");
    ui->bronze_img->setPixmap(bronze);
    logF.open("E:\\PureDoc_2\\DocPure_2\\Log.txt", ios::out | ios::trunc);;
    nsf = new NewStudentFormWindow(this);
    connect(nsf, &NewStudentFormWindow::returnStudent, this, &MainWindow::getStudent);

    cv = new ChartView(0);
    connect(cv, &ChartView::getStudentChart, this, &MainWindow::getStudentChart);

    ui->StudentView->setContextMenuPolicy(Qt::CustomContextMenu);
    contextMenu = new QMenu(this);
    deleteStudentAct = new QAction("Delete", this);
    showDiagramAct = new QAction("Show success diagram", this);
    contextMenu->addAction(deleteStudentAct);
    contextMenu->addAction(showDiagramAct);

    connect(ui->StudentView, &QTableWidget::customContextMenuRequested, this, &MainWindow::showContextMenu);
    connect(deleteStudentAct, &QAction::triggered, this, &MainWindow::deleteStudent);
       connect(showDiagramAct, &QAction::triggered, this, &MainWindow::showDiagram);

    logF << "Program is opened" << endl << endl;

}

void writeListInLog(vector<Student> a){
       for(int i = 0; i < a.size(); i++){
           logF << a[i].getSurname() << a[i].getName() << a[i].getCathedra() << a[i].getGroup() <<\
            a[i].getAvgMark() << a[i].getSemester() << a[i].getYear() << endl;
       }
       logF << endl;
}
//видалення студента зі списку
void MainWindow::deleteStudent(){
       logF << "Deleting student" << endl << endl;
       logF << StudentList[rightClickedRow].getSurname() << StudentList[rightClickedRow].getName() << StudentList[rightClickedRow].getCathedra() << StudentList[rightClickedRow].getGroup() <<\
       StudentList[rightClickedRow].getAvgMark() << StudentList[rightClickedRow].getSemester() << StudentList[rightClickedRow].getYear() << endl;
       StudentList.erase(StudentList.begin() + rightClickedRow);
           on_SeeFullList_clicked();
}


//запис усіх наявних записів про вибраного студента та переправлення їх до вікна з графіком
void MainWindow::showDiagram(){
       string name = ui->StudentView->item(rightClickedRow, 1)->text().toStdString();
       string surname = ui->StudentView->item(rightClickedRow, 0)->text().toStdString();
       vector<Student> it;
       std::copy_if(StudentList.begin(), StudentList.end(), std::back_inserter(it),
                    [name, surname](const Student& student) {
                        return student.getName() == name && student.getSurname() == surname;
                    });
       cv->getStudentChart(it);
          cv->show();
       logF << "Show Diagram for" << name << " " << surname << endl << endl;
}

MainWindow::~MainWindow()
{
    logF << "Closing Window" << endl << endl;
    logF.close();
    delete ui;
}


//додавання студента
void MainWindow::on_AddStudent_clicked()
{
    nsf->show();
    logF << "Add student window is opened" << endl << endl;

}

//отримання та запис інформації про новоствореного студента
void MainWindow::getStudent(Student received){
    StudentList.push_back(received);
    logF << "New Student added" << endl << endl;
    logF << received.getSurname() << received.getName() << received.getCathedra() << received.getGroup() <<\
   received.getAvgMark() << received.getSemester() << received.getYear() << endl << endl;

}

//оновлення таблиці
void MainWindow::on_SeeFullList_clicked()
{
    setTable(StudentList);
    logF << "Show full list" << endl << endl;
    writeListInLog(StudentList);

}

//вивід таблиці
void MainWindow::setTable(vector<Student> a){
     ui->StudentView->setRowCount(a.size());
     for (int i = 0; i < a.size(); i++) {
         ui->StudentView->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(a[i].getSurname())));
         ui->StudentView->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(a[i].getName())));
         ui->StudentView->setItem(i, 2, new QTableWidgetItem(QString::fromStdString(a[i].getCathedra())));
         ui->StudentView->setItem(i, 3, new QTableWidgetItem(QString::fromStdString(a[i].getGroup())));
         ui->StudentView->setItem(i, 4, new QTableWidgetItem(QString::number(a[i].getAvgMark())));
         ui->StudentView->setItem(i, 5, new QTableWidgetItem(QString::number(a[i].getSemester())));
         ui->StudentView->setItem(i, 6, new QTableWidgetItem(QString::number(a[i].getYear())));
     }
}

//створення списків успішності, відобреження найкращих та найгірших років, та трьох найкращих студентів
void MainWindow::on_BestRanking_clicked()
{
     logF << "Success grading" << endl << endl;
     //знаходження всіх років про які є запис
     if(!StudentList.empty()){
     vector<int> years;
     for (Student tmp : StudentList) {
         int year = tmp.getYear();
         if (::find(years.begin(), years.end(), year) == years.end()) {
             years.push_back(year);
         }
     }

     int maxYear = years[0];
     int minYear = years[0];
     double maxAvgMark = calculateAverageMarkForYear(maxYear);
     double minAvgMark = maxAvgMark;

     //знаходження найбільшого та найменшого середнього балу
     for (int year : years) {
         double avgMark = calculateAverageMarkForYear(year);
         if (avgMark > maxAvgMark) {
             maxAvgMark = avgMark;
             maxYear = year;
         } else if (avgMark < minAvgMark) {
             minAvgMark = avgMark;
             minYear = year;
         }
     }
     ui->BestYear->setText(QString::number(maxYear));
     ui->WorstYear->setText(QString::number(minYear));

     logF << "Best Year: "<< maxYear << endl << "Worst Year: " << minYear << endl;

     //створення масиву з тільки одним записом про кожного студента
     vector<Student> students;
     int check = false;
     for (Student tmp : StudentList) {
         string name = tmp.getName();
         string surname = tmp.getSurname();
         for(Student temp : students){
             if(temp.getSurname() == tmp.getSurname() && temp.getName() == tmp.getName()){
                 check = true;
                 break;
                 //students.push_back(temp);
             }
         }
         if(check == false){
             students.push_back(tmp);
         }
         check = false;
     }
     //обчислення середнього балу
     for(Student temp : students){
         temp.setAvgMark(calculateAverageMarkForStudent(temp.getName(), temp.getSurname()));
     }


     // сортування масиву
     std::sort(students.begin(), students.end(), [](const Student& a, const Student& b) {
         return a.getAvgMark() > b.getAvgMark(); // Change to '<' for ascending order
     });



     ui->Top1->setText(QString::fromStdString(students[0].getSurname()) + " " + QString::fromStdString(students[0].getName()));
     ui->Top2->setText(QString::fromStdString(students[1].getSurname()) + " " + QString::fromStdString(students[1].getName()));
     ui->Top3->setText(QString::fromStdString(students[2].getSurname()) + " " + QString::fromStdString(students[2].getName()));

     logF << "1. " << students[0].getSurname() << " " << students[0].getName() << endl;
     logF << "2. " << students[1].getSurname() << " " << students[1].getName() << endl;
     logF << "3. " << students[2].getSurname() << " " << students[2].getName() << endl << endl;

     } else {
     QMessageBox::warning(this, "Warning", "List is empty!");
     logF  << "List is empty" << endl << endl;
     }
}

//обчислення серерднього балу для якогось конкретного року
double MainWindow::calculateAverageMarkForYear(int year) {
     double totalMarks = 0;
     int count = 0;

     for (Student tmp : StudentList) {
         if (tmp.getYear() == year) {
             totalMarks += tmp.getAvgMark();
             count++;
         }
     }

     return (count > 0) ? (totalMarks / count) : 0.0;
}

double MainWindow::calculateAverageMarkForStudent(string name, string surname) {
     double totalMarks = 0;
     int count = 0;

     for (Student tmp : StudentList) {
         if (tmp.getName() == name && tmp.getSurname() == surname) {
             totalMarks += tmp.getAvgMark();
             count++;
         }
     }

     return (count > 0) ? (totalMarks / count) : 0.0;
}

//сортування списку за алгоритмом шелла в конкретному році та семестрі, якщо додатковим параметром виступає діапазон оцінок: просто відображається відфільтрований список
void MainWindow::on_ShellSort_clicked()
{
     logF << "Filtered show" << endl;
     if(!StudentList.empty()){
      ui->StudentView->clear();
     bool isRanged = false;
      int year = ui->ShellEnterYear->text().toInt();
     int sem = ui->ShellEnterSem->text().toInt();
      double markBegin = ui->RangeMarkBegin->text().toDouble();
      double markEnd = ui->RangeMarkEnd->text().toDouble();

      ui->RangeMarkBegin->clear();
      ui->RangeMarkEnd->clear();
      ui->ShellEnterSem->clear();
      ui->ShellEnterYear->clear();

         isRanged = (markBegin != NULL && markEnd != NULL)? true : false;
      logF << ((isRanged) ? "by semester, year and mark": "by year and semester, sorted") << endl << endl;
        //створення масиву тільки з значеннями що відповідають вмогам
        static vector<Student> filtered;
     for (Student tmp : StudentList) {
         if (tmp.getYear() == year && tmp.getSemester() == sem) {
             if(isRanged){
                 if(tmp.getAvgMark() >= markBegin && tmp.getAvgMark() <= markEnd){
                     filtered.push_back(tmp);
                 }
             } else {
                 filtered.push_back(tmp);
         }
         }
     }
     //якщо поля з діапазоном балів пусті то сортуємо список
     if(!isRanged){
         for (int s = filtered.size() / 2; s > 0; s /= 2) {
             for (int i = s; i < filtered.size(); i++) {
                 Student temp = filtered[i];
                 int j;
                 for (j = i; j >= s && filtered[j - s].getAvgMark() < temp.getAvgMark(); j -= s) {
                     filtered[j] = filtered[j - s];
                 }
                 filtered[j] = temp;
             }
         }
     }
     setTable(filtered);
     writeListInLog(filtered);
     filtered.clear();} else {
     QMessageBox::warning(this, "Warning", "List is empty!");
          logF  << "List is empty" << endl << endl;
     }
}

//знаходження найкращої групи за середнім бало в конкретному році
void MainWindow::on_BestGroup_clicked()
{
     logF <<"Find best group of certain year" << endl << endl;
     //визначення усіх груп про які є записи
     if(!StudentList.empty()){
     int year = ui->EnterYearGroup->text().toInt();
     map<string, double> groupAvgMarks;
     for (Student tmp : StudentList)
     {
         if (tmp.getYear() == year)
         {
            if (groupAvgMarks.find(tmp.getGroup()) == groupAvgMarks.end())
             {
                 groupAvgMarks[tmp.getGroup()] = 0.0;
             }
             groupAvgMarks[tmp.getGroup()] += tmp.getAvgMark();
         }
     }
     string bestGroup;
     double highestAvgMark = 0.0;

     for (auto pair : groupAvgMarks)
     {
         if (pair.second > highestAvgMark)
         {
             highestAvgMark = pair.second;
             bestGroup = pair.first;
         }
     }
     ui->ShowBestGroup->setText(QString::fromStdString(bestGroup));
     logF << "The best group of year " << year << " is " << bestGroup << endl << endl;
     } else {
     QMessageBox::warning(this, "Warning", "List is empty!");
          logF  << "List is empty" << endl << endl;
     }
}


//функція зчитування інформації про список з файлу
void MainWindow::on_ReadList_clicked()
{
     logF << "Read from list" << endl << endl;
     StudentList.clear();
     QString filePath = QFileDialog::getOpenFileName(this, "Open File", "", "Text Files (*.txt);;All Files (*)");

     ifstream fs;
     fs.open(filePath.toStdString());
     if(fs.is_open()){
         Student student;

         while (fs >> student)
         {
             StudentList.push_back(student);
         }
         fs.close();
         QMessageBox::information(this, "Result" ,"The list has been read!");
         logF << "The list has been read" << endl << endl;
     } else {
         QMessageBox::critical(this, "Result" ,"An error occurred while reading");
         logF << "An error occurred while reading" << endl << endl;
     }
}

//збереження інформації про поточний список в файл
void MainWindow::on_WriteList_clicked()
{
     logF << "Write list in file" << endl << endl;
     if(!StudentList.empty()){
         QMessageBox::warning(this,"Warning!", "If file wasn't empty previous data will be deleted!");
         QString filePath = QFileDialog::getOpenFileName(this, "Open File", "", "Text Files (*.txt);;All Files (*)");
     ofstream fs(filePath.toStdString(), ios::out | ios::trunc);
     if(fs.is_open()){
             for (int i = 0; i < StudentList.size(); i++)
         {
             fs << StudentList[i];
         }
         fs.close();
          QMessageBox::information(this, "Result" ,"The list is recorded!");
          logF << "The list is recorded" << endl << endl;
     } else{
          QMessageBox::critical(this, "Result" ,"An error occurred while writing");
          logF << "An error occurred while writing" << endl << endl;
     }} else {
     QMessageBox::warning(this, "Warning", "List is empty!");
     }
}

//відобрежння контекстного списку в таблиці
void MainWindow::showContextMenu(const QPoint &pos)
{
     rightClickedRow = ui->StudentView->indexAt(pos).row();
     ui->StudentView->selectRow(rightClickedRow);
     contextMenu->exec(ui->StudentView->mapToGlobal(pos));
}


void MainWindow::on_ClearList_clicked()
{
     StudentList.clear();
     on_SeeFullList_clicked();
     ui->BestYear->setText("?");
     ui->WorstYear->setText("?");
     ui->Top1->setText("?");
     ui->Top2->setText("?");
     ui->Top3->setText("?");
     ui->ShowBestGroup->setText("?");
     logF << "Clear List" << endl << endl;
}

