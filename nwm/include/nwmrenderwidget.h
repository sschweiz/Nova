#ifndef NWMRENDERWIDGET_H
#define NWMRENDERWIDGET_H

#include <QMainWindow>
#include <QWidget>
#include "nwmrender.h"
#include "nwmcomponentwidget.h"

QT_BEGIN_NAMESPACE
class QComboBox;
class QPushButton;
class QGroupBox;
class QGraphicsView;
class QStackedLayout;
QT_END_NAMESPACE

class nwmRenderWidget : public QWidget
{
Q_OBJECT
public:
    nwmRenderWidget();
    void setUseOnly(int n);

signals:

public slots:
    void Rerender(int index);
    void Dock(bool d);
    void showProps();

private:
    void PopulateToolbar();
    int m_useOnly;
    bool z_safe;

public:
    QToolBar *m_Toolbar;
    QComboBox *m_ContentCombo;
    QAction *m_ComboAction;
    QAction *m_DefaultButtons[3];
    QPushButton *m_btnResult;
    QGroupBox *m_ComponentBox;
    QStackedLayout *m_Views;

public:
    // Process Manager
    nwmRender *m_Render;
    nwmComponentWidget *m_Components;

    // Preferences
    QGroupBox *m_Preferences;
    // DAG
    QGraphicsView *m_DAG;

private:
    void setupPM();
    void setupDAG();
    void setupPreferences();
};

#endif // NWMRENDERWIDGET_H
