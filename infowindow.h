#ifndef INFOWINDOW_H
#define INFOWINDOW_H

#include <QDialog>
#include <QStandardItemModel>

#include "song.h"

namespace Ui
{
class InfoWindow;
}

class InfoWindow : public QDialog
{
    Q_OBJECT

   public:
    explicit InfoWindow(QWidget *parent = nullptr);
    ~InfoWindow();
    void getData(QStandardItemModel *plst, int songNumber);

   private:
    Ui::InfoWindow *ui;
};

#endif  // INFOWINDOW_H
