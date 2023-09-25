#include <QApplication>
#include "IcePaste.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    IcePaste w;
    w.show();
    return a.exec();
}
