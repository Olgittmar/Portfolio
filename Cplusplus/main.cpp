// std
#include <iostream>
#include <fstream>

// Own Qt stuff
#include <MyApp.h>
#include <QCoreApplication>
// #include "src/userinterface/MyApp/MyApp.h"

// Qt
// #include <QObject>

// Own

int
main( int argc, char* argv[] )
{
    using namespace std;
    cout << "Running main!" << endl;

    UserInterface::MyApp app(argc, argv);
    // QCoreApplication::setApplicationVersion(QT_VERSION_STR);

    return app.exec();
}