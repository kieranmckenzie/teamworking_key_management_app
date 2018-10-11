#ifndef DBHANDLE_H
#define DBHANDLE_H
#include <QtSql>
class DBHandle
{
  public:
    DBHandle();
    QSqlDatabase db;
};

#endif // DBHANDLE_H
