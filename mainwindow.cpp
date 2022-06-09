#include "mainwindow.h"

#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QStandardItemModel>
#include <fstream>
#include <sstream>

#include "./ui_mainwindow.h"
#include "aboutwindow.h"
#include "addwindow.h"
#include "playlistwindow.h"
#include "song.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->menuFile->addAction("About", this, SLOT(openAbout()));

    createTable();

    ui->label->setScaledContents(true);

    // assigning proxyModel to a tableView
    prModel = new ProxyModel();
    prModel->setSourceModel(model);
    ui->tableView->setModel(this->prModel);

    // sorting
    ui->tableView->setSortingEnabled(true);
    ui->tableView->sortByColumn(1, Qt::SortOrder::AscendingOrder);

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
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::createTable()
{
    model = new QStandardItemModel(0, 6, this);

    model->setHorizontalHeaderItem(0, new QStandardItem("Title"));
    model->setHorizontalHeaderItem(1, new QStandardItem("Artist"));
    model->setHorizontalHeaderItem(2, new QStandardItem("Genre"));
    model->setHorizontalHeaderItem(3, new QStandardItem("Year"));
    model->setHorizontalHeaderItem(4, new QStandardItem("Energy"));
    model->setHorizontalHeaderItem(5, new QStandardItem("Dance"));
    model->setHorizontalHeaderItem(6, new QStandardItem("Duration"));

    // Link the Table model with the table visible in the User Interface (UI)
    ui->tableView->setModel(model);

    // The command below disables editing of the rows in the table
    // ui->tableView->setEditTriggers(
    //   QAbstractItemView::EditTrigger::NoEditTriggers);

    std::ifstream inputData("top10s.csv");

    std::string line, token;
    std::getline(inputData, line);
    // we need this trick to skip the first line with the headers

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
        sng.title = temp;
        sng.artist = lineAsVector[lineAsVector.size() - 13];
        sng.genre = lineAsVector[lineAsVector.size() - 12];
        sng.year = std::stoi(lineAsVector[lineAsVector.size() - 11]);
        sng.energy = std::stoi(lineAsVector[lineAsVector.size() - 9]);
        sng.dance = std::stoi(lineAsVector[lineAsVector.size() - 8]);
        sng.duration = std::stoi(lineAsVector[lineAsVector.size() - 4]);
        this->vec.push_back(sng);
    }
    inputData.close();

    for (int i = 0; i < vec.size(); i++)
    {
        model->insertRows(i, 1);
        // Inserting data of the city in each column of the row
        model->setData(model->index(i, 0),
                       QString::fromStdString(vec[i].title));
        model->setData(model->index(i, 1),
                       QString::fromStdString(vec[i].artist));
        model->setData(model->index(i, 2),
                       QString::fromStdString(vec[i].genre));
        model->setData(model->index(i, 3), (vec[i].year));
        model->setData(model->index(i, 4), (vec[i].dance));
        model->setData(model->index(i, 5), (vec[i].energy));
        model->setData(model->index(i, 6), (vec[i].duration));
    }
}

void MainWindow::on_Playlist_clicked()
{
    playlistWindow plw(this, plst);
    plw.setWindowTitle("Playlist");
    plw.setModal(true);
    plw.exec();
}

void MainWindow::on_AddToPlaylist_clicked()
{
    QModelIndex index = this->ui->tableView->currentIndex();
    prModel->mapToSource(index);
    QModelIndex index2 = prModel->mapToSource(index);
    int songNumber = index2.row();
    plst.push_back(vec[songNumber]);
}

void MainWindow::on_SaveCSV_clicked()
{
    QString filename =
        QFileDialog::getSaveFileName(this, "Save file", "", ".csv");

    QFile f(filename);
    f.open(QIODevice::WriteOnly);
    f.write("TITLE,ARTIST,TOP GENRE,YEAR,ENERGY,DANCE,DURATION\n");

    for (int i = 0; i < vec.size(); i++)
    {
        std::stringstream ss;
        ss << vec[i].title << "," << vec[i].artist << "," << vec[i].genre << ","
           << vec[i].year << "," << vec[i].energy << "," << vec[i].dance << ","
           << vec[i].duration << '\n';
        f.write(ss.str().c_str());
    }
    f.close();
}

void MainWindow::on_DeleteFromPL_clicked()
{
    QModelIndex index = this->ui->tableView->currentIndex();
    prModel->mapToSource(index);
    QModelIndex index2 = prModel->mapToSource(index);
    int songNumber = index2.row();
    std::cout << vec[songNumber].title;

    int x = -1;
    for (int i = 0; i < plst.size(); ++i)
        if (vec[songNumber].title == plst[i].title)
            x = i;
    if (x == -1)
    {
        QMessageBox *msgBox = new QMessageBox(this);
        msgBox->setText("Song is not in the playlist!");
        msgBox->setMinimumHeight(350);
        msgBox->setMinimumWidth(350);
        msgBox->exec();
    }
    // delete the song from vector
    else
    {
        std::vector<Song>::iterator it = this->plst.begin() + x;
        this->plst.erase(it);
    }
}

void MainWindow::on_Add_clicked()
{
    AddWindow add;
    Song newSong;
    this->vec.push_back(newSong);
    add.setPointers(&vec[vec.size() - 1], model);
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

void MainWindow::on_Genre_textChanged(const QString &arg1)
{
    prModel->setGenre(ui->Genre->text());
}
