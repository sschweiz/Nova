#ifndef NWMMODEL_H
#define NWMMODEL_H

#include <QAbstractItemModel>
#include <QModelIndex>
#include <QVariant>

#include "nwmtreeitem.h"

class nwmModel : public QAbstractItemModel
{
Q_OBJECT

public:
    nwmModel(nwmTreeItem *root, QObject *parent = 0);
    ~nwmModel();

    QVariant data(const QModelIndex &index, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const;
    QModelIndex parent(const QModelIndex &index) const;

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;

    QModelIndex findChildVariable(const QString &name, const QModelIndex &parent = QModelIndex()) const;
	 
private:
    nwmTreeItem *rootItem;
};

#endif // NWMMODEL_H
