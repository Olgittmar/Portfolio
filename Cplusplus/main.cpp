// std
#include <iostream>
#include <fstream>

// Own Qt stuff
#include "mainwindow.h"

// Qt
#include <QApplication>

int
main( int argc, char* argv[] )
{
    using namespace std;
    cout << "Running main!" << endl;

    QApplication app(argc, argv);
    QCoreApplication::setApplicationVersion(QT_VERSION_STR);
    MainWindow mw;

    mw.show();
    return app.exec();
}
