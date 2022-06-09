#ifndef INFOWINDOW_H
#define INFOWINDOW_H

#include <QDialog>
#include <QStringListModel>

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
    void getData(Song sng);

   private:
    Ui::InfoWindow *ui;
    Song *sng;
};

#endif  // INFOWINDOW_H
