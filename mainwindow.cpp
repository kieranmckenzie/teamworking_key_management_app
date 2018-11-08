#include "mainwindow.h"
#include "ui_mainwindow.h"
void MainWindow::populate_table(TableSelection const t) {
  this->model = new CSqlRelationalTableModel(ui->main_result_count_label, this);
  // this->model->setEditStrategy(QSqlTableModel::OnFieldChange);
  this->ui->main_tableView->setModel(this->model);
  switch (t) {
  case Keys:
    this->load_keys_table();
    break;
  case People:
    this->load_people_table();
    break;
  case Leases:
    this->load_leases_table();
    break;
  default:
    this->load_keys_table();
    break;
  };
}
void MainWindow::load_keys_table() {
  this->model->setTable("key_data");
  this->model->setRelation(2, QSqlRelation("rooms", "id", "name"));
  this->model->setRelation(3, QSqlRelation("users", "id", "name"));
  this->model->setHeaderData(0, Qt::Horizontal, tr("Id"));
  this->model->setHeaderData(1, Qt::Horizontal, tr("Key Type"));
  this->model->setHeaderData(2, Qt::Horizontal, tr("Room"));
  this->model->setHeaderData(3, Qt::Horizontal, tr("Current Holder"));
  this->model->setHeaderData(4, Qt::Horizontal, tr("Storage Location"));
  this->setup_search_combobox(TableSelection::Keys);
  this->current_table_selection = TableSelection::Keys;
}
void MainWindow::load_people_table() {
  this->model->setTable("users");
  this->model->setHeaderData(0, Qt::Horizontal, tr("Id"));
  this->model->setHeaderData(1, Qt::Horizontal, tr("Name"));
  this->setup_search_combobox(TableSelection::People);
  this->current_table_selection = TableSelection::People;
}

void MainWindow::load_leases_table() {

  this->model->setTable("leases");
  //this->model->setHeaderData(0, Qt::Horizontal, tr("Id"));
  this->model->setHeaderData(1, Qt::Horizontal, tr("Key ID"));
  this->model->setHeaderData(2, Qt::Horizontal, tr("Start"));
  this->model->setHeaderData(3, Qt::Horizontal, tr("End"));
  this->model->setHeaderData(4, Qt::Horizontal, tr("Username"));
  this->model->setRelation(4, QSqlRelation("users", "id", "name"));
  this->setup_search_combobox(TableSelection::Leases);
  this->current_table_selection = TableSelection::Leases;
}


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  this->current_table_selection = TableSelection::Keys;
  ui->setupUi(this);
  this->last_sorted_header = 0;
  this->header_sort_state = HeaderSortState::None;
  this->db = DBHandle();
  this->populate_table(this->current_table_selection);
  ui->main_tableView->setItemDelegate(
      new QSqlRelationalDelegate(ui->main_tableView));
  ui->main_tableView->resizeColumnsToContents();
  ui->main_tableView->sortByColumn(0, Qt::SortOrder::AscendingOrder);
  QHeaderView *h = ui->main_tableView->horizontalHeader();

  connect(h, SIGNAL(sectionClicked(int)), this,
          SLOT(onHeaderClicked(int const)));
  // QSqlQuery q;

  ui->main_keysButton->setCheckable(true);
  ui->main_peopleButton->setCheckable(true);
  ui->main_leaseButton->setCheckable(true);
  ui->main_keysButton->setChecked(true);
  ui->main_peopleButton->setChecked(false);
  ui->main_leaseButton->setChecked(false);
  this->tab_buttons.push_back(this->ui->main_keysButton);
  this->tab_buttons.push_back(this->ui->main_peopleButton);
  this->tab_buttons.push_back(this->ui->main_leaseButton);

  std::cout << "Dank memes" << std::endl;
}
void MainWindow::release_all_tabs() {
  for (QPushButton *q : this->tab_buttons) {
    q->setChecked(false);
  }
}

