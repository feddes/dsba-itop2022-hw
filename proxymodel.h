#ifndef PROXYMODEL_H
#define PROXYMODEL_H

#include <QSortFilterProxyModel>

class ProxyModel : public QSortFilterProxyModel

{
   public:
    //flag == true => playlist; flag == false => mainwindow;
    ProxyModel(QObject* parent = 0, bool flag = false);

    QString getArtist() const { return this->artist; }
    QString getGenre() const { return this->genre; }

    int getMinDance() const { return this->minDance; }
    int getMaxDance() const { return this->maxDance; }

    int getMinEnergy() const { return this->minEnergy; }
    int getMaxEnergy() const { return this->maxEnergy; }

    int getMinDur() const { return this->minDur; }
    int getMaxDur() const { return this->maxDur; }

    int getMinYear() const { return this->minYear; }
    int getMaxYear() const { return this->maxYear; }

    void setArtist(QString artist);
    void setGenre(QString genre);

    void setMinDance(int minDance);
    void setMaxDance(int maxDance);

    void setMinEnergy(int Energy);
    void setMaxEnergy(int Energy);

    void setMinDur(int minDur);
    void setMaxDur(int maxDur);

    void setMinYear(int minYear);
    void setMaxYear(int maxYear);

   protected:
    bool filterAcceptsRow(int sourceRow, const QModelIndex& sourceParent)
        const override;  // filtering

    bool lessThan(const QModelIndex& left,
                  const QModelIndex& right) const override;  // sorting

   private:
    QString artist, genre;
    int minDance, minEnergy, minDur;
    int maxDance, maxEnergy, maxDur;
    int minYear, maxYear;
    bool flag;
};

#endif  // PROXYMODEL_H
