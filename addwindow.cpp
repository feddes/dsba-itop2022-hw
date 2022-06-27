#include "addwindow.h"

#include "ui_addwindow.h"

AddWindow::AddWindow(QWidget *parent, QStringList *lst) : QDialog(parent), ui(new Ui::AddWindow)
{
    ui->setupUi(this);

    this->lst = lst;
    // tricky validators
    ui->Year->setMinimum(2010);
    ui->Year->setMaximum(2022);

    ui->Energy->setMinimum(0);
    ui->Energy->setMaximum(100);

    ui->Dance->setMinimum(0);
    ui->Dance->setMaximum(100);

    ui->Duration->setMinimum(0);
    ui->Duration->setMaximum(1000);

    ui->Genre->addItems(*lst);
}

AddWindow::~AddWindow() { delete ui; }

void AddWindow::setPointers(QStandardItemModel *model)
{
    this->model = model;
}

void AddWindow::on_Add_clicked()
{
    // update model
    int row = model->rowCount();                              // get # of rows
    model->insertRows(row, 1);                                // add new row
    QModelIndex index = model->index(row, 0, QModelIndex());  // "iterator"
    model->setData(index, ui->Title->text());  // insert text at position index
    QModelIndex index1 = model->index(row, 1, QModelIndex());  // "iterator"
    model->setData(index1, ui->Artist->text());
    QModelIndex index2 = model->index(row, 2, QModelIndex());  // "iterator"
    model->setData(index2, ui->Genre->currentText());
    QModelIndex index3 = model->index(row, 3, QModelIndex());  // "iterator"
    model->setData(index3, ui->Year->text());
    QModelIndex index4 = model->index(row, 4, QModelIndex());  // "iterator"
    model->setData(index4, ui->Energy->text());
    QModelIndex index5 = model->index(row, 5, QModelIndex());  // "iterator"
    model->setData(index5, ui->Dance->text());
    QModelIndex index6 = model->index(row, 6, QModelIndex());  // "iterator"
    model->setData(index6, ui->Duration->text());
    this->close();
}
