#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  this->last_sorted_header = 0;
  this->header_sort_state = HeaderSortState::None;
  this->db = DBHandle();
  this->model = new CSqlRelationalTableModel(ui->main_result_count_label, this);
  model->setTable("key_data");
  model->setRelation(2, QSqlRelation("rooms", "id", "name"));
  model->setRelation(3, QSqlRelation("users", "id", "name"));
  model->setEditStrategy(QSqlTableModel::OnFieldChange);
  model->setHeaderData(0, Qt::Horizontal, tr("Id"));
  model->setHeaderData(1, Qt::Horizontal, tr("Key Type"));
  model->setHeaderData(2, Qt::Horizontal, tr("Room"));
  model->setHeaderData(3, Qt::Horizontal, tr("Current Holder"));
  model->setHeaderData(4, Qt::Horizontal, tr("Storage Location"));
  this->setup_search_combobox();
  ui->main_tableView->setModel(model);
  ui->main_tableView->setItemDelegate(
      new QSqlRelationalDelegate(ui->main_tableView));
  ui->main_tableView->resizeColumnsToContents();
  ui->main_tableView->sortByColumn(0, Qt::SortOrder::AscendingOrder);
  QHeaderView *h = ui->main_tableView->horizontalHeader();

  connect(h, SIGNAL(sectionClicked(int)), this, SLOT(onHeaderClicked(int)));
  // QSqlQuery q;

  std::cout << "Dank memes" << std::endl;
}

void MainWindow::onHeaderClicked(int logical_index) {
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
void MainWindow::on_main_filterButton_clicked() {
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
  }
  this->model->setFilter(s);
  std::cout << this->model->query().lastQuery().toStdString() << std::endl;
}

void MainWindow::setup_search_combobox() {
  ui->main_comboBox->addItem("Any");
  ui->main_comboBox->addItem("Key Type");
  ui->main_comboBox->addItem("Room");
  ui->main_comboBox->addItem("Current Holder");
  ui->main_comboBox->addItem("Storage Location");
}

FilterSelection MainWindow::from_qstring(QString qs) {
  if (qs == "Any")
    return Any;
  if (qs == "Key Type")
    return KeyType;
  if (qs == "Room")
    return Room;
  if (qs == "Current Holder")
    return CurrentHolder;
  if (qs == "Storage Location")
    return StorageLocation;

  return Any;
}

void MainWindow::on_main_pushButtonClearSearch_clicked() {
  this->model->setFilter(QString());
  this->ui->main_comboBox->clear();
  this->setup_search_combobox();
  this->ui->main_searchEntry->clear();
  this->model->select();
}
