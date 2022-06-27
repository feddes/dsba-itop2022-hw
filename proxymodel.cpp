#include "proxymodel.h"

#include <iostream>

ProxyModel::ProxyModel(QObject* parent, bool flag) : QSortFilterProxyModel(parent)
{
    minDance = 0;
    minEnergy = 0;
    minDur = 0;
    minYear = 2010;
    maxDance = INT_MAX;
    maxEnergy = INT_MAX;
    maxDur = INT_MAX;
    maxYear = 2022;
    artist = QString();
    genre = QString();
    this->flag = flag;
}

void ProxyModel::setArtist(QString artist)
{
    this->artist = artist.trimmed().isEmpty() ? QString() : artist;
    invalidateFilter();
}

void ProxyModel::setGenre(QString genre)
{
    this->genre = genre.trimmed() == "All" ? QString() : genre;
    invalidateFilter();
}

void ProxyModel::setMinDance(int minDance)
{
    this->minDance = minDance;
    invalidateFilter();
}

void ProxyModel::setMaxDance(int maxDance)
{
    this->maxDance = maxDance;
    invalidateFilter();
}

void ProxyModel::setMinEnergy(int minEnergy)
{
    this->minEnergy = minEnergy;
    invalidateFilter();
}

void ProxyModel::setMaxEnergy(int maxEnergy)
{
    this->maxEnergy = maxEnergy;
    invalidateFilter();
}

void ProxyModel::setMinDur(int minDur)
{
    this->minDur = minDur;
    invalidateFilter();
}

void ProxyModel::setMaxDur(int maxDur)
{
    this->maxDur = maxDur;
    invalidateFilter();
}

void ProxyModel::setMinYear(int minYear)
{
    this->minYear = minYear;
    invalidateFilter();
}

void ProxyModel::setMaxYear(int maxYear)
{
    this->maxYear = maxYear;
    invalidateFilter();
}

bool ProxyModel::filterAcceptsRow(int sourceRow,
                                  const QModelIndex& sourceParent) const
{
    if (flag)
    {
        QModelIndex index2 = sourceModel()->index(
            sourceRow, 2,
            sourceParent);  // 2 stands for genre, just like in the table
        QString rowGenre = sourceModel()->data(index2).toString();

        QModelIndex index1 = sourceModel()->index(
            sourceRow, 1,
            sourceParent);  // 1 stands for artist, just like in the table
        QString rowArtist = sourceModel()->data(index1).toString();

        //filter playlist

        if (this->artist.trimmed().isEmpty() && this->genre.trimmed().isEmpty())
            return true;
        else if (this->artist.trimmed().isEmpty())
            return this->genre == rowGenre;
        else if (this->genre.trimmed().isEmpty())
            return this->artist == rowArtist;
        return this->artist == rowArtist && this->genre == rowGenre;
    }

    else
    {
        //filter mainwindow
        QModelIndex index6 = sourceModel()->index(
            sourceRow, 6,
            sourceParent);  // 6 stands for duration, just like in the table
        int duration = sourceModel()->data(index6).toInt();

        QModelIndex index5 = sourceModel()->index(
            sourceRow, 5,
            sourceParent);  // 5 stands for energy, just like in the table
        int energy = sourceModel()->data(index5).toInt();

        QModelIndex index4 = sourceModel()->index(
            sourceRow, 4,
            sourceParent);  // 4 stands for danceability, just like in the table
        int dance = sourceModel()->data(index4).toInt();

        QModelIndex index3 = sourceModel()->index(
            sourceRow, 3,
            sourceParent);  // 3 stands for year, just like in the table
        int year = sourceModel()->data(index3).toInt();

        QModelIndex index2 = sourceModel()->index(
        sourceRow, 2,
            sourceParent);  // 2 stands for genre, just like in the table
        QString rowGenre = sourceModel()->data(index2).toString();

        QModelIndex index1 = sourceModel()->index(
            sourceRow, 1,
            sourceParent);  // 1 stands for artist, just like in the table
        QString rowArtist = sourceModel()->data(index1).toString();

        bool filters = (this->minYear < year && year < this->maxYear) &&
                (this->minEnergy < energy && energy < this->maxEnergy) &&
                (this->minDance < dance && dance < this->maxDance) &&
                (this->minDur < duration && duration < this->maxDur);


        if (this->artist.trimmed().isEmpty() && (this->genre.trimmed().isEmpty()))
            return filters;
        else if (this->artist.trimmed().isEmpty())
        {
            return this->genre == rowGenre && filters;
        }
        else if (this->genre.trimmed().isEmpty())
        {
            return this->artist == rowArtist && filters;
        }
        else
        {
            return filters && this->artist == rowArtist && this->genre == rowGenre;
        }
    }
}

bool ProxyModel::lessThan(const QModelIndex& left,
                          const QModelIndex& right) const
{
    QString stringA = sourceModel()->data(left).toString();
    QString stringB = sourceModel()->data(right).toString();

    return stringA < stringB;
}
