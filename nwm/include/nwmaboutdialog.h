#ifndef NWMABOUTDIALOG_H
#define NWMABOUTDIALOG_H

#include <QDialog>

namespace Ui {
    class nwmAboutDialog;
}

class nwmAboutDialog : public QDialog {
    Q_OBJECT
public:
    nwmAboutDialog(QWidget *parent = 0);
    ~nwmAboutDialog();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::nwmAboutDialog *ui;
};

#endif // NWMABOUTDIALOG_H
