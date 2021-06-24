// std
#include <iostream>
#include <fstream>

// Own Qt stuff
#include <MyApp.h>

// Qt
// #include <QObject>

// Own

int
main( int argc, char* argv[] )
{
    std::cout << "Running main!" << std::endl;
    QScopedPointer<UserInterface::MyApp> app( new UserInterface::MyApp(argc, argv) );
    app->setApplicationVersion(QT_VERSION_STR);
    app->setApplicationName("CPlusPlusSolutionRunner");
    app->setApplicationDisplayName("C++ solution runner");
    // QCoreApplication::setApplicationVersion(QT_VERSION_STR);

    return app->exec();
}