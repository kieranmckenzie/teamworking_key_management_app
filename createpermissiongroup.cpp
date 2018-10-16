#include "createpermissiongroup.h"
#include "ui_createpermissiongroup.h"
bool CreatePermissionGroup::validate_name_input(QString *error) {
  *error = "No error";
  return true;
}
bool CreatePermissionGroup::validate_dropdown_input(QString *error) {
  *error = "No error";
  return true;
}

CreatePermissionGroup::CreatePermissionGroup(QWidget *parent)
    : QDialog(parent), ui(new Ui::CreatePermissionGroup) {
  ui->setupUi(this);

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

CreatePermissionGroup::~CreatePermissionGroup() { delete ui; }

void CreatePermissionGroup::on_buttonBox_accepted() {
  QString str;

  if (!this->validate_name_input(&str))
    std::cout << str.toStdString() << std::endl;

  QSqlQuery q;
  q.prepare("INSERT INTO permission_groups (name) VALUES (:name)");
  q.bindValue(":name", this->ui->createpermissiongroup_lineEdit->text());
  q.exec();
}

void CreatePermissionGroup::on_createpermissiongroup_addroom_clicked() {
  int offset = this->ui->createpermissiongroup_rooms->currentIndex();
  this->string_list.append(
      this->ui->createpermissiongroup_rooms->currentText());
  this->room_dropdown_id_vec.push_back(offset);
  this->ui->createpermissiongroup_rooms->removeItem(offset);
}
