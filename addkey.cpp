#include "addkey.h"
#include "ui_addkey.h"
#include <iostream>
#include <string>
#include <cstring>
#include <locale>
#include <algorithm>


AddKey::AddKey(QSqlRelationalTableModel *m, QWidget *parent)
    : QDialog(parent), ui(new Ui::AddKey) {
  ui->setupUi(this);
  this->main_window_model = m;
  {
    QSqlQuery q("SELECT id, name FROM users");
    std::cout << "Length of return is: " << q.size() << std::endl;
    int id_offset = q.record().indexOf("id");
    int n_offset = q.record().indexOf("name");
    while (q.next()) {
      QString name = q.value(n_offset).toString();
      int id = q.value(id_offset).toInt();
      this->ui->addkey_user_dropdown->addItem(name);
      this->user_dropdown_id_vec.push_back(id);
    }
  }
  {
    QSqlQuery q("SELECT id,name from rooms");
    int id_offset = q.record().indexOf("id");
    int n_offset = q.record().indexOf("name");
    while (q.next()) {
      QString name = q.value(n_offset).toString();
      int id = q.value(id_offset).toInt();
      this->ui->addkey_room_dropdown->addItem(name);
      this->room_dropdown_id_vec.push_back(id);
    }
  }
}

AddKey::~AddKey() {
  std::cout << "Addkey destructor fired" << std::endl;
  if (!this->main_window_model->select()) {
    // Todo
  }
  delete ui;
}

bool AddKey::validate_input(QString *error) {
  // Todo
  *error = "No error";
  return true;
}

void AddKey::on_buttonBox_accepted() {
  QString str;

  if (!this->validate_input(&str))
    std::cout << str.toStdString() << std::endl;

  QSqlQuery q;
  q.prepare(
      "INSERT INTO key_data ( key_type, key_room, current_holder, "
      "storage_location)"
      "VALUES (:key_type, :key_room, :current_holder, :storage_location)");
  q.bindValue(":key_type", this->ui->addkey_key_type->text());
  // q.bindValue(":key_room", this->ui->addkey_key_room->text());

  q.bindValue(":storage_location", this->ui->addkey_storage_location->text());
  {
    int dropdown_index = this->ui->addkey_user_dropdown->currentIndex();
    q.bindValue(":current_holder", this->user_dropdown_id_vec[dropdown_index]);
  }
  {
    int dropdown_index = this->ui->addkey_room_dropdown->currentIndex();
    q.bindValue(":key_room", this->room_dropdown_id_vec[dropdown_index]);
  }

  // Start Saftey Check
  std::string checkerPhrase ((this->ui->addkey_key_type->text()).toStdString() + (this->ui->addkey_storage_location->text()).toStdString());
  std::string checkerComparisonArray[21] = {"TABLE", "Table", "table", "INTO", "Into", "into", "FROM", "From", "from", "WHERE", "Where", "where", "*", "+", "-", "DROP", "Drop", "drop", "DELETE", "Delete", "delete"}; // SQL command array I assume theres a library for this but ehh, and im sure theres a way to do this case insensitivly

  for (const std::string &text : checkerComparisonArray){
    if (checkerPhrase.find(text) != std::string::npos) {
            std::cout << "checkerPhrase" << "\n";
            std::cout << text << " found" << "\n";
            return;
        } else {
            std::cout << "checkerPhrase" << "\n";
            std::cout << text << " not found" << "\n";
    }
  }
  // End Saftey Check
  q.exec();
  std::cout << q.lastError().text().toStdString() << std::endl;
  this->deleteLater();
}

void AddKey::on_buttonBox_rejected() { this->deleteLater(); }
