#include "mainwindow.h"
#include "./ui_mainwindow.h"

// Own
#include "src/solutions/PointInPolygon.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mConnections.append( {
        QObject::connect(
            ui->browseInFileButton, &QPushButton::pressed,
            this, &MainWindow::selectInFile
        ),
        QObject::connect(
            ui->browseOutFileButton, &QPushButton::pressed,
            this, &MainWindow::selectOutFile
        ),
        QObject::connect(
            ui->runButton, &QPushButton::pressed,
            this, &MainWindow::runSolution
        )
    } );
    
    ui->solutionComboBox->addItem( "", SolutionOptions::None );
    ui->solutionComboBox->addItem( "Point in polygon", SolutionOptions::PointInPolygon );
    ui->solutionComboBox->setEditable(false);
}

MainWindow::~MainWindow()
{
    for( auto it = mConnections.begin(); it != mConnections.end(); it++ ){
        QObject::disconnect( *it );
    }
    delete ui;
}


void
MainWindow::selectInFile()
{
    QFileDialog dialog(this, "Select input file" );
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setNameFilter("Input files (*.in)");
    dialog.setViewMode(QFileDialog::Detail);
    if( dialog.exec() ){
        inFile = dialog.selectedFiles().first();
    }
}

void
MainWindow::selectOutFile()
{
    QFileDialog dialog(this, "Select output file" );
    dialog.setFileMode( QFileDialog::AnyFile );
    dialog.setNameFilter( "Output files (*.ans)" );
    dialog.setViewMode(QFileDialog::Detail);
    if( dialog.exec() ){
        outFile = dialog.selectedFiles().first();
    }
}

void
MainWindow::runSolution()
{
    bool ok = false;
    int index = ui->solutionComboBox->currentData().toInt( &ok );
    if(ok) {
        switch(index) {
            case SolutionOptions::PointInPolygon:
            {
                runPointInPolygon( inFileName(), outFileName() );
            }
        }
    }
}

void
MainWindow::runPointInPolygon( std::string inFile, std::string outFile )
{
    std::cout << "Command: Run PointInPolygon with\n" << "inFile: " << inFile << "\n" << "outFile: " << outFile << std::endl;
}