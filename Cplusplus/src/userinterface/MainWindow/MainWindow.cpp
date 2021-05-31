// Own Qt stuff
#include "MainWindow.h"
#include "./ui_MainWindow.h"

// Std
#include <iostream>
#include <exception>

// Qt


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
            this, &MainWindow::onRunButtonPressed
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
    ui->currentInFileLabel->setText( inFile );
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
    ui->currentOutFileLabel->setText( outFile );
}

void
MainWindow::onRunButtonPressed()
{
    std::cout << "Run button pressed!" << std::endl;
    bool ok;
    SolutionOptions selectedSolution = (SolutionOptions)ui->solutionComboBox->currentData( Qt::UserRole ).toInt( &ok );
    if(!ok){
        throw std::exception("Invalid solution selection!");
        return;
    }
    emit runSolution( selectedSolution, inFile, outFile );
}