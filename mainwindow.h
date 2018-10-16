#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "addkey.h"
#include "createpermissiongroup.h"
#include "csqlrelationaltablemodel.h"
#include "dbhandle.h"
#include <QMainWindow>
#include <iostream>
namespace Ui {
class MainWindow;
}

enum HeaderSortState { None, Ascending, Descending };
class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();
private slots:
  void on_header_clicked(int logicalIndex);

  void on_main_pushButton_clicked();

  void on_main_addPermissionGroup_clicked();

private:
  HeaderSortState header_sort_state;
  int last_sorted_header;
  Ui::MainWindow *ui;
  DBHandle db;
};

#endif // MAINWINDOW_H
