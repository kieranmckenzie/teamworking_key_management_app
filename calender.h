#ifndef CALENDER_H
#define CALENDER_H

#include <QCalendarWidget>
#include <QDateTimeEdit>
#include <QDialog>

namespace Ui {
class Calender;
}

class Calender : public QDialog {
  Q_OBJECT

public:
  explicit Calender(QDateTimeEdit *dt, QWidget *parent = 0);
  ~Calender();

private slots:

  void on_buttonBox_accepted();

private:
  Ui::Calender *ui;
  QDateTimeEdit *dt;
};

#endif // CALENDER_H
