#ifndef NWMPROPERTYWIDGET_H
#define NWMPROPERTYWIDGET_H

#include <QPlainTextEdit>
#include <QWidget>


QT_BEGIN_NAMESPACE
class QVBoxLayout;
class QFormLayout;
class QLineEdit;
class QTreeView;
class QToolBar;
class QGroupBox;
class QDialogButtonBox;
QT_END_NAMESPACE

class nwmPropDescriptionTextEdit : public QPlainTextEdit {
public:
    nwmPropDescriptionTextEdit(QWidget* parent = 0) : QPlainTextEdit(parent) { }
    virtual QSize sizeHint() const { return QSize(0, 25); }
};

class nwmPropertyWidget : public QWidget
{
Q_OBJECT
public:
    explicit nwmPropertyWidget(QWidget *parent = 0);

signals:

public slots:

private:
    QVBoxLayout *ilayout;
    QFormLayout *flayout;

    QLineEdit *m_Name;
    QLineEdit *m_Value;
    QDialogButtonBox *m_Submit;
    nwmPropDescriptionTextEdit *m_Desc;

public:
    QTreeView *m_View;
    QToolBar *m_Toolbar;
    QGroupBox *m_Form;

};

#endif // NWMPROPERTYWIDGET_H
