#include <QStringList>
#include "nwmTreeItem.h"

nwmTreeItem::nwmTreeItem(const QString &name, const QVariant &value, nwmInternalData internal, nwmTreeItem *parent)
{
    parentItem = parent;
    m_varName = name;
    m_varValue = value;
    m_varInternal = internal;
}

nwmTreeItem::nwmTreeItem(const QString &name, const QVariant &value, nwmTreeItem *parent)
{
    parentItem = parent;
    m_varName = name;
    m_varValue = value;
}

nwmTreeItem::~nwmTreeItem()
{
    qDeleteAll(childItems);
}

void nwmTreeItem::appendChild(nwmTreeItem *item)
{
    childItems.append(item);
}

nwmTreeItem *nwmTreeItem::child(int index)
{
    return childItems.value(index);
}

int nwmTreeItem::childCount() const
{
    return childItems.count();
}

nwmTreeItem *nwmTreeItem::parent()
{
    return parentItem;
}

const QString &nwmTreeItem::name()
{
    return m_varName;
}

QVariant nwmTreeItem::value()
{
    return m_varValue;
}

void nwmTreeItem::setInternalData(nwmInternalData internal)
{
    m_varInternal = internal;
}
