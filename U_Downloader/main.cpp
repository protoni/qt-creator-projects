#include "udownloader.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    UDownloader myapp;
    myapp.show();

    return app.exec();
}
