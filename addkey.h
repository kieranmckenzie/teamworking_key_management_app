#ifndef ADDKEY_H
#define ADDKEY_H

#include <QDialog>
#include <QtSql>
#include <vector>
#include <iostream>

namespace Ui {
class AddKey;
}

class AddKey : public QDialog
{
    Q_OBJECT

public:
    explicit AddKey(QWidget *parent = 0);
    ~AddKey();
    bool validate_input( QString* error ) ;

private slots:
    void on_buttonBox_accepted();

private:
    Ui::AddKey *ui;
    std::vector<size_t> dropdown_id_vec;

};

#endif // ADDKEY_H
