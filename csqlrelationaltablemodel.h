#ifndef CSQLRELATIONALMODEL_H
#define CSQLRELATIONALMODEL_H
#include <QSqlRelationalTableModel>
#include <QLabel>
class CSqlRelationalTableModel : public QSqlRelationalTableModel
{
private:
  QLabel *result_count_label;

public:
  explicit CSqlRelationalTableModel(QLabel *, QObject * = nullptr);
  bool select();
};

#endif // CSQLRELATIONALMODEL_H
