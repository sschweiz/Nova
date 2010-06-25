#include "nwmaboutdialog.h"
#include "ui_nwmaboutdialog.h"

nwmAboutDialog::nwmAboutDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::nwmAboutDialog)
{
    ui->setupUi(this);
}

nwmAboutDialog::~nwmAboutDialog()
{
    delete ui;
}

void nwmAboutDialog::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}
