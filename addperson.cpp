#include "addperson.h"
#include "ui_addperson.h"
#include <QtSql>
AddPerson::AddPerson(
        QSqlRelationalTableModel *m,
        QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddPerson)
{
    this->m = m;
    ui->setupUi(this);
}

AddPerson::~AddPerson()
{
    delete ui;
}

void AddPerson::on_buttonBox_accepted()
{
    QString s = ui->lineEdit->text();

    QSqlQuery q;
    q.prepare("INSERT INTO users (name) VALUES (:s)");
    q.bindValue(":s", s);
    q.exec();
    m->select();
}
