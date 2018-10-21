#include "csqlrelationaltablemodel.h"
#include <iostream>
CSqlRelationalTableModel::CSqlRelationalTableModel(QLabel *l, QObject *parent)
    : QSqlRelationalTableModel(parent) {
  this->result_count_label = l;
}

bool CSqlRelationalTableModel::select() {
  bool result = QSqlRelationalTableModel::select();
  this->result_count_label->setText(QString::number(this->rowCount()));
  return result;
}

CSqlRelationalTableModel::~CSqlRelationalTableModel()
{

    this->result_count_label = nullptr;

}
