#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  this->last_sorted_header = 0;
  this->header_sort_state = HeaderSortState::None;
  this->db = DBHandle();
  CSqlRelationalTableModel *model =
      new CSqlRelationalTableModel(ui->main_result_count_label, this);
  model->setTable("key_data");
  model->setRelation(2, QSqlRelation("rooms", "id", "name"));
  model->setRelation(3, QSqlRelation("users", "id", "name"));
  model->setEditStrategy(QSqlTableModel::OnFieldChange);
  model->setHeaderData(0, Qt::Horizontal, tr("Id"));
  model->setHeaderData(1, Qt::Horizontal, tr("Key Type"));
  model->setHeaderData(2, Qt::Horizontal, tr("Room"));
  model->setHeaderData(3, Qt::Horizontal, tr("Current Holder"));
  model->setHeaderData(4, Qt::Horizontal, tr("Storage Location"));
  ui->main_tableView->setModel(model);
  ui->main_tableView->setItemDelegate(
      new QSqlRelationalDelegate(ui->main_tableView));
  ui->main_tableView->resizeColumnsToContents();
  ui->main_tableView->sortByColumn(0, Qt::SortOrder::AscendingOrder);
  QHeaderView *h = ui->main_tableView->horizontalHeader();

  connect(h, SIGNAL(sectionClicked(int)), this, SLOT(on_header_clicked(int)));
  // QSqlQuery q;
  std::cout << "Dank memes" << std::endl;
}

void MainWindow::on_header_clicked(int logical_index) {
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

  AddKey *addkey = new AddKey();
  addkey->show();
}

void MainWindow::on_main_addPermissionGroup_clicked() {
  CreatePermissionGroup *cpg = new CreatePermissionGroup();
  cpg->show();
}
