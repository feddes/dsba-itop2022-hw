#include "playlistwindow.h"
#include <QTextStream>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <sstream>
#include <fstream>
#include "infowindow.h"
#include "song.h"
#include "ui_playlistwindow.h"

playlistWindow::playlistWindow(QWidget* parent,QStandardItemModel *plst, QStringList *lst)
                         : QDialog(parent), ui(new Ui::playlistWindow)
{
    ui->setupUi(this);

    ui->label->setScaledContents(true);

    this->plst = plst;
    this->lst = lst;
    // assigning proxyModel to a tableView
    prModel = new ProxyModel(this,true);
    prModel->setSourceModel(plst);
    ui->tableViewPlst->setModel(this->prModel);
    // sorting
    ui->tableViewPlst->setSortingEnabled(true);
    ui->tableViewPlst->sortByColumn(1, Qt::SortOrder::AscendingOrder);

    // The command below disables editing of the rows in the table
    ui->tableViewPlst->setEditTriggers(
        QAbstractItemView::EditTrigger::NoEditTriggers);

    ui->tableViewPlst->setColumnHidden(3, true);
    ui->tableViewPlst->setColumnHidden(4, true);
    ui->tableViewPlst->setColumnHidden(5, true);
    ui->tableViewPlst->setColumnHidden(6, true);

    //ComboBox setup
    ui->Genre->addItems(*lst);


}

void playlistWindow::insertRow(Song sng, int i)
{
    plst->insertRows(i, 1);
    // Inserting data of the song in each column of the row
    plst->setData(plst->index(i, 0),
                   QString::fromStdString(sng.title));
    plst->setData(plst->index(i, 1),
                   QString::fromStdString(sng.artist));
    plst->setData(plst->index(i, 2),
                   QString::fromStdString(sng.genre));
    plst->setData(plst->index(i, 3), (sng.year));
    plst->setData(plst->index(i, 4), (sng.dance));
    plst->setData(plst->index(i, 5), (sng.energy));
    plst->setData(plst->index(i, 6), (sng.duration));
}

playlistWindow::~playlistWindow() { delete ui; }

void playlistWindow::on_Info_clicked()
{
    QModelIndex index = this->ui->tableViewPlst->currentIndex();
    QModelIndex index2 = prModel->mapToSource(index);
    int songNumber = index2.row();

    if (plst == nullptr || plst->rowCount() == 0)
    {
        QMessageBox* msgBox = new QMessageBox(this);
        msgBox->setText("Playlist is empty!");
        msgBox->setMinimumHeight(350);
        msgBox->setMinimumWidth(350);
        msgBox->exec();
    }
    else
    {
        InfoWindow inf;
        inf.getData(plst, songNumber);
        inf.setWindowTitle("Information");
        inf.setModal(true);
        inf.exec();
    }
}

void playlistWindow::on_SavePlaylist_clicked()
{
    QString filename =
        QFileDialog::getSaveFileName(this, "Save file", "", ".csv");
    QFile f(filename);
    QString textData;
    f.write("TITLE,ARTIST,TOP GENRE,YEAR,ENERGY,DANCE,DURATION\n");
    int rows = plst->rowCount();
    int columns = plst->columnCount();
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
                textData += plst->data(plst->index(i,j)).toString();
                textData += "," ;
        }
        textData += "\n";
    }

    if(f.open(QIODevice::WriteOnly | QIODevice::Truncate))
    {
        QTextStream out(&f);
        out << textData;
        f.close();
    }
}

void playlistWindow::on_Artist_textChanged(const QString& arg1)
{
    prModel->setArtist(ui->Artist->text());
}

void playlistWindow::on_Genre_currentTextChanged(const QString &arg1)
{
    prModel->setGenre(arg1);
}


void playlistWindow::on_Del_clicked()
{
      QModelIndex index = this->ui->tableViewPlst->currentIndex();
      prModel->mapToSource(index);
      QModelIndex index2 = prModel->mapToSource(index);
      int songNumber = index2.row();
      if (plst->rowCount() == 0)
      {
          QMessageBox *msgBox = new QMessageBox(this);
          msgBox->setText("No songs in the playlist!");
          msgBox->setMinimumHeight(350);
          msgBox->setMinimumWidth(350);
          msgBox->exec();
      }
      // delete the song from vector
      else
        plst->removeRow(songNumber);

}
void playlistWindow::on_loadCSV_clicked()
{
    plst->removeRows(0,plst->rowCount());

    QString filename = QFileDialog::getOpenFileName(this, "Load file", "");
    QFile inputFile(filename);
    inputFile.open(QIODevice::ReadOnly);
    int i = 0;
    std::string line;
    while (!inputFile.atEnd())  // parsing our table
    {
        line = inputFile.readLine().toStdString();
        std::istringstream ss(line);
        std::string token;
        std::vector<std::string> lineAsVector;
        while(std::getline(ss, token, ','))
             lineAsVector.push_back(token);
        // storing all our tokens inside an array to create plst
        // conSTRUCT songs later on
        Song sng;
        sng.title = lineAsVector[lineAsVector.size() - 8];
        sng.artist = lineAsVector[lineAsVector.size() - 7];
        sng.genre = lineAsVector[lineAsVector.size() - 6];
        sng.year = std::stoi(lineAsVector[lineAsVector.size() - 5]);
        sng.energy = std::stoi(lineAsVector[lineAsVector.size() - 4]);
        sng.dance = std::stoi(lineAsVector[lineAsVector.size() - 3]);
        sng.duration = std::stoi(lineAsVector[lineAsVector.size() - 2]);
        insertRow(sng,i);
        ++i;

    }
    inputFile.close();

}
