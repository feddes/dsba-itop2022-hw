#include "infowindow.h"

#include "ui_infowindow.h"

InfoWindow::InfoWindow(QWidget *parent)
    : QDialog(parent), ui(new Ui::InfoWindow)
{
    ui->setupUi(this);
}

InfoWindow::~InfoWindow() { delete ui; }

void InfoWindow::getData(Song sng)
{
    ui->Title->setText(QString::fromStdString(sng.title));
    ui->Artist->setText(QString::fromStdString(sng.artist));
    ui->Genre->setText(QString::fromStdString(sng.genre));
    ui->Year->setText(QString::number(sng.year));
    ui->Energy->setText(QString::number(sng.energy));
    ui->Danceablitity->setText(QString::number(sng.dance));
    ui->Duration->setText(QString::number(sng.duration));
}
