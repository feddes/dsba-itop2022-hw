#include "mainwindow.h"
#include <QComboBox>
#include <QFile>
#include <QFileDialog>
#include <QStringList>
#include <QMessageBox>
#include <QStandardItemModel>
#include <fstream>
#include <sstream>
#include <string>
#include <set>
#include "./ui_mainwindow.h"
#include "aboutwindow.h"
#include "addwindow.h"
#include "playlistwindow.h"
#include "song.h"
#include "editwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->menuFile->addAction("About", this, SLOT(openAbout()));

    std::set<std::string> genres;
    createTable(genres);

    createPlst();

    ui->label->setScaledContents(true);


    // assigning proxyModel to a tableView
    prModel = new ProxyModel();
    prModel->setSourceModel(model);
    ui->tableView->setModel(this->prModel);

    // sorting
    ui->tableView->setSortingEnabled(true);
    ui->tableView->sortByColumn(1, Qt::SortOrder::AscendingOrder);

    // editing blocker
    // The command below disables editing of the rows in the table
     ui->tableView->setEditTriggers(
       QAbstractItemView::EditTrigger::NoEditTriggers);


    // spinBoxes
    ui->minYear->setMinimum(2010);
    ui->minYear->setMaximum(2022);
    ui->minYear->setValue(2010);

    ui->maxYear->setMinimum(2010);
    ui->maxYear->setMaximum(2022);
    ui->maxYear->setValue(2022);

    ui->minDance->setMinimum(0);
    ui->minDance->setMaximum(100);
    ui->minDance->setValue(0);

    ui->maxDance->setMinimum(0);
    ui->maxDance->setMaximum(100);
    ui->maxDance->setValue(100);

    ui->minEnergy->setMinimum(0);
    ui->minEnergy->setMaximum(100);
    ui->minEnergy->setValue(0);

    ui->maxEnergy->setMinimum(0);
    ui->maxEnergy->setMaximum(100);
    ui->maxEnergy->setValue(100);

    ui->minDur->setMinimum(0);
    ui->minDur->setMaximum(1000);
    ui->minDur->setValue(0);

    ui->maxDur->setMinimum(0);
    ui->maxDur->setMaximum(1000);
    ui->maxDur->setValue(1000);

    //ComboBox
    std::set<std::string>::iterator it = genres.begin();
    for (; it != genres.end();++it)
        lst += QString::fromStdString(*it);
    ui->Genre->addItems(lst);
    genres.clear();
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::insertRow(Song sng, int i)
{
    model->insertRows(i, 1);
    // Inserting data of the song in each column of the row
    model->setData(model->index(i, 0),
                   QString::fromStdString(sng.title));
    model->setData(model->index(i, 1),
                   QString::fromStdString(sng.artist));
    model->setData(model->index(i, 2),
                   QString::fromStdString(sng.genre));
    model->setData(model->index(i, 3), (sng.year));
    model->setData(model->index(i, 4), (sng.dance));
    model->setData(model->index(i, 5), (sng.energy));
    model->setData(model->index(i, 6), (sng.duration));
}


