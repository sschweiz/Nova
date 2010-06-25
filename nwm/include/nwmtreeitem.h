#ifndef NWMTREEITEM_H
#define NWMTREEITEM_H

#include <QList>
#include <QVariant>

/* Saving data in Nova

                [ Data Serialization]
   [nwmModel]<->[   QDataStream     ]<->[Device]
       ^v       [   tpl             ]
     [Data]

   Data is stored in memory in the nwmModel structure according to Model/View ideology.
   The actual access to the data is through a nwmTreeItem subclass.  To save information
   about the current process, all that Nova needs to do is serialize the nwmModel class
   and dump it to disk.  This saves all information about all forms and containers in
   the engine.  It does NOT hold state information.  This is held by Qt, presumably in
   the user's registry or home directory.
 */

typedef struct __nwmInternalData
{
    QString sEquation;
    QString sUnit;
    QVariant sMetaColor;
    QVariant sMetaDateTime;
    QVariant sMetaSize;
    unsigned int sType; // data type (for the DDE)
    bool sUpToDate; // data value is up-to-date as determined by the dynamic data engine
    unsigned int sEditFlag; // specifies what can be edited (either name, value, both, none)
} nwmInternalData;

/* Here, we want to hold only certain types of information:
    Public information, and internal variable information

    The public information consists of a variable name: QString
    and a value: QVariant

    The internal information is held in nwmInternalData structure
    This information is supplied to affect the drawing of the delegate.

    QString         m_varName;
    QVariant        m_varValue;
    nwmInternalData m_varInternal;

    The number of columns should therefore be 2 (since internal data
    is not shown).
*/

class nwmTreeItem
{
public:
    nwmTreeItem(const QString &name, const QVariant &value, nwmInternalData internal,
                nwmTreeItem *parent = 0);
    nwmTreeItem(const QString &name, const QVariant &value, nwmTreeItem *parent = 0);
    ~nwmTreeItem();

    nwmTreeItem *child(int index);
    int childCount() const;
    nwmTreeItem *parent();

    void appendChild(nwmTreeItem *item);

public:
    const QString &name();
    QVariant value();
    void setInternalData(nwmInternalData internal);

public:
    enum nwmItemRole { nwmEquationRole = Qt::UserRole, nwmUnitRole, nwmFunctionRole };

private:
    QString         m_varName;
    QVariant        m_varValue;
    nwmInternalData m_varInternal;

    QList<nwmTreeItem *> childItems;
    nwmTreeItem *parentItem;
};

#endif // NWMTREEITEM_H
