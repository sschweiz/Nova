#ifndef NWMCOMPONENTWIDGET_H
#define NWMCOMPONENTWIDGET_H

#include <QVBoxLayout>

#define NWM_MAX_INPUTS 5

class QGridLayout;
class QVBoxLayout;
class QLabel;
class QToolButton;

struct __nwmComponentInfo;

typedef struct __nwmComponentLink {
    bool sRequired;
    struct __nwmComponentInfo *sLink;
} nwmComponentLink;

typedef struct __nwmComponentInfo {
    QString sName;
    unsigned long sId;
    QList<nwmComponentLink> sInputs;
    nwmComponentLink sOutput;
} nwmComponentInfo;

class nwmComponentWidget : public QVBoxLayout
{
Q_OBJECT
public:
    explicit nwmComponentWidget();

signals:

public slots:

public:
    void UpdateComponent(const nwmComponentInfo &info);
    void clearCommon();

private:
    QGridLayout *m_Common;
    QGridLayout *m_Components;

    QLabel *m_Inputs[NWM_MAX_INPUTS];
    QLabel *m_InLinks[NWM_MAX_INPUTS];
    QLabel *m_InTypes[NWM_MAX_INPUTS];
    QToolButton *m_InConn[NWM_MAX_INPUTS];
    QLabel *m_Output;
    QLabel *m_OutLink;
    QLabel *m_OutType;
    QToolButton *m_OutConn;

    void DoExample();
};

#endif // NWMCOMPONENTWIDGET_H
