// Own Qt stuff
#include "MyApp.h"

// Std
#include <iostream>
#include <sstream>
#include <fstream>
#include <exception>

// Qt

// Own
#include "../solutions/PointInPolygon.h"

namespace UserInterface {

MyApp::~MyApp()
{
    for( auto it = mConnections.begin(); it != mConnections.end(); it++ ){
        disconnect( *it );
    }

    if( mw ){
        delete mw;
    }
}

int
MyApp::exec()
{
    if( !mw ){
        mw = QPointer( new MainWindow() );
        mConnections.append( {
            QObject::connect( mw, &MainWindow::runSolution,
            this, &MyApp::runSolution )
        } );
    }
    mw->show();
    return QApplication::exec();
}

void
MyApp::runSolution( const MainWindow::SolutionOptions solutionIndex, const QString inFile, const QString outFile )
{
    std::ifstream ifstrm( inFile.toStdString() );
    std::ofstream ofstrm( outFile.toStdString() );
    std::streambuf* istrmbuf;
    std::streambuf* ostrmbuf;
    // res only used for debug purposes here
    std::string res;
    
    //! Not 100% sure this is exception-safe...
    if( !ifstrm.is_open() ){
        std::cerr << "WARNING: Manual input is not supported, this option is for debug use only!" << std::endl;
        istrmbuf = std::cin.rdbuf();
    } else {
        istrmbuf = ifstrm.rdbuf();
    }
    if( !ofstrm.is_open() ){
        ostrmbuf = std::cout.rdbuf();
    } else {
        ostrmbuf = ofstrm.rdbuf();
    }

    std::istream in( istrmbuf );
    std::ostream out( ostrmbuf );
    // Make sure everything is ok before we begin processing
    if( in.good() && out.good() ){
        switch( solutionIndex ){
        case MainWindow::SolutionOptions::PointInPolygon:
        {
            std::cout << "Running PointInPolygon with" << std::endl;
            std::cout << "\tinFile: " << inFile.toStdString() << std::endl;
            std::cout << "\toutFile: " << outFile.toStdString() << std::endl;
            res = Solutions::PointInPolygon( in, out );
        }
        break;
        default:
            std::cout << "Please select a solution to run" << std::endl;
        }
    } else {
        std::cerr << "Input or output stream failed while processing command" << std::endl;
    }

    std::cout << res << std:: endl;
    if( ifstrm.is_open() ){
        ifstrm.close();
    }
    if( ofstrm.is_open() ){
        ofstrm.close();
    }
}

} // UserInterface