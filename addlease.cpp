#include "addlease.h"
#include "calender.h"
#include "ui_addlease.h"

AddLease::AddLease(QWidget *parent) : QDialog(parent), ui(new Ui::AddLease) {
  ui->setupUi(this);
  r = ui->rooms;
  k = ui->keys;
  p = ui->people;
  u = ui->to;
  f = ui->from;
  update_rooms();
  reload_date_time();
  update_keys();
  populate_people();
}

AddLease::~AddLease() { delete ui; }

bool AddLease::update_rooms() {
  // todo error validation
  return update_rooms(new QString());
}
bool AddLease::populate_people() {

  QSqlQuery q("SELECT users.id, users.name  FROM users");
  while (q.next()) {
    p->addItem(q.value(q.record().indexOf("users.name")).toString());
  }
}

bool AddLease::update_keys() {
  key_ids.clear();

  k->clear();
  QSqlQuery q;
  if (r->currentIndex() > 0) {
    q.prepare("SELECT key_data.id, key_data.key_type AS key_type FROM key_data "
              "JOIN rooms "
              "ON key_data.key_room=rooms.id WHERE rooms.name = :r ");
    q.bindValue(":r", r->currentText());
  } else {
    q.prepare("SELECT id, key_type FROM key_data");
  }
  if (!q.exec()) {
  }
  std::cout << q.lastQuery().toStdString() << std::endl;
  std::cout << q.lastError().text().toStdString() << std::endl;

  QStringList l;
  QSqlQuery v("SELECT * FROM leases");
  v.exec();
  std::vector<int> _leases;
  {
    int lease_offset = v.record().indexOf("key_id");
    while (v.next()) {
      _leases.push_back(v.value(lease_offset).toInt());
    }
  }

  while (q.next()) {
    int name_offset = q.record().indexOf("key_type");

    int id_offset = q.record().indexOf("id");
    int id = q.value(id_offset).toInt();
    if (std::find(_leases.begin(), _leases.end(), id) == _leases.end()) {
      key_ids.push_back(id);
      QString s = q.value(name_offset).toString();
      if (!l.contains(s)) {
        l.push_back(s);

        k->addItem(s);
      }
    }
  }
  return true;
}

bool AddLease::update_rooms(QString *s) {
  // todo error validation
  QSqlQuery q("SELECT name FROM rooms");
  int r_name_offset = q.record().indexOf("name");
  r->addItem("None");
  while (q.next()) {
    r->addItem(QString(q.value(r_name_offset).toString()));
  }
  return true;
}

void AddLease::reload_date_time() {

  u->setDateTime(QDateTime(QDate::currentDate(), QTime::currentTime()));
  f->setDateTime(QDateTime(QDate::currentDate(), QTime::currentTime()));
}

void AddLease::on_rooms_currentIndexChanged(int index) { update_keys(); }
int AddLease::get_id_of_selected_user() {
  QSqlQuery q;
  q.prepare("SELECT id FROM users WHERE name LIKE :name ");
  q.bindValue(":name", p->currentText());
  if (!q.exec()) {
      qDebug() << q.lastError();
  }
  int index = q.record().indexOf("id");
  q.first();
  int answer = q.value(index).toInt();
  if (answer == -1 ) {
      std::cout << "Error" << std::endl;
      throw;
  }
  return answer;
}
void AddLease::on_buttonBox_accepted() {

  int _k = get_id_of_selected_user();

  QSqlQuery q;
  qDebug() << _k;

  q.prepare("INSERT INTO leases (key_id, start_ts, end_ts, user_id) VALUES "
            "(:id, :sts, :ets, :u_id);");
  q.bindValue(":id", this->key_ids[k->currentIndex()]);
  q.bindValue(":sts", f->dateTime());
  q.bindValue(":ets", u->dateTime());
  q.bindValue(":u_id", _k);
  q.exec();
  std::cout << q.lastQuery().toStdString() << std::endl;
  std::cout << q.lastError().text().toStdString() << std::endl
               ;
   qDebug() << q.lastError();

  // key_data.key_room=rooms.id ");
}

void AddLease::on_cal_1_clicked() { on_cal_clicked(f); }

void AddLease::on_cal_2_clicked() { on_cal_clicked(u); }
void AddLease::on_cal_clicked(QDateTimeEdit *dt) {
  Calender *cal = new Calender(dt);
  cal->show();
}
