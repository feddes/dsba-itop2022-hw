#include "playlistwindow.h"

#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <sstream>

#include "infowindow.h"
#include "song.h"
#include "ui_playlistwindow.h"

playlistWindow::playlistWindow(QWidget* parent, const std::vector<Song>& plst)
    : QDialog(parent), ui(new Ui::playlistWindow), plst(plst)
{
    ui->setupUi(this);
    createPlayList();

    ui->label->setScaledContents(true);

    // assigning proxyModel to a tableView
    prModel = new ProxyModel();
    prModel->setSourceModel(model);
    ui->tableView->setModel(this->prModel);

    // sorting
    ui->tableView->setSortingEnabled(true);
    ui->tableView->sortByColumn(1, Qt::SortOrder::AscendingOrder);
}

playlistWindow::~playlistWindow() { delete ui; }

void playlistWindow::createPlayList()
{
    model = new QStandardItemModel(0, 3, this);

    model->setHorizontalHeaderItem(0, new QStandardItem("Title"));
    model->setHorizontalHeaderItem(1, new QStandardItem("Artist"));
    model->setHorizontalHeaderItem(2, new QStandardItem("Genre"));

    // Link the Table model with the table visible in the User Interface (UI)
    ui->tableView->setModel(model);

    // The command below disables editing of the rows in the table
    ui->tableView->setEditTriggers(
        QAbstractItemView::EditTrigger::NoEditTriggers);

    for (int i = 0; i < plst.size(); i++)
    {
        model->insertRows(i, 1);
        // Inserting data of the city in each column of the row
        model->setData(model->index(i, 0),
                       QString::fromStdString(plst[i].title));
        model->setData(model->index(i, 1),
                       QString::fromStdString(plst[i].artist));
        model->setData(model->index(i, 2),
                       QString::fromStdString(plst[i].genre));
    }
}

void playlistWindow::on_Info_clicked()
{
    QModelIndex index = this->ui->tableView->currentIndex();
    prModel->mapToSource(index);
    QModelIndex index2 = prModel->mapToSource(index);
    int songNumber = index2.row();
    InfoWindow inf;
    if (plst.size() == 0)
    {
        QMessageBox* msgBox = new QMessageBox(this);
        msgBox->setText("Playlist is empty!");
        msgBox->setMinimumHeight(350);
        msgBox->setMinimumWidth(350);
        msgBox->exec();
    }
    else
    {
        inf.getData(plst[songNumber]);
        inf.setWindowTitle("Information");
        setModal(true);
        inf.exec();
    }
}

void playlistWindow::on_SavePlaylist_clicked()
{
    QString filename =
        QFileDialog::getSaveFileName(this, "Save file", "", ".csv");

    QFile f(filename);
    f.open(QIODevice::WriteOnly);
    f.write("TITLE,ARTIST,TOP GENRE,YEAR,ENERGY,DANCE,DURATION\n");

    for (int i = 0; i < plst.size(); i++)
    {
        std::stringstream ss;
        ss << plst[i].title << "," << plst[i].artist << "," << plst[i].genre
           << "," << plst[i].year << "," << plst[i].energy << ","
           << plst[i].dance << "," << plst[i].duration << '\n';
        f.write(ss.str().c_str());
    }
    f.close();
}

void playlistWindow::on_Artist_textChanged(const QString& arg1)
{
    prModel->setArtist(ui->Artist->text());
}

void playlistWindow::on_Genre_textChanged(const QString& arg1)
{
    prModel->setGenre(ui->Genre->text());
}
