#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCharts>
#include "settingsdialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    int simulationIterations;
    int simulationStartingPopulation;

    bool chartSplineLines;

protected:
    QtCharts::QChart *chart;
    QtCharts::QChartView *chartView;
    QValueAxis *mXAxis;
    QValueAxis *mYAxis;
    SettingsDialog *mSettings;

    void setupChartView();

private:
    Ui::MainWindow *ui;    

private slots:
    void on_actionExit_triggered();
    void on_actionSettings_triggered();
    void on_actionAddRun_triggered();

    void addRun();
    void changeSettings();
};
#endif // MAINWINDOW_H
