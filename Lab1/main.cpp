#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}

// Dodać histogram R, G, B i luminancji
// lum = 0.27R + 0.62G + 0.11B
