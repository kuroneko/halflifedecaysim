#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "decaysimulation.h"
#include "newrunoptions.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      simulationIterations(100),
      simulationStartingPopulation(1000),
      chartSplineLines(true),
      chart(nullptr),
      chartView(nullptr),
      mXAxis(nullptr),
      mYAxis(nullptr),
      mSettings(nullptr),
      ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setupChartView();
    setCentralWidget(chartView);
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
    chart->removeAllSeries();

    if (!mXAxis) {
        mXAxis = new QtCharts::QValueAxis(chart);
        chart->addAxis(mXAxis, Qt::AlignBottom);
    }
    mXAxis->setRange(0.0, simulationIterations);
    mXAxis->setTickAnchor(0);
    mXAxis->setTickCount(11);

    if (!mYAxis) {
        mYAxis = new QtCharts::QValueAxis(this);
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
    if (!mSettings) {
        mSettings = new SettingsDialog(this);
        connect(mSettings, SIGNAL(accepted()), this, SLOT(changeSettings()));
    }
    if (!mSettings->isVisible()) {
        mSettings->setIterations(simulationIterations);
        mSettings->setPopulation(simulationStartingPopulation);
        mSettings->setSplineCharts(chartSplineLines);

        mSettings->show();
    } else {
        mSettings->raise();
    }
}

void MainWindow::changeSettings()
{
    auto *settings = dynamic_cast<SettingsDialog *>(sender());

    simulationIterations = settings->getIterations();
    simulationStartingPopulation = settings->getPopulation();
    chartSplineLines = settings->getSplineCharts();
    // reset the chart layout.
    setupChartView();
}


void MainWindow::on_actionAddRun_triggered()
{
    auto *runOptions = new NewRunOptions(this);
    runOptions->setAttribute(Qt::WA_DeleteOnClose, true);
    connect(runOptions, SIGNAL(accepted()), this, SLOT(addRun()));
    runOptions->show();
}

void MainWindow::addRun()
{
    auto *runOptions = dynamic_cast<NewRunOptions *>(sender());
    DecaySimulation decaySim(simulationStartingPopulation, simulationIterations, runOptions->getProbability());
    decaySim.run();
    auto *chartData = decaySim.getPopulationTimeData(this, chartSplineLines);
    chart->addSeries(chartData);
    update();
}
