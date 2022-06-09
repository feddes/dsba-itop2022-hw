#ifndef ABOUTWINDOW_H
#define ABOUTWINDOW_H

#include <QDialog>
#include <QtCore>
#include <QtGui>
namespace Ui
{
class AboutWindow;
}

class AboutWindow : public QDialog
{
    Q_OBJECT

   public:
    explicit AboutWindow(QWidget *parent = nullptr);
    ~AboutWindow();

   protected:
    // Overwrite the method paint() - each we show the MainWindow, we will call
    // the method paint()
    void paintEvent(QPaintEvent *e);

   private:
    Ui::AboutWindow *ui;
};

#endif  // ABOUTWINDOW_H
