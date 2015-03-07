#include "mainwindow.h"
#include "titlebar/frame.h"

int main (int argc, char **argv)
{
    QApplication app(argc, argv);

    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));

    QFile file("./qss/candy.qss");
    file.open(QFile::ReadOnly);
    app.setStyleSheet(file.readAll());

#ifdef CNGC_V2

    Frame myframe;
    myframe.move(0,0);
    QVBoxLayout * vlayout = new QVBoxLayout(myframe.contentWidget());
    vlayout->setMargin(0);
    MainWindow* mainwindow = new MainWindow(myframe.contentWidget());
    vlayout->addWidget(mainwindow);

    myframe.show();
    //this->setAttribute(Qt::WA_TranslucentBackground,true);  //设置背景透明
#else
      MainWindow mw;
      mw.setWindowFlags(mw.windowFlags() & ~Qt::WindowMaximizeButtonHint);
      mw.show();

#endif

    return app.exec();
}
