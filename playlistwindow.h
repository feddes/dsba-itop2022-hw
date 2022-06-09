#ifndef PLAYLISTWINDOW_H
#define PLAYLISTWINDOW_H

#include <QDialog>
#include <QStandardItemModel>
#include <vector>

#include "proxymodel.h"
#include "song.h"

namespace Ui
{
class playlistWindow;
}

class playlistWindow : public QDialog
{
    Q_OBJECT

   public:
    explicit playlistWindow(QWidget *parent = nullptr,
                            const std::vector<Song> &plst = {});
    ~playlistWindow();

    void createPlayList();

   private slots:

    void on_Info_clicked();

    void on_SavePlaylist_clicked();

    void on_Artist_textChanged(const QString &arg1);

    void on_Genre_textChanged(const QString &arg1);

   private:
    Ui::playlistWindow *ui;
    QStandardItemModel *model;
    const std::vector<Song> &plst;
    ProxyModel *prModel;
};

#endif  // PLAYLISTWINDOW_H
