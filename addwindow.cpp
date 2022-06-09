#include "addwindow.h"

#include "ui_addwindow.h"

AddWindow::AddWindow(QWidget *parent) : QDialog(parent), ui(new Ui::AddWindow)
{
    ui->setupUi(this);
}

AddWindow::~AddWindow() { delete ui; }

void AddWindow::setPointers(Song *song, QStandardItemModel *model)
{
    this->song = song;
    this->model = model;
}

void AddWindow::on_Add_clicked()
{
    // fill a Pizza with set attributes
    this->song->title = ui->Title->text().toStdString();
    this->song->artist = ui->Artist->text().toStdString();
    this->song->genre = ui->Genre->text().toStdString();
    this->song->year = ui->Year->text().toInt();
    this->song->energy = ui->Energy->text().toInt();
    this->song->dance = ui->Dance->text().toInt();
    this->song->duration = ui->Duration->text().toInt();

    // update model
    int row = model->rowCount();                              // get # of rows
    model->insertRows(row, 1);                                // add new row
    QModelIndex index = model->index(row, 0, QModelIndex());  // "iterator"
    model->setData(index, ui->Title->text());  // insert text at position index
    QModelIndex index1 = model->index(row, 1, QModelIndex());  // "iterator"
    model->setData(index1, ui->Artist->text());
    QModelIndex index2 = model->index(row, 2, QModelIndex());  // "iterator"
    model->setData(index2, ui->Genre->text());
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
