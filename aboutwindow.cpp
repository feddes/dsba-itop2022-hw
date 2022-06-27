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

    painter.setPen(Qt::black);
    painter.setBrush(QBrush(QBrush(Qt::black)));
    painter.drawRect(150, 150, 200, 200);

    painter.setPen(QPen(Qt::white, 14));
    painter.setBrush(QBrush(QBrush(Qt::white)));
    painter.drawLine(160, 340, 340, 340);
    painter.drawLine(160, 160, 340, 160);
    painter.drawLine(158, 338, 340, 162);

}
