#ifndef CSQLRELATIONALMODEL_H
#define CSQLRELATIONALMODEL_H
#include <QLabel>
#include <QSqlRelationalTableModel>
class CSqlRelationalTableModel : public QSqlRelationalTableModel {
private:
  QLabel *result_count_label;

public:
  explicit CSqlRelationalTableModel(QLabel *, QObject * = nullptr);
  bool select();


  ~CSqlRelationalTableModel();
};

#endif // CSQLRELATIONALMODEL_H
