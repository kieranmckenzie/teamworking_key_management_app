#include "createpermissiongroup.h"
#include "ui_createpermissiongroup.h"
bool CreatePermissionGroup::validate_name_input(QString *error) {
  // Todo
  *error = "No error";
  return true;
}
bool CreatePermissionGroup::validate_dropdown_input(QString *error) {
  // Todo
  *error = "No error";
  return true;
}

CreatePermissionGroup::CreatePermissionGroup(QSqlRelationalTableModel *m,
                                             QWidget *parent)
    : QDialog(parent), ui(new Ui::CreatePermissionGroup) {
  ui->setupUi(this);
  this->main_window_model = m;
  this->string_list_model.setStringList(this->string_list);
  this->ui->createpermissiongroup_listView->setModel(&this->string_list_model);

  QSqlQuery r("SELECT id, name FROM rooms");

  int r_id_offset = r.record().indexOf("id");
  int r_name_offset = r.record().indexOf("name");
  while (r.next()) {
    QString name = r.value(r_name_offset).toString();
    int id = r.value(r_id_offset).toInt();
    this->ui->createpermissiongroup_rooms->addItem(name);
    this->room_dropdown_id_vec.push_back(id);
  }
}

CreatePermissionGroup::~CreatePermissionGroup() {
  if (!this->main_window_model->select()) {
    // Todo
  }
  delete ui;
}

void CreatePermissionGroup::on_buttonBox_accepted() {
  QString str;

  if (!this->validate_name_input(&str))
    std::cout << str.toStdString() << std::endl;

  QSqlQuery q;
  q.prepare("INSERT INTO permission_groups (name) VALUES (:name)");
  q.bindValue(":name", this->ui->createpermissiongroup_lineEdit->text());
  // Start Saftey Check
  std::string checkerPhrase(
      this->ui->createpermissiongroup_lineEdit->text().toStdString());
  std::string
      checkerComparisonArray[21] = {"TABLE", "Table", "table",  "INTO",
                                    "Into",  "into",  "FROM",   "From",
                                    "from",  "WHERE", "Where",  "where",
                                    "*",     "+",     "-",      "DROP",
                                    "Drop",  "drop",  "DELETE", "Delete",
                                    "delete"}; // SQL command array I assume
                                               // theres a library for this but
                                               // ehh, and im sure theres a way
                                               // to do this case insensitivly

  for (const std::string &text : checkerComparisonArray) {
    if (checkerPhrase.find(text) != std::string::npos) {
      std::cout << "checkerPhrase"
                << "\n";
      std::cout << text << " found"
                << "\n";
      return;
    } else {
      std::cout << "checkerPhrase"
                << "\n";
      std::cout << text << " not found"
                << "\n";
    }
  }
  // End Saftey Check
  q.exec();
  this->deleteLater();
}

void CreatePermissionGroup::on_createpermissiongroup_addroom_clicked() {
  int offset = this->ui->createpermissiongroup_rooms->currentIndex();
  this->string_list.append(
      this->ui->createpermissiongroup_rooms->currentText());
  this->room_dropdown_id_vec.push_back(offset);
  this->ui->createpermissiongroup_rooms->removeItem(offset);
  this->string_list_model.setStringList(this->string_list);
}

void CreatePermissionGroup::on_buttonBox_rejected() { this->deleteLater(); }

void CreatePermissionGroup::on_createpermissiongroup_remove_clicked() {
  int offset = ui->createpermissiongroup_listView->currentIndex().row();
  if (current_selected >= 0 && offset >= 0) {
    ui->createpermissiongroup_rooms->addItem(string_list.at(offset));
    string_list.removeAt(offset);
    string_list_model.setStringList(string_list);
  }
}

void CreatePermissionGroup::on_createpermissiongroup_listView_clicked(
    const QModelIndex &index) {

  current_selected = index.row();

  std::cout << current_selected << std::endl;
}
