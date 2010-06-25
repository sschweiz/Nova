#include <QtGui>
#include <Qsci/qsciscintilla.h>
#include <Qsci/qscilexerlua.h>
#include "nwmtriggereditorwidget.h"

nwmTriggerEditorWidget::nwmTriggerEditorWidget(QWidget *parent) :
    QWidget(parent)
{
    m_Toolbar = new QToolBar;
    m_btnBuild = new QPushButton;//(QIcon(":/image/success.png"), tr("Build Information"));
    m_Editor = new QsciScintilla;
    QsciLexerLua *lex = new QsciLexerLua();
    QGridLayout *layout = new QGridLayout;
    QHBoxLayout *hlayout = new QHBoxLayout;

    layout->setMargin(1);
    layout->setHorizontalSpacing(2);
    layout->setVerticalSpacing(2);

    hlayout->setMargin(0);
    hlayout->setSpacing(2);

    PopulateToolbar();

    m_btnBuild->setIcon(QIcon(":/images/success.png"));
    m_btnBuild->setIconSize(QSize(16, 16));
    m_btnBuild->setFixedSize(32, 32);

    lex->setDefaultFont(QFont(tr("Consolas"), 10));
    m_Editor->setLexer(lex);

    m_Editor->setMarginLineNumbers(1, true);
    m_Editor->setMarginsFont(QFont(tr("Consolas"), 10));
    m_Editor->setMarginWidth(1, tr("000 "));
    m_Editor->setIndentationGuides(true);
    m_Editor->setAutoIndent(true);
    m_Editor->setTabIndents(true);
    m_Editor->setTabWidth(4);

    hlayout->addWidget(m_Toolbar);
    hlayout->addWidget(m_btnBuild);

    layout->addLayout(hlayout, 0, 0);
    layout->addWidget(m_Editor, 1, 0);

    setLayout(layout);
}

void nwmTriggerEditorWidget::PopulateToolbar()
{
    m_Toolbar->addAction(QIcon(":/images/new.png"), tr("New"));
    m_Toolbar->addAction(QIcon(":/images/open.png"), tr("Open"));
    m_Toolbar->addAction(QIcon(":/images/save.png"), tr("Save"));
    m_Toolbar->addSeparator();
    m_Toolbar->addAction(QIcon(":/images/cut.png"), tr("Cut"));
    m_Toolbar->addAction(QIcon(":/images/copy.png"), tr("Copy"));
    m_Toolbar->addAction(QIcon(":/images/paste.png"), tr("Paste"));
    m_Toolbar->addSeparator();
    m_Toolbar->addAction(QIcon(":/images/build.png"), tr("Build"));
    m_Toolbar->addAction(QIcon(":/images/debug.png"), tr("Debug"));
}
