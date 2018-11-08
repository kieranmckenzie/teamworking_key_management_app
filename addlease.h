#ifndef ADDLEASE_H
#define ADDLEASE_H

#include <QComboBox>
#include <QDateTimeEdit>
#include <QDialog>
#include <QtSql>
#include <vector>

#include <iostream>
namespace Ui {
class AddLease;
}

class AddLease : public QDialog {
  Q_OBJECT

public:
  explicit AddLease(QSqlRelationalTableModel *m, QWidget *parent = 0);
  ~AddLease();

private slots:
  void on_rooms_currentIndexChanged(int index);

  void on_buttonBox_accepted();

  void on_cal_1_clicked();

  void on_cal_2_clicked();

private:
  Ui::AddLease *ui;
  QComboBox *r, *k, *p;
  QDateTimeEdit *f, *u;
  QSqlRelationalTableModel *m;
  bool update_rooms();
  bool update_rooms(QString *);
  void reload_date_time();
  bool update_keys();
  bool update_keys(QString *);
  bool populate_people();
  std::vector<int> key_ids;
  void on_cal_clicked(QDateTimeEdit *);
  int get_id_of_selected_user();
};

#endif // ADDLEASE_H
