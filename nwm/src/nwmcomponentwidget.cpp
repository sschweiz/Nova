#include <QtGui>
#include "nwmcomponentwidget.h"

nwmComponentWidget::nwmComponentWidget()
{
    int i;

    m_Common = new QGridLayout;
    m_Components = new QGridLayout;
    //m_Full = new QVBoxLayout;
    m_Output = new QLabel;
    m_OutLink = new QLabel;
    m_OutType = new QLabel;
    m_OutConn = new QToolButton;
    for (i = 0; i < NWM_MAX_INPUTS; i++) {
        m_Inputs[i] = new QLabel;
        m_Inputs[i]->setTextFormat(Qt::RichText);

        m_InLinks[i] = new QLabel;
        m_InLinks[i]->setTextFormat(Qt::RichText);
        m_InLinks[i]->setTextInteractionFlags(Qt::TextBrowserInteraction);

        m_InConn[i] = new QToolButton;
        m_InConn[i]->setIcon(QIcon(":/images/pm/bullet_delete.png"));
        m_InConn[i]->setAutoRaise(true);

        m_InTypes[i] = new QLabel;
    }
    m_Output->setTextFormat(Qt::RichText);
    m_OutLink->setTextFormat(Qt::RichText);
    m_OutLink->setTextInteractionFlags(Qt::TextBrowserInteraction);
    m_OutConn->setIcon(QIcon(":/images/pm/bullet_delete.png"));
    m_OutConn->setAutoRaise(true);

    QLabel *desc = new QLabel;
    desc->setText(tr("out = in0 + in1\n\nAdds line values of in0 and in1 and places their sum in out."));
    m_Components->addWidget(desc, 0, 0);

    m_Common->setVerticalSpacing(1);

    DoExample();

    addLayout(m_Common);
    addLayout(m_Components, 2);
    //setLayout(m_Full);
}

void nwmComponentWidget::UpdateComponent(const nwmComponentInfo &info)
{
    QString sz;
    int i, n;

    if (info.sInputs.count() > 5) { n = 5; } else { n = info.sInputs.count(); }

    for (i = 0; i < n; i++) {
        sz = tr("");
        if (info.sInputs[i].sRequired) {
            if (info.sInputs[i].sLink == NULL) {
                sz = QString(tr("<strong style=\"color: #ff0000;\">in%1:</strong>")).arg(i);
                m_InLinks[i]->setText("none");
            } else {
                sz = QString(tr("<strong>in%1:</strong>")).arg(i);
                m_InLinks[i]->setText(QString("<a href=\"#\">%1</a>").arg(info.sInputs[i].sLink->sId, 3, 10, QLatin1Char('0')));
            }
        }
        m_Inputs[i]->setText(sz);
    }
}

void nwmComponentWidget::clearCommon()
{
    QLayoutItem *child;
    while ((child = m_Common->takeAt(0)) != 0) {
        delete child;
    }
}

void nwmComponentWidget::DoExample()
{
    int i;
    // in this example, add 2 required inputs, 1 optional input and
    // a required output
    m_Inputs[0]->setText(tr("<strong>in0:</strong>"));
    m_Inputs[1]->setText(tr("<strong>in1:</strong>"));
    m_Inputs[2]->setText(tr("in2:"));
    m_Output->setText(tr("<strong>out:</strong>"));

    m_InLinks[0]->setText(tr("<a href=\"#\">003</a>"));
    m_InLinks[1]->setText(tr("<a href=\"#\">006</a>"));
    m_InLinks[2]->setText(tr("<a href=\"#\">none</a>"));
    m_OutLink->setText(tr("<a href=\"#\">002</a>"));

    m_InTypes[0]->setText(tr("(wave.generate)"));
    m_InTypes[1]->setText(tr("(random.gaussian)"));
    m_InTypes[2]->setText(tr(""));
    m_OutType->setText(tr("(output)"));

    for (i = 0; i < 3; i++) {
        m_Common->addWidget(m_Inputs[i], i, 0);
        m_Common->addWidget(m_InLinks[i], i, 1);
        m_Common->addWidget(m_InTypes[i], i, 2);
        if (i < 2) {
            m_Common->addWidget(m_InConn[i], i, 3);
        }
    }
    m_Common->addWidget(m_Output, 3, 0);
    m_Common->addWidget(m_OutLink, 3, 1);
    m_Common->addWidget(m_OutType, 3, 2);
    m_Common->addWidget(m_OutConn, 3, 3);
}
