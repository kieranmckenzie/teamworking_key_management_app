#ifndef CREATEPERMISSIONGROUP_H
#define CREATEPERMISSIONGROUP_H

#include <QDialog>
#include <QSqlRelationalTableModel>
#include <QStringList>
#include <QStringListModel>
#include <QtSql>
#include <iostream>
namespace Ui {
class CreatePermissionGroup;
}

class CreatePermissionGroup : public QDialog {
  Q_OBJECT

public:
  explicit CreatePermissionGroup(QSqlRelationalTableModel *m,
                                 QWidget *parent = 0);
  ~CreatePermissionGroup();

private slots:
  void on_buttonBox_accepted();

  void on_createpermissiongroup_addroom_clicked();

  void on_buttonBox_rejected();

  void on_createpermissiongroup_remove_clicked();

  void on_createpermissiongroup_listView_clicked(const QModelIndex &index);

private:
  bool validate_dropdown_input(QString *error);
  bool validate_name_input(QString *error);
  Ui::CreatePermissionGroup *ui;
  std::vector<int> room_dropdown_id_vec;
  std::vector<int> selected_room_dropdown_id_vec;
  QStringListModel string_list_model;
  QStringList string_list;
  QSqlRelationalTableModel *main_window_model;
  int current_selected = -1;
};

#endif // CREATEPERMISSIONGROUP_H
