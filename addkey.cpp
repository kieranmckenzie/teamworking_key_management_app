#include "addkey.h"
#include "ui_addkey.h"


AddKey::AddKey(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddKey)
{
    ui->setupUi(this);
    QSqlQuery q("SELECT id, first_name, last_name FROM users");
    std::cout << "Length of return is: " << q.size() << std::endl;
    int id_offset = q.record().indexOf("id");
    int fn_offset = q.record().indexOf("first_name");
    int ln_offset = q.record().indexOf("last_name");
    while (q.next()) {
        QString first_name = q.value(fn_offset).toString();
        QString last_name = q.value(ln_offset).toString();
        int id = q.value(id_offset).toInt();
        QString out = first_name + " " + last_name;
       this->ui->addkey_user_dropdown->addItem(out);
        this->dropdown_id_vec.push_back(id);
    }



}

AddKey::~AddKey()
{
    delete ui;
}

bool AddKey::validate_input( QString* error) {
    *error = "No error";
    return true;
}

void AddKey::on_buttonBox_accepted()
{
    QString str;

    if (!this->validate_input(&str))
        std::cout << str.toStdString() << std::endl;


    QSqlQuery q;
    q.prepare("INSERT INTO key_data ( key_type, key_room, current_holder, storage_location)"
              "VALUES (:key_type, :key_room, :current_holder, :storage_location)");
    q.bindValue(":key_type", this->ui->addkey_key_type->toPlainText());
    q.bindValue(":key_room", this->ui->addkey_key_room->toPlainText());
    q.bindValue(":storage_location", this->ui->addkey_storage_location->toPlainText());

    int dropdown_index = this->ui->addkey_user_dropdown->currentIndex();
    q.bindValue(":current_holder", (int)this->dropdown_id_vec[dropdown_index]);
    q.exec();
    std::cout << q.lastError().text().toStdString() << std::endl;

}
