#include "aboutwindow.h"

#include <Qpen>

#include "ui_aboutwindow.h"

AboutWindow::AboutWindow(QWidget *parent)
    : QDialog(parent), ui(new Ui::AboutWindow)
{
    ui->setupUi(this);
}

AboutWindow::~AboutWindow() { delete ui; }

void AboutWindow::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);

    // painter.setPen(Qt::white);
    // painter.setBrush(QBrush(QBrush(Qt::white)));
    // painter.drawEllipse(100, 150, 150, 150);

    painter.setPen(Qt::black);
    painter.setBrush(QBrush(QBrush(Qt::black)));
    painter.drawRect(150, 150, 200, 200);

    painter.setPen(QPen(Qt::white, 14));
    painter.setBrush(QBrush(QBrush(Qt::white)));
    painter.drawLine(160, 340, 340, 340);
    painter.drawLine(160, 160, 340, 160);
    painter.drawLine(158, 338, 340, 162);

    // Loading the double-headed bizantine eagle
    // QImage image;
    // image.load("eagle.png");
    // QImage scaledImage = image.scaled(50, 50, Qt::KeepAspectRatio);
    // painter.drawImage(38, 55, scaledImage);
}
