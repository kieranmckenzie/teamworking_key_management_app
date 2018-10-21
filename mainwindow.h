#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "addkey.h"
#include "createpermissiongroup.h"
#include "csqlrelationaltablemodel.h"
#include "dbhandle.h"
#include <QMainWindow>
#include <iostream>
#include <vector>
#include <QPushButton>
namespace Ui {
class MainWindow;
}
enum FilterSelection { Any, KeyType, Room, CurrentHolder, StorageLocation, Name, BeforeStart, AfterStart, BeforeEnd, AfterEnd, KeyID };
enum TableSelection { Keys, People, Leases };
enum HeaderSortState { None, Ascending, Descending };
class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();
private slots:
  void onHeaderClicked(int const logicalIndex);

  void on_main_pushButton_clicked();

  void on_main_addPermissionGroup_clicked();

  void on_main_filterButton_clicked();

  void on_main_pushButtonClearSearch_clicked();

  void on_main_keysButton_clicked();

  void on_main_peopleButton_clicked();

  void on_main_searchEntry_returnPressed();

  void on_main_leaseButton_clicked();

private:
  HeaderSortState header_sort_state;
  int last_sorted_header;
  Ui::MainWindow *ui;
  DBHandle db;
  CSqlRelationalTableModel *model;
  void setup_search_combobox(TableSelection const);
  FilterSelection from_qstring(QString const) const;
  void populate_table(TableSelection const);
  //load tables
  void load_keys_table();
  void load_people_table();
  void load_leases_table();
  //refresh combobox
  void setup_keys_search_combobox();
  void setup_people_search_combobox();
  void setup_leases_search_combobox();
  TableSelection current_table_selection;
  std::vector<QPushButton*> tab_buttons;
  void release_all_tabs();
  //generate sql queries
  void gen_search_sql_query_keys();
  void gen_search_sql_query_people();
  void gen_search_sql_query_leases();
  void search();
};

#endif // MAINWINDOW_H
