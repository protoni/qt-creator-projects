#include "startup.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Ps::Startup start_up;
    start_up.show();

    return a.exec();
}
