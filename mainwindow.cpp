#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "settingsdialog.h"
#include "decaysimulation.h"

using namespace QtCharts;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      simulationIterations(100),
      simulationStartingPopulation(1000),
      chart(nullptr),
      chartView(nullptr),
      chartWindow(nullptr),
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
        chartView->setRenderHint(QPainter::Antialiasing);
    }
    chart->setTitle(tr("Population vs Time"));   
}


void
MainWindow::on_actionExit_triggered()
{
    close();
}

void MainWindow::on_actionSettings_triggered()
{
    auto *settings = new SettingsDialog(this);

    settings->setIterations(simulationIterations);
    settings->setPopulation(simulationStartingPopulation);

    auto result = settings->exec();
    if (result == QDialog::Accepted) {
        simulationIterations = settings->getIterations();
        simulationStartingPopulation = settings->getPopulation();
    }
}

void MainWindow::on_actionAddRun_triggered()
{
    DecaySimulation     decaySim(simulationStartingPopulation, simulationIterations, 0.2);
    decaySim.run();
    chart->addSeries(decaySim.getPopulationTimeData(chart));
    chart->createDefaultAxes();
}

