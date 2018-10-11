#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "dbhandle.h"
#include <iostream>
#include "csqlrelationaltablemodel.h"
#include "addkey.h"
namespace Ui
{
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

  public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
  private slots:



    void on_main_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    DBHandle db;

};

#endif // MAINWINDOW_H
