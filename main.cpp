#include "mainwindow.h"

int main (int argc, char **argv)
{
    QApplication app(argc, argv);

    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));

    MainWindow mw;
    //mw.setWindowFlags(mw.windowFlags() & ~Qt::WindowMaximizeButtonHint);
    mw.show();

    /*
    QFile file("mystyle.qss");
    file.open(QFile::ReadOnly);
    qApp->setStyleSheet(file.readAll());
    */

    return app.exec();
}
