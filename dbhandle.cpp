#include "dbhandle.h"
#include <iostream>
DBHandle::DBHandle()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");
    db.setHostName("maegis.net");
    db.setUserName("iksf");
    db.setPassword("Password!");
    db.setDatabaseName("keys");

    if (!db.open()) {
        std::cout << db.lastError().text().toStdString() << std::endl;
    }

    QStringList tables = db.tables();
    for (QString i : tables) {
        std::cout << i.toStdString() << std::endl;
    }
    this->db = db;




}
