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
enum FilterSelection { Any, KeyType, Room, CurrentHolder, StorageLocation };
FilterSelection from_qstring(QString qs);
enum HeaderSortState { None, Ascending, Descending };
class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();
private slots:
  void onHeaderClicked(int logicalIndex);

  void on_main_pushButton_clicked();

  void on_main_addPermissionGroup_clicked();

  void on_main_filterButton_clicked();

  void on_main_pushButtonClearSearch_clicked();

private:
  HeaderSortState header_sort_state;
  int last_sorted_header;
  Ui::MainWindow *ui;
  DBHandle db;
  CSqlRelationalTableModel *model;
  void setup_search_combobox();
  FilterSelection from_qstring(QString);
};

#endif // MAINWINDOW_H