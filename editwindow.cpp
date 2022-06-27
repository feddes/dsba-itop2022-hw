#include "editwindow.h"
#include "ui_editwindow.h"

#include <iostream>
#include <QValidator>

EditWindow::EditWindow(QWidget *parent,QStringList *lst) :
    QDialog(parent),
    ui(new Ui::EditWindow)
{
    ui->setupUi(this);

    this->lst = lst;

    // tricky validators
    ui->Year->setMinimum(2010);
    ui->Year->setMaximum(2022);

    ui->Energy->setMinimum(0);
    ui->Energy->setMaximum(100);

    ui->Danceability->setMinimum(0);
    ui->Danceability->setMaximum(100);

    ui->Duration->setMinimum(0);
    ui->Duration->setMaximum(1000);

    ui->Genre->addItems(*lst);
}

EditWindow::~EditWindow()
{
    delete ui;
}
void EditWindow::setPointers(QStandardItemModel *model, int songNumber)
{
    this->model = model;
    this->songNumber= songNumber;

    QString title = model->data(model->index(songNumber,0)).toString();
    QString artist = model->data(model->index(songNumber,1)).toString();
    QString genre = model->data(model->index(songNumber,2)).toString();
    int year = model->data(model->index(songNumber,3)).toInt();
    int energy = model->data(model->index(songNumber,4)).toInt();
    int dance = model->data(model->index(songNumber,5)).toInt();
    int dur = model->data(model->index(songNumber,6)).toInt();

    ui->Title->setText(title);
    ui->Artist->setText(artist);
    ui->Genre->setCurrentText(genre);
    ui->Year->setValue(year);
    ui->Energy->setValue(energy);
    ui->Danceability->setValue(dance);
    ui->Duration->setValue(dur);
}

void EditWindow::on_pushButton_clicked()
{
    // Updating the model
    QModelIndex index = model->index(songNumber, 0, QModelIndex());  // "iterator"
    model->setData(index, ui->Title->text());  // insert text at position index
    QModelIndex index1 = model->index(songNumber, 1, QModelIndex());  // "iterator"
    model->setData(index1, ui->Artist->text());
    QModelIndex index2 = model->index(songNumber, 2, QModelIndex());  // "iterator"
    model->setData(index2, ui->Genre->currentText());
    QModelIndex index3 = model->index(songNumber, 3, QModelIndex());  // "iterator"
    model->setData(index3, ui->Year->text());
    QModelIndex index4 = model->index(songNumber, 4, QModelIndex());  // "iterator"
    model->setData(index4, ui->Energy->text());
    QModelIndex index5 = model->index(songNumber, 5, QModelIndex());  // "iterator"
    model->setData(index5, ui->Danceability->text());
    QModelIndex index6 = model->index(songNumber, 6, QModelIndex());  // "iterator"
    model->setData(index6, ui->Duration->text());
    this->close();
}

