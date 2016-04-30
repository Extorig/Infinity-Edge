#include "infinityedge.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    InfinityEdge w;
    w.show();

    return a.exec();
}
