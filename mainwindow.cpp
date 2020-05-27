/*
 * HalflifeDecaySim: A Simple App to Model Radioactive Decay
 * Copyright (C) 2020 Chris Collins
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "decaysimulation.h"
#include "newrunoptions.h"
#include "aboutdialog.h"

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
    mXAxis->setTitleText(tr("Iterations"));

    if (!mYAxis) {
        mYAxis = new QtCharts::QValueAxis(this);
        chart->addAxis(mYAxis, Qt::AlignLeft);
    }
    mYAxis->setRange(0.0, simulationStartingPopulation);
    mYAxis->setTickCount(11);
    mYAxis->setTickAnchor(0);
    mYAxis->setTitleText(tr("Population"));
}

void MainWindow::on_actionAbout_triggered()
{
    auto *about = new AboutDialog(this);
    about->setAttribute(Qt::WA_DeleteOnClose, true);
    about->show();
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
