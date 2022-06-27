#ifndef ADDWINDOW_H
#define ADDWINDOW_H
#include <QDialog>
#include <QStandardItemModel>

#include "song.h"
namespace Ui
{
class AddWindow;
}

class AddWindow : public QDialog
{
    Q_OBJECT

   public:
    explicit AddWindow(QWidget *parent = nullptr, QStringList *lst = {});
    ~AddWindow();

    void setPointers(QStandardItemModel *model);

   private slots:
    void on_Add_clicked();

   private:
    Ui::AddWindow *ui;
    QStandardItemModel *model;
    QStringList *lst;
};

#endif  // ADDWINDOW_H
