/********************************************************************************
** Form generated from reading UI file 'nwmaboutdialog.ui'
**
** Created: Thu Jun 24 20:03:03 2010
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NWMABOUTDIALOG_H
#define UI_NWMABOUTDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QFrame>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_nwmAboutDialog
{
public:
    QVBoxLayout *verticalLayout;
    QFrame *frame;
    QLabel *label;
    QFrame *line;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *nwmAboutDialog)
    {
        if (nwmAboutDialog->objectName().isEmpty())
            nwmAboutDialog->setObjectName(QString::fromUtf8("nwmAboutDialog"));
        nwmAboutDialog->resize(499, 314);
        verticalLayout = new QVBoxLayout(nwmAboutDialog);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, -1);
        frame = new QFrame(nwmAboutDialog);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        label = new QLabel(frame);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(0, -10, 475, 131));
        label->setMaximumSize(QSize(16777215, 191));
        label->setFrameShape(QFrame::NoFrame);
        label->setPixmap(QPixmap(QString::fromUtf8("nova.png")));
        label->setScaledContents(false);
        label->setOpenExternalLinks(false);
        line = new QFrame(frame);
        line->setObjectName(QString::fromUtf8("line"));
        line->setGeometry(QRect(0, 120, 475, 3));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(frame);

        buttonBox = new QDialogButtonBox(nwmAboutDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(nwmAboutDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), nwmAboutDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), nwmAboutDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(nwmAboutDialog);
    } // setupUi

    void retranslateUi(QDialog *nwmAboutDialog)
    {
        nwmAboutDialog->setWindowTitle(QApplication::translate("nwmAboutDialog", "About", 0, QApplication::UnicodeUTF8));
        label->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class nwmAboutDialog: public Ui_nwmAboutDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NWMABOUTDIALOG_H
