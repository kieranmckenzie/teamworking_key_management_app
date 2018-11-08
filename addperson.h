#ifndef ADDPERSON_H
#define ADDPERSON_H

#include <QDialog>
#include <QSqlRelationalTableModel>

namespace Ui {
class AddPerson;
}

class AddPerson : public QDialog {
  Q_OBJECT

public:
  explicit AddPerson(QSqlRelationalTableModel *m, QWidget *parent = 0);
  ~AddPerson();

private slots:
  void on_buttonBox_accepted();

private:
  Ui::AddPerson *ui;
  QSqlRelationalTableModel *m;
};

#endif // ADDPERSON_H
