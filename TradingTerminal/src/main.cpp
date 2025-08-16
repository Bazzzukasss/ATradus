#include <QApplication>
#include "src/MainWindow.h"

using namespace atradus;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    w.show();

    return a.exec();
}
