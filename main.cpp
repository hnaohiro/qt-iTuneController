#include <QtGui/QApplication>
#include "mainwindow.h"

#include <QTextCodec>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));

    QApplication::setOrganizationName("Naohiro");
    QApplication::setApplicationName("iTunesController");

    MainWindow w;
    w.show();
    
    return a.exec();
}
