#include "widget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //QTextCodec *code = QTextCodec::codecForName("utf-8");
    Widget w;
    w.show();

    return a.exec();
}