void MainWindow::createTable(std::set<std::string>& genres)
{
    model = new QStandardItemModel(0, 7, this);

    model->setHorizontalHeaderItem(0, new QStandardItem("Title"));
    model->setHorizontalHeaderItem(1, new QStandardItem("Artist"));
    model->setHorizontalHeaderItem(2, new QStandardItem("Genre"));
    model->setHorizontalHeaderItem(3, new QStandardItem("Year"));
    model->setHorizontalHeaderItem(4, new QStandardItem("Energy"));
    model->setHorizontalHeaderItem(5, new QStandardItem("Dance"));
    model->setHorizontalHeaderItem(6, new QStandardItem("Duration"));

    // Link the Table model with the table visible in the User Interface (UI)
    ui->tableView->setModel(model);

    std::ifstream inputData("top10s.csv");

    std::string line, token;
    std::getline(inputData, line);
    // we need this trick to skip the first line with the headers
    int i = 0;
    while (std::getline(inputData, line))  // parsing our table
    {
        std::istringstream ss(line);
        std::vector<std::string> lineAsVector;
        while (std::getline(ss, token, ','))
            lineAsVector.push_back(token);
        // storagin all our tokens inside an array to create
        // conSTRUCT songs later on
        Song sng;
        std::string temp;
        for (int i = 1; i < lineAsVector.size() - 13; ++i)
        {
            temp += lineAsVector[i];
            if (i != lineAsVector.size() - 14)
                temp += ",";
        }
        std::string title = temp.substr(1,temp.size()-2);
        std::string art = lineAsVector[lineAsVector.size() - 13];
        std::string gnr = lineAsVector[lineAsVector.size() - 12];
        sng.title = title;
        sng.artist = art.substr(1,art.size()-2);
        sng.genre = gnr.substr(1,gnr.size()-2);
        sng.year = std::stoi(lineAsVector[lineAsVector.size() - 11]);
        sng.energy = std::stoi(lineAsVector[lineAsVector.size() - 9]);
        sng.dance = std::stoi(lineAsVector[lineAsVector.size() - 8]);
        sng.duration = std::stoi(lineAsVector[lineAsVector.size() - 4]);
        genres.insert(sng.genre);
        insertRow(sng,i);
        ++i;
        }
      inputData.close();
}
void MainWindow::createPlst()
{
    plst = new QStandardItemModel(0, 7, this);

    plst->setHorizontalHeaderItem(0, new QStandardItem("Title"));
    plst->setHorizontalHeaderItem(1, new QStandardItem("Artist"));
    plst->setHorizontalHeaderItem(2, new QStandardItem("Genre"));
    plst->setHorizontalHeaderItem(3, new QStandardItem("Year"));
    plst->setHorizontalHeaderItem(4, new QStandardItem("Energy"));
    plst->setHorizontalHeaderItem(5, new QStandardItem("Dance"));
    plst->setHorizontalHeaderItem(6, new QStandardItem("Duration"));
}
void MainWindow::on_Playlist_clicked()
{
    if (plst->rowCount() > 0)
    {
        playlistWindow plw(this, plst, &lst);
        plw.setWindowTitle("Playlist");
        plw.setModal(true);
        plw.exec();
    }
    else
    {
        QMessageBox* msgBox = new QMessageBox(this);
        msgBox->setText("Playlist is empty!");
        msgBox->setMinimumHeight(350);
        msgBox->setMinimumWidth(350);
        msgBox->exec();

    }
}
void MainWindow::on_AddToPlaylist_clicked()
{

    QModelIndex index = this->ui->tableView->currentIndex();
    prModel->mapToSource(index);
    QModelIndex index2 = prModel->mapToSource(index);
    int songNumber = index2.row();
    int i = plst->rowCount();
    QString title = model->data(model->index(songNumber,0)).toString();
    QString artist = model->data(model->index(songNumber,1)).toString();
    QString genre = model->data(model->index(songNumber,2)).toString();
    QString year = model->data(model->index(songNumber,3)).toString();
    QString energy = model->data(model->index(songNumber,4)).toString();
    QString dance = model->data(model->index(songNumber,5)).toString();
    QString dur = model->data(model->index(songNumber,6)).toString();
    int x = 1;;
    for (int j = 0; j < i;++j)
        if((plst->data(plst->index(j,0))) == title)
            x = 0;
    if (x)
    {
        plst->insertRows(i, 1);
        plst->setData(plst->index(i, 0),title);
        plst->setData(plst->index(i, 1),artist);
        plst->setData(plst->index(i, 2),genre);
        plst->setData(plst->index(i, 3),year);
        plst->setData(plst->index(i, 4),energy);
        plst->setData(plst->index(i, 5),dance);
        plst->setData(plst->index(i, 6),dur);
    }
    else
    {
        QMessageBox *msgBox = new QMessageBox(this);
        msgBox->setText("This song is already in playlist!");
        msgBox->setMinimumHeight(350);
        msgBox->setMinimumWidth(350);
        msgBox->exec();
    }
}

void MainWindow::on_SaveCSV_clicked()
{
    QString filename =
        QFileDialog::getSaveFileName(this, "Save file", "", ".csv");
    QFile f(filename);
    QString textData;
    int rows = model->rowCount();
    int columns = model->columnCount();
    f.write("TITLE,ARTIST,TOP GENRE,YEAR,ENERGY,DANCE,DURATION\n");
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
                textData += model->data(model->index(i,j)).toString();
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

void MainWindow::on_DeleteFromPL_clicked()
{
    QModelIndex index = this->ui->tableView->currentIndex();
    prModel->mapToSource(index);
    QModelIndex index2 = prModel->mapToSource(index);
    int songNumber = index2.row();
    model->removeRow(songNumber);

}

void MainWindow::on_Add_clicked()
{
    AddWindow add(this, &lst);
    add.setPointers(model);
    add.setWindowTitle("Adder");
    add.setModal(true);
    add.exec();
}

void MainWindow::openAbout()
{
    AboutWindow abw;
    abw.setWindowTitle("About");
    abw.setVisible(true);
    abw.exec();
}

void MainWindow::on_minDance_valueChanged(int arg1)
{
    prModel->setMinDance(ui->minDance->text().toInt());
}

void MainWindow::on_maxDance_valueChanged(int arg1)
{
    prModel->setMaxDance(ui->maxDance->text().toInt());
}

void MainWindow::on_minEnergy_valueChanged(int arg1)
{
    prModel->setMinEnergy(ui->minEnergy->text().toInt());
}

void MainWindow::on_maxEnergy_valueChanged(int arg1)
{
    prModel->setMaxEnergy(ui->maxEnergy->text().toInt());
}

void MainWindow::on_minDur_valueChanged(int arg1)
{
    prModel->setMinDur(ui->minDur->text().toInt());
}

void MainWindow::on_maxDur_valueChanged(int arg1)
{
    prModel->setMaxDur(ui->maxDur->text().toInt());
}

void MainWindow::on_minYear_valueChanged(int arg1)
{
    prModel->setMinYear(ui->minYear->text().toInt());
}

void MainWindow::on_maxYear_valueChanged(int arg1)
{
    prModel->setMaxYear(ui->maxYear->text().toInt());
}

void MainWindow::on_Artist_textChanged(const QString &arg1)
{
    prModel->setArtist(ui->Artist->text());
}

void MainWindow::on_Genre_currentTextChanged(const QString &arg1)
{
    prModel->setGenre(arg1);
}


void MainWindow::on_pushButton_clicked()
{

    QModelIndex index = this->ui->tableView->currentIndex();
    prModel->mapToSource(index);
    QModelIndex index2 = prModel->mapToSource(index);
    int songNumber = index2.row();

    EditWindow edw(this,&lst);
    edw.setPointers(model, songNumber);
    edw.setModal(true);
    edw.setWindowTitle("Edit");
    edw.exec();
}

