#ifndef PLAYLISTWINDOW_H
#define PLAYLISTWINDOW_H

#include <QDialog>
#include <QStandardItemModel>
#include <vector>
#include <set>
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
                            QStandardItemModel *plst = nullptr, QStringList *lst = {});
    ~playlistWindow();

    void insertRow(Song sng, int i);

   private slots:

    void on_Info_clicked();

    void on_SavePlaylist_clicked();

    void on_Artist_textChanged(const QString &arg1);

    void on_Del_clicked();

    void on_Genre_currentTextChanged(const QString &arg1);

    void on_loadCSV_clicked();

private:
    Ui::playlistWindow *ui;
    QStandardItemModel *plst;
    ProxyModel *prModel;
    QStringList *lst;
};

#endif  // PLAYLISTWINDOW_H
