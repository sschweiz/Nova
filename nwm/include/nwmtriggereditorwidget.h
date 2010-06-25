#ifndef NWMTRIGGEREDITORWIDGET_H
#define NWMTRIGGEREDITORWIDGET_H

#include <QPlainTextEdit>
#include <Qsci/qsciscintilla.h>
#include <QWidget>

QT_BEGIN_NAMESPACE
class QPushButton;
class QToolBar;
QT_END_NAMESPACE

class nwmTriggerTextEdit : public QPlainTextEdit {
public:
    nwmTriggerTextEdit(QWidget* parent = 0) : QPlainTextEdit(parent) { }
    virtual QSize sizeHint() const { return QSize(0, 45); }
};

class nwmTriggerEditorWidget : public QWidget
{
Q_OBJECT
public:
    explicit nwmTriggerEditorWidget(QWidget *parent = 0);

signals:

public slots:

private:
    QPushButton *m_btnBuild;
    QToolBar *m_Toolbar;
    QsciScintilla *m_Editor;

    void PopulateToolbar();

};

#endif // NWMTRIGGEREDITORWIDGET_H