void MainWindow::onHeaderClicked(int const logical_index) {
  std::cout << "on header clicked" << std::endl;
  QHeaderView *h = ui->main_tableView->horizontalHeader();
  if (this->last_sorted_header == logical_index &&
      this->header_sort_state == HeaderSortState::Ascending) {
    h->setSortIndicator(logical_index, Qt::DescendingOrder);
    this->header_sort_state = HeaderSortState::Descending;
  } else {
    h->setSortIndicator(logical_index, Qt::AscendingOrder);
    this->header_sort_state = HeaderSortState::Ascending;
  }
  this->last_sorted_header = logical_index;
  ui->main_tableView->sortByColumn(logical_index);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_main_pushButton_clicked() {

  AddKey *addkey = new AddKey(this->model);
  addkey->show();
}

void MainWindow::on_main_addPermissionGroup_clicked() {
  CreatePermissionGroup *cpg = new CreatePermissionGroup(this->model);
  cpg->show();
}

void MainWindow::gen_search_sql_query_people() {
  QString s;
  QString t = this->ui->main_searchEntry->text();
  switch (this->from_qstring(this->ui->main_comboBox->currentText())) {
  case Name:
    s = "users.name LIKE '%" + t + "%'";
    break;
  default:
    break;
  };

  this->model->setFilter(s);
  std::cout << this->model->query().lastQuery().toStdString() << std::endl;
}

void MainWindow::gen_search_sql_query_leases() {
  QString s;
  QString t = this->ui->main_searchEntry->text();
  switch (this->from_qstring(this->ui->main_comboBox->currentText())) {
  // SELECT leases."id",relTblAl_1.name AS
  // users_name_2,relTblAl_2.name,leases."end_ts" FROM leases,users
  // relTblAl_1,rooms relTblAl_2 WHERE (leases."key_id"=relTblAl_1.id AND
  // leases."start_ts"=relTblAl_2.id)
  case Any:
    s = "relTblAl_1.name LIKE '%" + t + "%' OR relTblAl_2.name LIKE '%" + t +
        "%' OR leases.key_id LIKE '%" + t + "%' OR leases.id LIKE '%" + t +
        "%';";
    break;
  case CurrentHolder:
    s = "relTblAl_1.name LIKE '%" + t + "%';";
    break;
  case Room:
    s = "relTblAl_2.name LIKE '%" + t + "%';";
    break;
  case KeyID:

    s = "leases.key_id IS '%" + t + "%';";
    break;
    // Todo
    // Accomodate alternative timedate formats
  case BeforeStart:
    s = " leases.start_ts LESS THAN '%" + t + "%';";
    break;
  case AfterStart:
    s = "leases.start_ts GREATER THAN '%" + t + "%';";
    break;

  case BeforeEnd:
    s = "leases.end_ts LESS THAN '%" + t + "%';";
    break;
  case AfterEnd:
    s = "leases.end_ts GREATER THAN '%" + t + "%';";
    break;
    //
  default:
    std::cout << "185" << std::endl;
    abort();
  };
  this->model->setFilter(s);

  std::cout << this->model->query().lastQuery().toStdString() << std::endl;
  std::cout << this->model->query().lastError().text().toStdString()
            << std::endl;
}

void MainWindow::gen_search_sql_query_keys() {

  QString s;
  QString t = this->ui->main_searchEntry->text();
  switch (from_qstring(this->ui->main_comboBox->currentText())) {
  case Any:
    s = "key_type LIKE '%" + t + "%' " + "OR relTblAl_2.name LIKE '%" + t +
        "%' " + "OR relTblAl_3.name LIKE '%" + t + "%' " +
        "OR storage_location LIKE '%" + t + "%' ";
    break;
  case KeyType:

    s = "key_type LIKE '%" + t + "%'";
    break;
  case Room:
    s = "relTblAl_2.name LIKE '%" + t + "%'";
    break;
  case CurrentHolder:
    s = "relTblAl_3.name LIKE '%" + t + "%'";
    break;
  case StorageLocation:
    s = "storage_location LIKE '%" + t + "%'";
    break;
  default:
    std::cout << "139 err" << std::endl;
    break;
  }
  this->model->setFilter(s);
  std::cout << this->model->query().lastQuery().toStdString() << std::endl;
}
void MainWindow::search() {
  switch (this->current_table_selection) {
  case Keys:
    this->gen_search_sql_query_keys();
    break;
  case People:
    this->gen_search_sql_query_people();
    break;
  case Leases:
    this->gen_search_sql_query_leases();
    break;
  default:
    std::cout << "Error1" << std::endl;
    break;
  }
}
void MainWindow::on_main_filterButton_clicked() { this->search(); }

void MainWindow::setup_search_combobox(TableSelection const t) {
  // hack
  // main_comboBox->count() not right?
  for (int i = 0; i < 50; i++) {
    ui->main_comboBox->removeItem(0);
  }
  switch (t) {
  case TableSelection::Keys:
    this->setup_keys_search_combobox();
    break;
  case TableSelection::People:
    this->setup_people_search_combobox();
    break;
  case TableSelection::Leases:
    this->setup_leases_search_combobox();
    break;
  default:
    std::cout << "Error2" << std::endl;
    abort();
    break;
  }
  // ui->main_comboBox->currentText() = "";
}

void MainWindow::setup_keys_search_combobox() {
  ui->main_comboBox->addItem("Any");
  ui->main_comboBox->addItem("Key Type");
  ui->main_comboBox->addItem("Room");
  ui->main_comboBox->addItem("Current Holder");
  ui->main_comboBox->addItem("Storage Location");
}
void MainWindow::setup_people_search_combobox() {
  ui->main_comboBox->addItem("Name");
}

void MainWindow::setup_leases_search_combobox() {
  ui->main_comboBox->addItem("Any");
  // ui->main_comboBox->addItem("Lease Id");
  ui->main_comboBox->addItem("Key ID");
  ui->main_comboBox->addItem("Leased to");
  ui->main_comboBox->addItem("Room");
  ui->main_comboBox->addItem("Started since");
  ui->main_comboBox->addItem("Started before");
  ui->main_comboBox->addItem("Ended since");
  ui->main_comboBox->addItem("Ended before");
}

inline FilterSelection MainWindow::from_qstring(QString const qs) const {
  if (qs == "Any")
    return Any;
  if (qs == "Key Type")
    return KeyType;
  if (qs == "Room")
    return Room;
  if (qs == "Current Holder" || qs == "Leased to")
    return CurrentHolder;
  if (qs == "Storage Location")
    return StorageLocation;
  if (qs == "Name")
    return Name;
  if (qs == "Started since")
    return BeforeEnd;
  if (qs == "Started before")
    return BeforeStart;
  if (qs == "Ended since")
    return AfterEnd;
  if (qs == "Ended before")
    return AfterStart;
  if (qs == "KeyID" || qs == "Key ID")
    return KeyID;
  // Crash fix?
  std::cout << "Unable to determine switch for " << qs.toStdString()
            << std::endl;
  abort();
}

void MainWindow::on_main_pushButtonClearSearch_clicked() {
  this->model->setFilter(QString());
  this->ui->main_comboBox->clear();
  this->setup_search_combobox(this->current_table_selection);
  this->ui->main_searchEntry->clear();
  this->model->select();
}

void MainWindow::on_main_keysButton_clicked() {
  if (this->current_table_selection != TableSelection::Keys) {
    this->release_all_tabs();
    ui->main_keysButton->setChecked(true);
    this->populate_table(TableSelection::Keys);
    this->model->select();
  }
}

void MainWindow::on_main_peopleButton_clicked() {
  if (this->current_table_selection != TableSelection::People) {
    this->release_all_tabs();
    ui->main_peopleButton->setChecked(true);
    this->populate_table(TableSelection::People);
    this->model->select();
  }
}

void MainWindow::on_main_searchEntry_returnPressed() { this->search(); }

void MainWindow::on_main_leaseButton_clicked() {

  if (this->current_table_selection != TableSelection::Leases) {
    this->release_all_tabs();
    ui->main_leaseButton->setChecked(true);
    this->populate_table(TableSelection::Leases);
    this->model->select();
  }
}

void MainWindow::on_main_pushButton_add_person_clicked()
{
    AddPerson* addperson = new AddPerson();
    addperson->show();

}

void MainWindow::on_main_pushButton_add_lease_clicked()

{

    AddLease *leases = new AddLease();
    leases->show();
}
