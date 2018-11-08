#include "addperson.h"
#include "ui_addperson.h"
#include <QtSql>
AddPerson::AddPerson(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddPerson)
{
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
}
