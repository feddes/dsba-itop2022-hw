#ifndef EDITWINDOW_H
#define EDITWINDOW_H

#include <QDialog>
#include <QStandardItemModel>

namespace Ui {
class EditWindow;
}

class EditWindow : public QDialog
{
    Q_OBJECT

public:
    explicit EditWindow(QWidget *parent = nullptr, QStringList* lst = {});
    ~EditWindow();

        void setPointers(QStandardItemModel *model, int row);
private slots:
        void on_pushButton_clicked();

private:
    Ui::EditWindow *ui;
    QStandardItemModel *model;
    int songNumber;
    QStringList* lst;
};

#endif // EDITWINDOW_H
