#pragma once

#include <QMainWindow>
#include <QFileDialog>
#include <QString>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    std::string inFileName() const { return inFile.toStdString(); }
    std::string outFileName() const { return outFile.toStdString(); }

    enum SolutionOptions { None, PointInPolygon };
    Q_ENUM(SolutionOptions);

private slots:
    void selectInFile();
    void selectOutFile();
    void runSolution();

private:
    void runPointInPolygon( std::string inFile, std::string outFile );

    Ui::MainWindow *ui;
    QList<QMetaObject::Connection> mConnections;

    QString inFile;
    QString outFile;
    int selectedSolution;
};
