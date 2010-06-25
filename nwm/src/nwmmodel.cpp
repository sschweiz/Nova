#include <QStringList>
#include <QtDebug>
#include "nwmtreeitem.h"
#include "nwmmodel.h"

nwmModel::nwmModel(nwmTreeItem *root, QObject *parent) : QAbstractItemModel(parent)
{
    rootItem = root;
}

nwmModel::~nwmModel()
{
    delete rootItem;
}

QModelIndex nwmModel::index(int row, int column, const QModelIndex &parent) const
{
    nwmTreeItem *pNode;

    if (!parent.isValid()) {
        pNode = rootItem;
    } else {
        pNode = reinterpret_cast<nwmTreeItem *>(parent.internalPointer());
    }

    if (!pNode) return QModelIndex();
    if ((column < 0) || (column > 1) || (row < 0) || (row >= pNode->childCount())) return QModelIndex();

    return createIndex(row, column, pNode->child(row));
}

QModelIndex nwmModel::findChildVariable(const QString &name, const QModelIndex &parent) const
{
    QStringList l;
    nwmTreeItem *pNode;
    int j, i;

    if (!parent.isValid()) {
        pNode = rootItem;
    } else {
        pNode = reinterpret_cast<nwmTreeItem *>(parent.internalPointer());
    }

    if (!pNode) return QModelIndex();

    l = name.split(".", QString::SkipEmptyParts);
    for (j = 0; j < l.size(); j++) {
        for (i = 0; i < pNode->childCount(); i++) {
            if (l.at(j).compare(pNode->child(i)->name()) == 0) {
                if (j == (l.size()-1)) {
                    return createIndex(i, 0, pNode->child(i)); // always just get the 0 column child (it's just how trees work)
                } else {
                    pNode = pNode->child(i);
                    break;
                }
            }
        }
    }

    return QModelIndex();
}

QModelIndex nwmModel::parent(const QModelIndex &index) const
{
    if (!index.isValid()) return QModelIndex();
    int row = -1, i;

    nwmTreeItem *pNode = reinterpret_cast<nwmTreeItem *>(index.internalPointer());

    if (!pNode) return QModelIndex();
    if ((!pNode->parent()) || (!pNode->parent()->parent())) return QModelIndex();

    for (i = 0; i < pNode->parent()->parent()->childCount(); i++) {
        if (pNode->parent()->parent()->child(i) == pNode->parent()) row = i;
    }

    if (row == -1) return QModelIndex();
    return createIndex(row, 0, pNode->parent());
}

int nwmModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 2;
}

int nwmModel::rowCount(const QModelIndex &parent) const
{
    nwmTreeItem *pNode;

    if (!parent.isValid()) {
        pNode = rootItem;
    } else {
        pNode = reinterpret_cast<nwmTreeItem *>(parent.internalPointer());
        if (parent.column() != 0) return 0;
    }

    if (!pNode) return 0;
    return pNode->childCount();
}

QVariant nwmModel::data(const QModelIndex &index, int role) const
{
    nwmTreeItem *pNode;

    if (!index.isValid()) {
        pNode = rootItem;
    } else {
        pNode = reinterpret_cast<nwmTreeItem *>(index.internalPointer());
    }

    if (!pNode) return QVariant();

    switch (role) {
    case Qt::DisplayRole:
        if (index.column() == 0) {
            return pNode->name();
        } else if (index.column() == 1){
            return pNode->value();
        } else {
            return QVariant();
        }
        break;
    }

    return QVariant();
}

Qt::ItemFlags nwmModel::flags(const QModelIndex &index) const
{
    if (!index.isValid()) return 0;

    return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

QVariant nwmModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if ((orientation == Qt::Horizontal) && (role == Qt::DisplayRole)) {
        if (section == 0) {
            return rootItem->name();
        } else {
            return rootItem->value();
        }
    }

    return QVariant();
}
