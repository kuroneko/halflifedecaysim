#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "settingsdialog.h"
#include "decaysimulation.h"
#include "newrunoptions.h"

using namespace QtCharts;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      simulationIterations(100),
      simulationStartingPopulation(1000),
      chartSplineLines(true),
      chart(nullptr),
      chartView(nullptr),
      chartWindow(nullptr),
      mXAxis(nullptr),
      mYAxis(nullptr),
      ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setupChartView();
    chartWindow = ui->mdiArea->addSubWindow(chartView);
    chartWindow->setWindowTitle(tr("Chart View"));    
    chartWindow->resize(400, 300);
    chartWindow->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupChartView()
{
    if (!chart) {
        chart = new QChart();
    }
    if (!chartView) {
        chartView = new QChartView(chart, this);
    }
    chartView->setRenderHint(QPainter::Antialiasing);
    chart->setTitle(tr("Population vs Time"));
    chart->removeAllSeries();

    if (!mXAxis) {
        mXAxis = new QValueAxis(chart);
        chart->addAxis(mXAxis, Qt::AlignBottom);
    }
    mXAxis->setRange(0.0, simulationIterations);
    mXAxis->setTickAnchor(0);
    mXAxis->setTickCount(11);

    if (!mYAxis) {
        mYAxis = new QValueAxis(this);
        chart->addAxis(mYAxis, Qt::AlignLeft);
    }
    mYAxis->setRange(0.0, simulationStartingPopulation);
    mYAxis->setTickCount(11);
    mYAxis->setTickAnchor(0);
}


void
MainWindow::on_actionExit_triggered()
{
    close();
}

void MainWindow::on_actionSettings_triggered()
{
    SettingsDialog settings;

    settings.setIterations(simulationIterations);
    settings.setPopulation(simulationStartingPopulation);
    settings.setSplineCharts(chartSplineLines);

    auto result = settings.exec();
    if (result == QDialog::Accepted) {
        simulationIterations = settings.getIterations();
        simulationStartingPopulation = settings.getPopulation();
        chartSplineLines = settings.getSplineCharts();
        // reset the chart layout.

        setupChartView();
    }
}

void MainWindow::on_actionAddRun_triggered()
{
    NewRunOptions runOptions;

    auto result = runOptions.exec();
    if (result == QDialog::Accepted) {
        DecaySimulation decaySim(simulationStartingPopulation, simulationIterations, runOptions.getProbability());
        decaySim.run();
        chart->addSeries(decaySim.getPopulationTimeData(chart, chartSplineLines));
    }
}

