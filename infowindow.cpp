#include "infowindow.h"
#include <QVariant>
#include "ui_infowindow.h"

InfoWindow::InfoWindow(QWidget *parent)
    : QDialog(parent), ui(new Ui::InfoWindow)
{
    ui->setupUi(this);
}

InfoWindow::~InfoWindow() { delete ui; }

void InfoWindow::getData(QStandardItemModel *plst, int songNumber)
{
    ui->Title->setText(plst->data(plst->index(songNumber,0)).toString());
    ui->Artist->setText(plst->data(plst->index(songNumber,1)).toString());
    ui->Genre->setText(plst->data(plst->index(songNumber,2)).toString());
    ui->Year->setText(plst->data(plst->index(songNumber,3)).toString());
    ui->Energy->setText(plst->data(plst->index(songNumber,4)).toString());
    ui->Danceablitity->setText(plst->data(plst->index(songNumber,5)).toString());
    ui->Duration->setText(plst->data(plst->index(songNumber,6)).toString());
}
