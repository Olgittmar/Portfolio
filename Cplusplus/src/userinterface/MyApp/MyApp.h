#pragma once

// Qt
#include <QApplication>
#include <QPointer>

// Own Qt stuff
#include "MainWindow.h"

namespace UserInterface {

class MyApp : public QApplication
{
    Q_OBJECT
  public:
    MyApp( int argc, char* argv[] ) : QApplication(argc, argv) {}
    ~MyApp();

    int exec();

  private slots:
    void runSolution( const MainWindow::SolutionOptions solutionIndex, const QString infile, const QString outFile );

  private:
    QPointer<MainWindow> mw;
    QList<QMetaObject::Connection> mConnections;
};

} // UserInterface