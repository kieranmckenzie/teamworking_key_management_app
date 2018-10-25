#ifndef ADDKEY_H
#define ADDKEY_H

#include <QDialog>
#include <QSqlRelationalTableModel>
#include <QtSql>
#include <iostream>
#include <vector>

namespace Ui {
class AddKey;
}

class AddKey : public QDialog {
  Q_OBJECT

public:
  explicit AddKey(QSqlRelationalTableModel *m, QWidget *parent = 0);
  ~AddKey();
  bool validate_input(QString *error);

private slots:
  void on_buttonBox_accepted();

  void on_buttonBox_rejected();

private:
  Ui::AddKey *ui;
  std::vector<int> user_dropdown_id_vec;
  std::vector<int> room_dropdown_id_vec;
  QSqlRelationalTableModel *main_window_model;
};

#endif // ADDKEY_H
