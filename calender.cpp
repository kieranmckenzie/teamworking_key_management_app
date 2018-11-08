#include "calender.h"
#include "ui_calender.h"

Calender::Calender(QDateTimeEdit *dt, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Calender)
{
    ui->setupUi(this);
    this->dt = dt;
}

Calender::~Calender()
{
    delete ui;
}

void Calender::on_buttonBox_accepted()
{
   dt->setDate( ui->calendarWidget->selectedDate());
}
