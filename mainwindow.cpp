#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),
                                          ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->db = DBHandle();
    CSqlRelationalTableModel *model = new CSqlRelationalTableModel(ui->main_result_count_label, this);
    model->setTable("key_data");
    model->setRelation(3, QSqlRelation("users", "id", "last_name"));
    model->setEditStrategy(QSqlTableModel::OnFieldChange);
    model->setHeaderData(0, Qt::Horizontal, tr("Id"));
    model->setHeaderData(1, Qt::Horizontal, tr("Key Type"));
    model->setHeaderData(2, Qt::Horizontal, tr("Room"));
    model->setHeaderData(3, Qt::Horizontal, tr("Current Holder"));
    model->setHeaderData(4, Qt::Horizontal, tr("Storage Location"));
    ui->main_tableView->setModel(model);
    ui->main_tableView->setItemDelegate(new QSqlRelationalDelegate(ui->main_tableView));
    ui->main_tableView->resizeColumnsToContents();
    ui->main_tableView->sortByColumn(0, Qt::SortOrder::AscendingOrder);
    //QSqlQuery q;
    std::cout << "Dank memes" << std::endl;
}

MainWindow::~MainWindow()
{
    delete ui;
}




void MainWindow::on_main_pushButton_clicked()
{

   AddKey* addkey = new AddKey();
   addkey->show();
}
