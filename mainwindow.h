#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <vector>

#include "proxymodel.h"
#include "song.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
    friend class playlistWindow;

   public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void createTable();

   private slots:

    void on_Playlist_clicked();

    void on_AddToPlaylist_clicked();

    void on_SaveCSV_clicked();

    void on_DeleteFromPL_clicked();

    void on_Add_clicked();

    void on_minDance_valueChanged(int arg1);

    void on_maxDance_valueChanged(int arg1);

    void on_minEnergy_valueChanged(int arg1);

    void on_maxEnergy_valueChanged(int arg1);

    void on_minDur_valueChanged(int arg1);

    void on_maxDur_valueChanged(int arg1);

    void on_minYear_valueChanged(int arg1);

    void on_maxYear_valueChanged(int arg1);

    void on_Artist_textChanged(const QString &arg1);

    void on_Genre_textChanged(const QString &arg1);

    void openAbout();

   private:
    Ui::MainWindow *ui;
    QStandardItemModel *model;
    std::vector<Song> vec;
    std::vector<Song> plst;
    ProxyModel *prModel;
};
#endif  // MAINWINDOW_H
