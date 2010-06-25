#include <QtGui>
#include <QApplication>

#include "nwmapp.h"
#include "nwmmainwindow.h"

int main(int argc, char *argv[])
{
    nwmApp app(argc, argv);
    Q_INIT_RESOURCE(nwm);

    QPixmap pixmap(":/splash.png");
    QSplashScreen splash(pixmap);
    splash.show();

    app.processEvents();

    nwmMainWindow mainWin;
    app.setMainWindow(&mainWin);
    mainWin.showMaximized();

//    app.setStyle(new QCleanlooksStyle);

//    QFile file("nova.qss");
//    file.open(QFile::ReadOnly);
//    QString styleSheet = QLatin1String(file.readAll());
//    app.setStyleSheet(styleSheet);

    return app.exec();
}
